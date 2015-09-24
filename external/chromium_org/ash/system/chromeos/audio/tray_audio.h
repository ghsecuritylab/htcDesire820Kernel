// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_CHROMEOS_AUDIO_TRAY_AUDIO_H_
#define ASH_SYSTEM_CHROMEOS_AUDIO_TRAY_AUDIO_H_

#include "ash/system/tray/tray_image_item.h"
#include "chromeos/audio/cras_audio_handler.h"

namespace ash {
namespace internal {

namespace tray {
class VolumeView;
class AudioDetailedView;
}

class TrayAudio : public TrayImageItem,
                  public chromeos::CrasAudioHandler::AudioObserver {
 public:
  explicit TrayAudio(SystemTray* system_tray);
  virtual ~TrayAudio();

 private:
  
  virtual bool GetInitialVisibility() OVERRIDE;

  
  virtual views::View* CreateDefaultView(user::LoginStatus status) OVERRIDE;
  virtual views::View* CreateDetailedView(user::LoginStatus status) OVERRIDE;
  virtual void DestroyDefaultView() OVERRIDE;
  virtual void DestroyDetailedView() OVERRIDE;
  virtual bool ShouldHideArrow() const OVERRIDE;
  virtual bool ShouldShowLauncher() const OVERRIDE;

  
  virtual void OnOutputVolumeChanged() OVERRIDE;
  virtual void OnOutputMuteChanged() OVERRIDE;
  virtual void OnInputGainChanged() OVERRIDE;
  virtual void OnInputMuteChanged() OVERRIDE;
  virtual void OnAudioNodesChanged() OVERRIDE;
  virtual void OnActiveOutputNodeChanged() OVERRIDE;
  virtual void OnActiveInputNodeChanged() OVERRIDE;

  void Update();

  tray::VolumeView* volume_view_;
  tray::AudioDetailedView* audio_detail_;

  
  
  bool pop_up_volume_view_;

  DISALLOW_COPY_AND_ASSIGN(TrayAudio);
};

}  
}  

#endif  