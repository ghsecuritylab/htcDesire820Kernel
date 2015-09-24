// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_HASH_VALUE_H_
#define NET_BASE_HASH_VALUE_H_

#include <string.h>

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string_piece.h"
#include "build/build_config.h"
#include "net/base/net_export.h"

namespace net {

struct NET_EXPORT SHA1HashValue {
  bool Equals(const SHA1HashValue& other) const;

  unsigned char data[20];
};

struct NET_EXPORT SHA256HashValue {
  bool Equals(const SHA256HashValue& other) const;

  unsigned char data[32];
};

enum HashValueTag {
  HASH_VALUE_SHA1,
  HASH_VALUE_SHA256,

  
  HASH_VALUE_TAGS_COUNT
};

class NET_EXPORT HashValue {
 public:
  explicit HashValue(HashValueTag tag) : tag(tag) {}
  HashValue() : tag(HASH_VALUE_SHA1) {}

  
  
  
  
  
  
  bool Equals(const HashValue& other) const;

  
  
  
  
  
  
  
  
  
  

  
  
  bool FromString(const base::StringPiece input);

  
  
  std::string ToString() const;

  size_t size() const;
  unsigned char* data();
  const unsigned char* data() const;

  HashValueTag tag;

 private:
  union {
    SHA1HashValue sha1;
    SHA256HashValue sha256;
  } fingerprint;
};

typedef std::vector<HashValue> HashValueVector;


class SHA1HashValueLessThan {
 public:
  bool operator()(const SHA1HashValue& lhs,
                  const SHA1HashValue& rhs) const {
    return memcmp(lhs.data, rhs.data, sizeof(lhs.data)) < 0;
  }
};

class SHA256HashValueLessThan {
 public:
  bool operator()(const SHA256HashValue& lhs,
                  const SHA256HashValue& rhs) const {
    return memcmp(lhs.data, rhs.data, sizeof(lhs.data)) < 0;
  }
};

class HashValuesEqual {
  public:
  explicit HashValuesEqual(const HashValue& fingerprint) :
      fingerprint_(fingerprint) {}

  bool operator()(const HashValue& other) const {
    return fingerprint_.Equals(other);
  }

  const HashValue& fingerprint_;
};


bool IsSHA1HashInSortedArray(const SHA1HashValue& hash,
                             const uint8* array,
                             size_t array_byte_len);

}  

#endif  
