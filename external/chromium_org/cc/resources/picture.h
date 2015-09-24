// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_PICTURE_H_
#define CC_RESOURCES_PICTURE_H_

#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/debug/trace_event.h"
#include "base/lazy_instance.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "cc/base/cc_export.h"
#include "cc/base/region.h"
#include "skia/ext/lazy_pixel_ref.h"
#include "skia/ext/refptr.h"
#include "third_party/skia/include/core/SkPixelRef.h"
#include "third_party/skia/include/core/SkTileGridPicture.h"
#include "ui/gfx/rect.h"

namespace base {
class Value;
}

namespace skia {
class AnalysisCanvas;
}

namespace cc {

class ContentLayerClient;

class CC_EXPORT Picture
    : public base::RefCountedThreadSafe<Picture> {
 public:
  typedef std::pair<int, int> PixelRefMapKey;
  typedef std::vector<skia::LazyPixelRef*> PixelRefs;
  typedef base::hash_map<PixelRefMapKey, PixelRefs> PixelRefMap;

  static scoped_refptr<Picture> Create(gfx::Rect layer_rect);
  static scoped_refptr<Picture> CreateFromValue(const base::Value* value);
  static scoped_refptr<Picture> CreateFromSkpValue(const base::Value* value);

  gfx::Rect LayerRect() const { return layer_rect_; }
  gfx::Rect OpaqueRect() const { return opaque_rect_; }

  
  scoped_refptr<Picture> GetCloneForDrawingOnThread(
      unsigned thread_index) const;

  
  void CloneForDrawing(int num_threads);

  
  
  void Record(ContentLayerClient* client,
              const SkTileGridPicture::TileGridInfo& tile_grid_info);

  
  void GatherPixelRefs(const SkTileGridPicture::TileGridInfo& tile_grid_info);

  
  bool HasRecording() const { return picture_.get() != NULL; }

  
  
  int Raster(SkCanvas* canvas,
             SkDrawPictureCallback* callback,
             const Region& negated_content_region,
             float contents_scale);

  
  
  void Replay(SkCanvas* canvas);

  scoped_ptr<base::Value> AsValue() const;

  class CC_EXPORT PixelRefIterator {
   public:
    PixelRefIterator();
    PixelRefIterator(gfx::Rect layer_rect, const Picture* picture);
    ~PixelRefIterator();

    skia::LazyPixelRef* operator->() const {
      DCHECK_LT(current_index_, current_pixel_refs_->size());
      return (*current_pixel_refs_)[current_index_];
    }

    skia::LazyPixelRef* operator*() const {
      DCHECK_LT(current_index_, current_pixel_refs_->size());
      return (*current_pixel_refs_)[current_index_];
    }

    PixelRefIterator& operator++();
    operator bool() const {
      return current_index_ < current_pixel_refs_->size();
    }

   private:
    static base::LazyInstance<PixelRefs> empty_pixel_refs_;
    const Picture* picture_;
    const PixelRefs* current_pixel_refs_;
    unsigned current_index_;

    gfx::Point min_point_;
    gfx::Point max_point_;
    int current_x_;
    int current_y_;
  };

  void EmitTraceSnapshot();
  void EmitTraceSnapshotAlias(Picture* original);

  bool WillPlayBackBitmaps() const { return picture_->willPlayBackBitmaps(); }

 private:
  explicit Picture(gfx::Rect layer_rect);
  
  
  Picture(const skia::RefPtr<SkPicture>&,
          gfx::Rect layer_rect,
          gfx::Rect opaque_rect,
          const PixelRefMap& pixel_refs);
  
  Picture(SkPicture*,
          gfx::Rect layer_rect,
          gfx::Rect opaque_rect);
  ~Picture();

  gfx::Rect layer_rect_;
  gfx::Rect opaque_rect_;
  skia::RefPtr<SkPicture> picture_;

  typedef std::vector<scoped_refptr<Picture> > PictureVector;
  PictureVector clones_;

  PixelRefMap pixel_refs_;
  gfx::Point min_pixel_cell_;
  gfx::Point max_pixel_cell_;
  gfx::Size cell_size_;

  scoped_refptr<base::debug::ConvertableToTraceFormat>
    AsTraceableRasterData(float scale) const;
  scoped_refptr<base::debug::ConvertableToTraceFormat>
    AsTraceableRecordData() const;

  friend class base::RefCountedThreadSafe<Picture>;
  friend class PixelRefIterator;
  DISALLOW_COPY_AND_ASSIGN(Picture);
};

}  

#endif  
