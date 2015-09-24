// Copyright 2008 Google Inc.  All rights reserved.
//     * Redistributions of source code must retain the above copyright
// copyright notice, this list of conditions and the following disclaimer
// this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT


#ifndef GOOGLE_PROTOBUF_REFLECTION_OPS_H__
#define GOOGLE_PROTOBUF_REFLECTION_OPS_H__

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/message.h>

namespace google {
namespace protobuf {
namespace internal {

class LIBPROTOBUF_EXPORT ReflectionOps {
 public:
  static void Copy(const Message& from, Message* to);
  static void Merge(const Message& from, Message* to);
  static void Clear(Message* message);
  static bool IsInitialized(const Message& message);
  static void DiscardUnknownFields(Message* message);

  
  
  
  static void FindInitializationErrors(const Message& message,
                                       const string& prefix,
                                       vector<string>* errors);

 private:
  
  GOOGLE_DISALLOW_EVIL_CONSTRUCTORS(ReflectionOps);
};

}  
}  

}  
#endif  