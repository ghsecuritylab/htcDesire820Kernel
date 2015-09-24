// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_FORMAT_H_
#define GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_FORMAT_H_


#include <KHR/khrplatform.h>

#include <string.h>

#include "base/safe_numerics.h"
#include "gpu/command_buffer/common/bitfield_helpers.h"
#include "gpu/command_buffer/common/cmd_buffer_common.h"
#include "gpu/command_buffer/common/gles2_cmd_ids.h"
#include "gpu/command_buffer/common/types.h"

typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLboolean;
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned long GLulong;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef khronos_intptr_t GLintptr;
typedef khronos_ssize_t  GLsizeiptr;

namespace gpu {
namespace gles2 {

#pragma pack(push, 1)

namespace id_namespaces {

enum IdNamespaces {
  kBuffers,
  kFramebuffers,
  kProgramsAndShaders,
  kRenderbuffers,
  kTextures,
  kQueries,
  kVertexArrays,
  kNumIdNamespaces
};

COMPILE_ASSERT(kBuffers == 0, kBuffers_is_not_0);
COMPILE_ASSERT(kFramebuffers == 1, kFramebuffers_is_not_1);
COMPILE_ASSERT(kProgramsAndShaders == 2, kProgramsAndShaders_is_not_2);
COMPILE_ASSERT(kRenderbuffers == 3, kRenderbuffers_is_not_3);
COMPILE_ASSERT(kTextures == 4, kTextures_is_not_4);

}  

template <typename T>
struct SizedResult {
  typedef T Type;

  T* GetData() {
    return static_cast<T*>(static_cast<void*>(&data));
  }

  
  
  static size_t ComputeSize(size_t num_results) {
    return sizeof(T) * num_results + sizeof(uint32);  
  }

  
  
  static size_t ComputeSizeFromBytes(size_t size_of_result_in_bytes) {
    return size_of_result_in_bytes + sizeof(uint32);  
  }

  
  static uint32 ComputeMaxResults(size_t size_of_buffer) {
    return (size_of_buffer >= sizeof(uint32)) ?
        ((size_of_buffer - sizeof(uint32)) / sizeof(T)) : 0;  
  }

  
  void SetNumResults(size_t num_results) {
    size = sizeof(T) * num_results;  
  }

  
  int32 GetNumResults() const {
    return size / sizeof(T);  
  }

  
  void CopyResult(void* dst) const {
    memcpy(dst, &data, size);
  }

  uint32 size;  
  int32 data;  
};

COMPILE_ASSERT(sizeof(SizedResult<int8>) == 8, SizedResult_size_not_8);
COMPILE_ASSERT(offsetof(SizedResult<int8>, size) == 0,
               OffsetOf_SizedResult_size_not_0);
COMPILE_ASSERT(offsetof(SizedResult<int8>, data) == 4,
               OffsetOf_SizedResult_data_not_4);

struct ProgramInput {
  uint32 type;             
  int32 size;              
  uint32 location_offset;  
                           
  uint32 name_offset;      
  uint32 name_length;      
};

struct ProgramInfoHeader {
  uint32 link_status;
  uint32 num_attribs;
  uint32 num_uniforms;
  
};

struct QuerySync {
  void Reset() {
    process_count = 0;
    result = 0;
  }

  uint32 process_count;
  uint64 result;
};

COMPILE_ASSERT(sizeof(ProgramInput) == 20, ProgramInput_size_not_20);
COMPILE_ASSERT(offsetof(ProgramInput, type) == 0,
               OffsetOf_ProgramInput_type_not_0);
COMPILE_ASSERT(offsetof(ProgramInput, size) == 4,
               OffsetOf_ProgramInput_size_not_4);
COMPILE_ASSERT(offsetof(ProgramInput, location_offset) == 8,
               OffsetOf_ProgramInput_location_offset_not_8);
COMPILE_ASSERT(offsetof(ProgramInput, name_offset) == 12,
               OffsetOf_ProgramInput_name_offset_not_12);
COMPILE_ASSERT(offsetof(ProgramInput, name_length) == 16,
               OffsetOf_ProgramInput_name_length_not_16);

COMPILE_ASSERT(sizeof(ProgramInfoHeader) == 12, ProgramInfoHeader_size_not_12);
COMPILE_ASSERT(offsetof(ProgramInfoHeader, link_status) == 0,
               OffsetOf_ProgramInfoHeader_link_status_not_0);
COMPILE_ASSERT(offsetof(ProgramInfoHeader, num_attribs) == 4,
               OffsetOf_ProgramInfoHeader_num_attribs_not_4);
COMPILE_ASSERT(offsetof(ProgramInfoHeader, num_uniforms) == 8,
               OffsetOf_ProgramInfoHeader_num_uniforms_not_8);

namespace cmds {

#include "../common/gles2_cmd_format_autogen.h"

// These are hand written commands.

struct GetAttribLocation {
  typedef GetAttribLocation ValueType;
  static const CommandId kCmdId = kGetAttribLocation;
  static const cmd::ArgFlags kArgFlags = cmd::kFixed;

  typedef GLint Result;

  static uint32 ComputeSize() {
    return static_cast<uint32>(sizeof(ValueType));  
  }

  void SetHeader() {
    header.SetCmd<ValueType>();
  }

  void Init(
      GLuint _program, uint32 _name_shm_id, uint32 _name_shm_offset,
      uint32 _location_shm_id, uint32 _location_shm_offset,
      uint32 _data_size) {
    SetHeader();
    program = _program;
    name_shm_id = _name_shm_id;
    name_shm_offset = _name_shm_offset;
    location_shm_id = _location_shm_id;
    location_shm_offset = _location_shm_offset;
    data_size = _data_size;
  }

  void* Set(
      void* cmd, GLuint _program, uint32 _name_shm_id, uint32 _name_shm_offset,
      uint32 _location_shm_id, uint32 _location_shm_offset,
      uint32 _data_size) {
    static_cast<ValueType*>(
        cmd)->Init(
            _program, _name_shm_id, _name_shm_offset, _location_shm_id,
            _location_shm_offset, _data_size);
    return NextCmdAddress<ValueType>(cmd);
  }

  CommandHeader header;
  uint32 program;
  uint32 name_shm_id;
  uint32 name_shm_offset;
  uint32 location_shm_id;
  uint32 location_shm_offset;
  uint32 data_size;
};

COMPILE_ASSERT(sizeof(GetAttribLocation) == 28,
               Sizeof_GetAttribLocation_is_not_28);
COMPILE_ASSERT(offsetof(GetAttribLocation, header) == 0,
               OffsetOf_GetAttribLocation_header_not_0);
COMPILE_ASSERT(offsetof(GetAttribLocation, program) == 4,
               OffsetOf_GetAttribLocation_program_not_4);
COMPILE_ASSERT(offsetof(GetAttribLocation, name_shm_id) == 8,
               OffsetOf_GetAttribLocation_name_shm_id_not_8);
COMPILE_ASSERT(offsetof(GetAttribLocation, name_shm_offset) == 12,
               OffsetOf_GetAttribLocation_name_shm_offset_not_12);
COMPILE_ASSERT(offsetof(GetAttribLocation, location_shm_id) == 16,
               OffsetOf_GetAttribLocation_location_shm_id_not_16);
COMPILE_ASSERT(offsetof(GetAttribLocation, location_shm_offset) == 20,
               OffsetOf_GetAttribLocation_location_shm_offset_not_20);
COMPILE_ASSERT(offsetof(GetAttribLocation, data_size) == 24,
               OffsetOf_GetAttribLocation_data_size_not_24);


struct GetAttribLocationBucket {
  typedef GetAttribLocationBucket ValueType;
  static const CommandId kCmdId = kGetAttribLocationBucket;
  static const cmd::ArgFlags kArgFlags = cmd::kFixed;

  typedef GLint Result;

  static uint32 ComputeSize() {
    return static_cast<uint32>(sizeof(ValueType));  
  }

  void SetHeader() {
    header.SetCmd<ValueType>();
  }

  void Init(
      GLuint _program, uint32 _name_bucket_id,
      uint32 _location_shm_id, uint32 _location_shm_offset) {
    SetHeader();
    program = _program;
    name_bucket_id = _name_bucket_id;
    location_shm_id = _location_shm_id;
    location_shm_offset = _location_shm_offset;
  }

  void* Set(
      void* cmd, GLuint _program, uint32 _name_bucket_id,
      uint32 _location_shm_id, uint32 _location_shm_offset) {
    static_cast<ValueType*>(
        cmd)->Init(
            _program, _name_bucket_id, _location_shm_id,
            _location_shm_offset);
    return NextCmdAddress<ValueType>(cmd);
  }

  CommandHeader header;
  uint32 program;
  uint32 name_bucket_id;
  uint32 location_shm_id;
  uint32 location_shm_offset;
};

COMPILE_ASSERT(sizeof(GetAttribLocationBucket) == 20,
               Sizeof_GetAttribLocationBucket_is_not_24);
COMPILE_ASSERT(offsetof(GetAttribLocationBucket, header) == 0,
               OffsetOf_GetAttribLocationBucket_header_not_0);
COMPILE_ASSERT(offsetof(GetAttribLocationBucket, program) == 4,
               OffsetOf_GetAttribLocationBucket_program_not_4);
COMPILE_ASSERT(offsetof(GetAttribLocationBucket, name_bucket_id) == 8,
               OffsetOf_GetAttribLocationBucket_name_bucket_id_not_8);
COMPILE_ASSERT(offsetof(GetAttribLocationBucket, location_shm_id) == 12,
               OffsetOf_GetAttribLocationBucket_location_shm_id_not_12);
COMPILE_ASSERT(offsetof(GetAttribLocationBucket, location_shm_offset) == 16,
               OffsetOf_GetAttribLocationBucket_location_shm_offset_not_16);

struct GetUniformLocation {
  typedef GetUniformLocation ValueType;
  static const CommandId kCmdId = kGetUniformLocation;
  static const cmd::ArgFlags kArgFlags = cmd::kFixed;

  typedef GLint Result;

  static uint32 ComputeSize() {
    return static_cast<uint32>(sizeof(ValueType));  
  }

  void SetHeader() {
    header.SetCmd<ValueType>();
  }

  void Init(
      GLuint _program, uint32 _name_shm_id, uint32 _name_shm_offset,
      uint32 _location_shm_id, uint32 _location_shm_offset,
      uint32 _data_size) {
    SetHeader();
    program = _program;
    name_shm_id = _name_shm_id;
    name_shm_offset = _name_shm_offset;
    location_shm_id = _location_shm_id;
    location_shm_offset = _location_shm_offset;
    data_size = _data_size;
  }

  void* Set(
      void* cmd, GLuint _program, uint32 _name_shm_id, uint32 _name_shm_offset,
      uint32 _location_shm_id, uint32 _location_shm_offset,
      uint32 _data_size) {
    static_cast<ValueType*>(
        cmd)->Init(
            _program, _name_shm_id, _name_shm_offset, _location_shm_id,
            _location_shm_offset, _data_size);
    return NextCmdAddress<ValueType>(cmd);
  }

  CommandHeader header;
  uint32 program;
  uint32 name_shm_id;
  uint32 name_shm_offset;
  uint32 location_shm_id;
  uint32 location_shm_offset;
  uint32 data_size;
};

COMPILE_ASSERT(sizeof(GetUniformLocation) == 28,
               Sizeof_GetUniformLocation_is_not_28);
COMPILE_ASSERT(offsetof(GetUniformLocation, header) == 0,
               OffsetOf_GetUniformLocation_header_not_0);
COMPILE_ASSERT(offsetof(GetUniformLocation, program) == 4,
               OffsetOf_GetUniformLocation_program_not_4);
COMPILE_ASSERT(offsetof(GetUniformLocation, name_shm_id) == 8,
               OffsetOf_GetUniformLocation_name_shm_id_not_8);
COMPILE_ASSERT(offsetof(GetUniformLocation, name_shm_offset) == 12,
               OffsetOf_GetUniformLocation_name_shm_offset_not_12);
COMPILE_ASSERT(offsetof(GetUniformLocation, location_shm_id) == 16,
               OffsetOf_GetUniformLocation_location_shm_id_not_16);
COMPILE_ASSERT(offsetof(GetUniformLocation, location_shm_offset) == 20,
               OffsetOf_GetUniformLocation_location_shm_offset_not_20);
COMPILE_ASSERT(offsetof(GetUniformLocation, data_size) == 24,
               OffsetOf_GetUniformLocation_data_size_not_24);

struct GetUniformLocationBucket {
  typedef GetUniformLocationBucket ValueType;
  static const CommandId kCmdId = kGetUniformLocationBucket;
  static const cmd::ArgFlags kArgFlags = cmd::kFixed;

  typedef GLint Result;

  static uint32 ComputeSize() {
    return static_cast<uint32>(sizeof(ValueType));  
  }

  void SetHeader() {
    header.SetCmd<ValueType>();
  }

  void Init(
      GLuint _program, uint32 _name_bucket_id,
      uint32 _location_shm_id, uint32 _location_shm_offset) {
    SetHeader();
    program = _program;
    name_bucket_id = _name_bucket_id;
    location_shm_id = _location_shm_id;
    location_shm_offset = _location_shm_offset;
  }

  void* Set(
      void* cmd, GLuint _program, uint32 _name_bucket_id,
      uint32 _location_shm_id, uint32 _location_shm_offset) {
    static_cast<ValueType*>(
        cmd)->Init(
            _program, _name_bucket_id, _location_shm_id,
            _location_shm_offset);
    return NextCmdAddress<ValueType>(cmd);
  }

  CommandHeader header;
  uint32 program;
  uint32 name_bucket_id;
  uint32 location_shm_id;
  uint32 location_shm_offset;
};

COMPILE_ASSERT(sizeof(GetUniformLocationBucket) == 20,
               Sizeof_GetUniformLocationBucket_is_not_24);
COMPILE_ASSERT(offsetof(GetUniformLocationBucket, header) == 0,
               OffsetOf_GetUniformLocationBucket_header_not_0);
COMPILE_ASSERT(offsetof(GetUniformLocationBucket, program) == 4,
               OffsetOf_GetUniformLocationBucket_program_not_4);
COMPILE_ASSERT(offsetof(GetUniformLocationBucket, name_bucket_id) == 8,
               OffsetOf_GetUniformLocationBucket_name_bucket_id_not_8);
COMPILE_ASSERT(offsetof(GetUniformLocationBucket, location_shm_id) == 12,
               OffsetOf_GetUniformLocationBucket_location_shm_id_not_12);
COMPILE_ASSERT(offsetof(GetUniformLocationBucket, location_shm_offset) == 16,
               OffsetOf_GetUniformLocationBucket_location_shm_offset_not_16);

struct GenMailboxCHROMIUM {
  typedef GenMailboxCHROMIUM ValueType;
  static const CommandId kCmdId = kGenMailboxCHROMIUM;
  static const cmd::ArgFlags kArgFlags = cmd::kFixed;
  CommandHeader header;
};

struct InsertSyncPointCHROMIUM {
  typedef InsertSyncPointCHROMIUM ValueType;
  static const CommandId kCmdId = kInsertSyncPointCHROMIUM;
  static const cmd::ArgFlags kArgFlags = cmd::kFixed;
  CommandHeader header;
};

#pragma pack(pop)

}  
}  
}  

#endif  