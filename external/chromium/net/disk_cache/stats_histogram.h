// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_DISK_CACHE_STATS_HISTOGRAM_H_
#define NET_DISK_CACHE_STATS_HISTOGRAM_H_
#pragma once

#include <string>

#include "base/metrics/histogram.h"

namespace disk_cache {

class Stats;

class StatsHistogram : public base::Histogram {
 public:
  class StatsSamples : public SampleSet {
   public:
    Counts* GetCounts() {
      return &counts_;
    }
  };

  explicit StatsHistogram(const std::string& name, Sample minimum,
                          Sample maximum, size_t bucket_count)
      : Histogram(name, minimum, maximum, bucket_count), init_(false) {}
  ~StatsHistogram();

  static StatsHistogram* StatsHistogramFactoryGet(const std::string& name);

  
  bool Init(const Stats* stats);

  virtual Sample ranges(size_t i) const;
  virtual size_t bucket_count() const;
  virtual void SnapshotSample(SampleSet* sample) const;
  virtual Inconsistencies FindCorruption(const SampleSet& snapshot) const;
  virtual uint32 CalculateRangeChecksum() const;

 private:
  bool init_;
  static const Stats* stats_;
  DISALLOW_COPY_AND_ASSIGN(StatsHistogram);
};

}  

#endif  