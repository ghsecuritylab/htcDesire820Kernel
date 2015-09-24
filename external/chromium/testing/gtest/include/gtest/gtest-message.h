// Copyright 2005, Google Inc.
//     * Redistributions of source code must retain the above copyright
// copyright notice, this list of conditions and the following disclaimer
// this software without specific prior written permission.
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT

#ifndef GTEST_INCLUDE_GTEST_GTEST_MESSAGE_H_
#define GTEST_INCLUDE_GTEST_GTEST_MESSAGE_H_

#include <limits>

#include "gtest/internal/gtest-string.h"
#include "gtest/internal/gtest-internal.h"

namespace testing {

class GTEST_API_ Message {
 private:
  
  
  typedef std::ostream& (*BasicNarrowIoManip)(std::ostream&);

 public:
  
  
  
  
  
  Message() : ss_(new ::std::stringstream) {
    
    
    *ss_ << std::setprecision(std::numeric_limits<double>::digits10 + 2);
  }

  
  Message(const Message& msg) : ss_(new ::std::stringstream) {  
    *ss_ << msg.GetString();
  }

  
  explicit Message(const char* str) : ss_(new ::std::stringstream) {
    *ss_ << str;
  }

#if GTEST_OS_SYMBIAN
  
  template <typename T>
  inline Message& operator <<(const T& value) {
    StreamHelper(typename internal::is_pointer<T>::type(), value);
    return *this;
  }
#else
  
  template <typename T>
  inline Message& operator <<(const T& val) {
    ::GTestStreamToHelper(ss_.get(), val);
    return *this;
  }

  
  
  
  
  
  
  
  
  
  
  
  
  
  template <typename T>
  inline Message& operator <<(T* const& pointer) {  
    if (pointer == NULL) {
      *ss_ << "(null)";
    } else {
      ::GTestStreamToHelper(ss_.get(), pointer);
    }
    return *this;
  }
#endif  

  
  
  
  
  
  
  Message& operator <<(BasicNarrowIoManip val) {
    *ss_ << val;
    return *this;
  }

  
  Message& operator <<(bool b) {
    return *this << (b ? "true" : "false");
  }

  
  
  Message& operator <<(const wchar_t* wide_c_str) {
    return *this << internal::String::ShowWideCString(wide_c_str);
  }
  Message& operator <<(wchar_t* wide_c_str) {
    return *this << internal::String::ShowWideCString(wide_c_str);
  }

#if GTEST_HAS_STD_WSTRING
  
  
  Message& operator <<(const ::std::wstring& wstr);
#endif  

#if GTEST_HAS_GLOBAL_WSTRING
  
  
  Message& operator <<(const ::wstring& wstr);
#endif  

  
  
  
  
  internal::String GetString() const {
    return internal::StringStreamToString(ss_.get());
  }

 private:

#if GTEST_OS_SYMBIAN
  
  
  
  
  template <typename T>
  inline void StreamHelper(internal::true_type , T* pointer) {
    if (pointer == NULL) {
      *ss_ << "(null)";
    } else {
      ::GTestStreamToHelper(ss_.get(), pointer);
    }
  }
  template <typename T>
  inline void StreamHelper(internal::false_type , const T& value) {
    ::GTestStreamToHelper(ss_.get(), value);
  }
#endif  

  
  const internal::scoped_ptr< ::std::stringstream> ss_;

  
  
  void operator=(const Message&);
};

inline std::ostream& operator <<(std::ostream& os, const Message& sb) {
  return os << sb.GetString();
}

}  

#endif  