// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef org_chromium_example_jni_generator_SampleForTests_JNI
#define org_chromium_example_jni_generator_SampleForTests_JNI

#include <jni.h>

#include "base/android/jni_android.h"
#include "base/android/scoped_java_ref.h"
#include "base/basictypes.h"
#include "base/logging.h"

using base::android::ScopedJavaLocalRef;

namespace {
const char kInnerStructAClassPath[] =
    "org/chromium/example/jni_generator/SampleForTests$InnerStructA";
const char kSampleForTestsClassPath[] =
    "org/chromium/example/jni_generator/SampleForTests";
const char kInnerStructBClassPath[] =
    "org/chromium/example/jni_generator/SampleForTests$InnerStructB";
jclass g_InnerStructA_clazz = NULL;
jclass g_SampleForTests_clazz = NULL;
jclass g_InnerStructB_clazz = NULL;
}  

namespace base {
namespace android {

static jint Init(JNIEnv* env, jobject obj,
    jstring param);

static jdouble GetDoubleFunction(JNIEnv* env, jobject obj);

static jfloat GetFloatFunction(JNIEnv* env, jclass clazz);

static void SetNonPODDatatype(JNIEnv* env, jobject obj,
    jobject rect);

static jobject GetNonPODDatatype(JNIEnv* env, jobject obj);

static void Destroy(JNIEnv* env, jobject obj,
    jint nativeCPPClass) {
  DCHECK(nativeCPPClass) << "Destroy";
  CPPClass* native = reinterpret_cast<CPPClass*>(nativeCPPClass);
  return native->Destroy(env, obj);
}

static jint Method(JNIEnv* env, jobject obj,
    jint nativeCPPClass) {
  DCHECK(nativeCPPClass) << "Method";
  CPPClass* native = reinterpret_cast<CPPClass*>(nativeCPPClass);
  return native->Method(env, obj);
}

static jdouble MethodOtherP0(JNIEnv* env, jobject obj,
    jint nativePtr) {
  DCHECK(nativePtr) << "MethodOtherP0";
  CPPClass::InnerClass* native =
      reinterpret_cast<CPPClass::InnerClass*>(nativePtr);
  return native->MethodOtherP0(env, obj);
}

static void AddStructB(JNIEnv* env, jobject obj,
    jint nativeCPPClass,
    jobject b) {
  DCHECK(nativeCPPClass) << "AddStructB";
  CPPClass* native = reinterpret_cast<CPPClass*>(nativeCPPClass);
  return native->AddStructB(env, obj, b);
}

static void IterateAndDoSomethingWithStructB(JNIEnv* env, jobject obj,
    jint nativeCPPClass) {
  DCHECK(nativeCPPClass) << "IterateAndDoSomethingWithStructB";
  CPPClass* native = reinterpret_cast<CPPClass*>(nativeCPPClass);
  return native->IterateAndDoSomethingWithStructB(env, obj);
}

static base::subtle::AtomicWord g_SampleForTests_javaMethod = 0;
static jint Java_SampleForTests_javaMethod(JNIEnv* env, jobject obj, jint foo,
    jint bar) {
  
  DCHECK(g_SampleForTests_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, g_SampleForTests_clazz,
      "javaMethod",

"("
"I"
"I"
")"
"I",
      &g_SampleForTests_javaMethod);

  jint ret =
    env->CallIntMethod(obj,
      method_id, foo, bar);
  base::android::CheckException(env);
  return ret;
}

static base::subtle::AtomicWord g_SampleForTests_staticJavaMethod = 0;
static jboolean Java_SampleForTests_staticJavaMethod(JNIEnv* env) {
  
  DCHECK(g_SampleForTests_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, g_SampleForTests_clazz,
      "staticJavaMethod",

"("
")"
"Z",
      &g_SampleForTests_staticJavaMethod);

  jboolean ret =
    env->CallStaticBooleanMethod(g_SampleForTests_clazz,
      method_id);
  base::android::CheckException(env);
  return ret;
}

static base::subtle::AtomicWord g_SampleForTests_packagePrivateJavaMethod = 0;
static void Java_SampleForTests_packagePrivateJavaMethod(JNIEnv* env, jobject
    obj) {
  
  DCHECK(g_SampleForTests_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, g_SampleForTests_clazz,
      "packagePrivateJavaMethod",

"("
")"
"V",
      &g_SampleForTests_packagePrivateJavaMethod);

  env->CallVoidMethod(obj,
      method_id);
  base::android::CheckException(env);

}

static base::subtle::AtomicWord g_SampleForTests_methodThatThrowsException = 0;
static void Java_SampleForTests_methodThatThrowsException(JNIEnv* env, jobject
    obj) {
  
  DCHECK(g_SampleForTests_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, g_SampleForTests_clazz,
      "methodThatThrowsException",

"("
")"
"V",
      &g_SampleForTests_methodThatThrowsException);

  env->CallVoidMethod(obj,
      method_id);

}

static base::subtle::AtomicWord g_InnerStructA_create = 0;
static ScopedJavaLocalRef<jobject> Java_InnerStructA_create(JNIEnv* env, jlong
    l,
    jint i,
    jstring s) {
  
  DCHECK(g_InnerStructA_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_STATIC>(
      env, g_InnerStructA_clazz,
      "create",

"("
"J"
"I"
"Ljava/lang/String;"
")"
"Lorg/chromium/example/jni_generator/SampleForTests$InnerStructA;",
      &g_InnerStructA_create);

  jobject ret =
    env->CallStaticObjectMethod(g_InnerStructA_clazz,
      method_id, l, i, s);
  base::android::CheckException(env);
  return ScopedJavaLocalRef<jobject>(env, ret);
}

static base::subtle::AtomicWord g_SampleForTests_addStructA = 0;
static void Java_SampleForTests_addStructA(JNIEnv* env, jobject obj, jobject a)
    {
  
  DCHECK(g_SampleForTests_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, g_SampleForTests_clazz,
      "addStructA",

"("
"Lorg/chromium/example/jni_generator/SampleForTests$InnerStructA;"
")"
"V",
      &g_SampleForTests_addStructA);

  env->CallVoidMethod(obj,
      method_id, a);
  base::android::CheckException(env);

}

static base::subtle::AtomicWord g_SampleForTests_iterateAndDoSomething = 0;
static void Java_SampleForTests_iterateAndDoSomething(JNIEnv* env, jobject obj)
    {
  
  DCHECK(g_SampleForTests_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, g_SampleForTests_clazz,
      "iterateAndDoSomething",

"("
")"
"V",
      &g_SampleForTests_iterateAndDoSomething);

  env->CallVoidMethod(obj,
      method_id);
  base::android::CheckException(env);

}

static base::subtle::AtomicWord g_InnerStructB_getKey = 0;
static jlong Java_InnerStructB_getKey(JNIEnv* env, jobject obj) {
  
  DCHECK(g_InnerStructB_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, g_InnerStructB_clazz,
      "getKey",

"("
")"
"J",
      &g_InnerStructB_getKey);

  jlong ret =
    env->CallLongMethod(obj,
      method_id);
  base::android::CheckException(env);
  return ret;
}

static base::subtle::AtomicWord g_InnerStructB_getValue = 0;
static ScopedJavaLocalRef<jstring> Java_InnerStructB_getValue(JNIEnv* env,
    jobject obj) {
  
  DCHECK(g_InnerStructB_clazz);
  jmethodID method_id =
      base::android::MethodID::LazyGet<
      base::android::MethodID::TYPE_INSTANCE>(
      env, g_InnerStructB_clazz,
      "getValue",

"("
")"
"Ljava/lang/String;",
      &g_InnerStructB_getValue);

  jstring ret =
    static_cast<jstring>(env->CallObjectMethod(obj,
      method_id));
  base::android::CheckException(env);
  return ScopedJavaLocalRef<jstring>(env, ret);
}


static bool RegisterNativesImpl(JNIEnv* env) {

  g_InnerStructA_clazz = reinterpret_cast<jclass>(env->NewGlobalRef(
      base::android::GetClass(env, kInnerStructAClassPath).obj()));
  g_SampleForTests_clazz = reinterpret_cast<jclass>(env->NewGlobalRef(
      base::android::GetClass(env, kSampleForTestsClassPath).obj()));
  g_InnerStructB_clazz = reinterpret_cast<jclass>(env->NewGlobalRef(
      base::android::GetClass(env, kInnerStructBClassPath).obj()));
  static const JNINativeMethod kMethodsSampleForTests[] = {
    { "nativeInit",
"("
"Ljava/lang/String;"
")"
"I", reinterpret_cast<void*>(Init) },
    { "nativeDestroy",
"("
"I"
")"
"V", reinterpret_cast<void*>(Destroy) },
    { "nativeGetDoubleFunction",
"("
")"
"D", reinterpret_cast<void*>(GetDoubleFunction) },
    { "nativeGetFloatFunction",
"("
")"
"F", reinterpret_cast<void*>(GetFloatFunction) },
    { "nativeSetNonPODDatatype",
"("
"Landroid/graphics/Rect;"
")"
"V", reinterpret_cast<void*>(SetNonPODDatatype) },
    { "nativeGetNonPODDatatype",
"("
")"
"Ljava/lang/Object;", reinterpret_cast<void*>(GetNonPODDatatype) },
    { "nativeMethod",
"("
"I"
")"
"I", reinterpret_cast<void*>(Method) },
    { "nativeMethodOtherP0",
"("
"I"
")"
"D", reinterpret_cast<void*>(MethodOtherP0) },
    { "nativeAddStructB",
"("
"I"
"Lorg/chromium/example/jni_generator/SampleForTests$InnerStructB;"
")"
"V", reinterpret_cast<void*>(AddStructB) },
    { "nativeIterateAndDoSomethingWithStructB",
"("
"I"
")"
"V", reinterpret_cast<void*>(IterateAndDoSomethingWithStructB) },
  };
  const int kMethodsSampleForTestsSize = arraysize(kMethodsSampleForTests);

  if (env->RegisterNatives(g_SampleForTests_clazz,
                           kMethodsSampleForTests,
                           kMethodsSampleForTestsSize) < 0) {
    LOG(ERROR) << "RegisterNatives failed in " << __FILE__;
    return false;
  }

  return true;
}
}  
}  

#endif  