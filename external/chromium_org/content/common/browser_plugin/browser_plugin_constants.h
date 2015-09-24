// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef  CONTENT_COMMON_BROWSER_PLUGIN_BROWSER_PLUGIN_CONSTANTS_H_
#define  CONTENT_COMMON_BROWSER_PLUGIN_BROWSER_PLUGIN_CONSTANTS_H_

namespace content {

namespace browser_plugin {

extern const char kMethodBack[];
extern const char kMethodCanGoBack[];
extern const char kMethodCanGoForward[];
extern const char kMethodForward[];
extern const char kMethodGetGuestInstanceId[];
extern const char kMethodGetInstanceId[];
extern const char kMethodGo[];
extern const char kMethodReload[];
extern const char kMethodStop[];
extern const char kMethodTerminate[];

extern const char kMethodInternalAttach[];
extern const char kMethodInternalAttachWindowTo[];
extern const char kMethodInternalTrackObjectLifetime[];

extern const char kEventInternalInstanceIDAllocated[];
extern const char kEventInternalTrackedObjectGone[];

extern const char kAttributeAllowTransparency[];
extern const char kAttributeApi[];
extern const char kAttributeAutoSize[];
extern const char kAttributeContentWindow[];
extern const char kAttributeMaxHeight[];
extern const char kAttributeMaxWidth[];
extern const char kAttributeMinHeight[];
extern const char kAttributeMinWidth[];
extern const char kAttributeName[];
extern const char kAttributePartition[];
extern const char kAttributeSrc[];

extern const char kDefaultPromptText[];
extern const char kId[];
extern const char kInitialHeight[];
extern const char kInitialWidth[];
extern const char kLastUnlockedBySelf[];
extern const char kMessageText[];
extern const char kMessageType[];
extern const char kName[];
extern const char kPermission[];
extern const char kPermissionTypeDialog[];
extern const char kPermissionTypeDownload[];
extern const char kPermissionTypeGeolocation[];
extern const char kPermissionTypeMedia[];
extern const char kPermissionTypeNewWindow[];
extern const char kPermissionTypePointerLock[];
extern const char kPersistPrefix[];
extern const char kProcessId[];
extern const char kRequestId[];
extern const char kRequestMethod[];
extern const char kTargetURL[];
extern const char kURL[];
extern const char kUserGesture[];
extern const char kWindowID[];
extern const char kWindowOpenDisposition[];

extern const char kErrorAlreadyNavigated[];
extern const char kErrorInvalidPartition[];
extern const char kErrorCannotRemovePartition[];

extern const char kBrowserPluginGuestManagerKeyName[];
extern const int kInstanceIDNone;
extern const int kInvalidPermissionRequestID;

}  

}  

#endif  
