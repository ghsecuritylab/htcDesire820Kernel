// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_WIN_REGISTRY_H_
#define BASE_WIN_REGISTRY_H_
#pragma once

#include <windows.h>
#include <string>

#include "base/base_api.h"
#include "base/basictypes.h"

namespace base {
namespace win {

class BASE_API RegKey {
 public:
  RegKey();
  RegKey(HKEY rootkey, const wchar_t* subkey, REGSAM access);
  ~RegKey();

  LONG Create(HKEY rootkey, const wchar_t* subkey, REGSAM access);

  LONG CreateWithDisposition(HKEY rootkey, const wchar_t* subkey,
                             DWORD* disposition, REGSAM access);

  LONG Open(HKEY rootkey, const wchar_t* subkey, REGSAM access);

  
  LONG CreateKey(const wchar_t* name, REGSAM access);

  
  LONG OpenKey(const wchar_t* name, REGSAM access);

  void Close();

  DWORD ValueCount() const;

  
  LONG ReadName(int index, std::wstring* name) const;

  
  bool Valid() const { return key_ != NULL; }

  
  
  LONG DeleteKey(const wchar_t* name);

  
  LONG DeleteValue(const wchar_t* name);

  bool ValueExists(const wchar_t* name) const;

  LONG ReadValue(const wchar_t* name, void* data, DWORD* dsize,
                 DWORD* dtype) const;
  LONG ReadValue(const wchar_t* name, std::wstring* value) const;
  LONG ReadValueDW(const wchar_t* name, DWORD* value) const;
  LONG ReadInt64(const wchar_t* name, int64* value) const;

  LONG WriteValue(const wchar_t* name, const void* data, DWORD dsize,
                  DWORD dtype);
  LONG WriteValue(const wchar_t* name, const wchar_t* value);
  LONG WriteValue(const wchar_t* name, DWORD value);

  
  
  LONG StartWatching();

  
  
  
  bool HasChanged();

  
  
  LONG StopWatching();

  inline bool IsWatching() const { return watch_event_ != 0; }
  HANDLE watch_event() const { return watch_event_; }
  HKEY Handle() const { return key_; }

 private:
  HKEY key_;  
  HANDLE watch_event_;

  DISALLOW_COPY_AND_ASSIGN(RegKey);
};

class BASE_API RegistryValueIterator {
 public:
  RegistryValueIterator(HKEY root_key, const wchar_t* folder_key);

  ~RegistryValueIterator();

  DWORD ValueCount() const;

  
  bool Valid() const;

  
  void operator++();

  const wchar_t* Name() const { return name_; }
  const wchar_t* Value() const { return value_; }
  DWORD ValueSize() const { return value_size_; }
  DWORD Type() const { return type_; }

  int Index() const { return index_; }

 private:
  
  bool Read();

  
  HKEY key_;

  
  int index_;

  
  wchar_t name_[MAX_PATH];
  wchar_t value_[MAX_PATH];
  DWORD value_size_;
  DWORD type_;

  DISALLOW_COPY_AND_ASSIGN(RegistryValueIterator);
};

class BASE_API RegistryKeyIterator {
 public:
  RegistryKeyIterator(HKEY root_key, const wchar_t* folder_key);

  ~RegistryKeyIterator();

  DWORD SubkeyCount() const;

  
  bool Valid() const;

  
  void operator++();

  const wchar_t* Name() const { return name_; }

  int Index() const { return index_; }

 private:
  
  bool Read();

  
  HKEY key_;

  
  int index_;

  wchar_t name_[MAX_PATH];

  DISALLOW_COPY_AND_ASSIGN(RegistryKeyIterator);
};

}  
}  

#endif  