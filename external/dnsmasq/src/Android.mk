LOCAL_PATH := $(call my-dir)

#########################

include $(CLEAR_VARS)
LOCAL_SRC_FILES :=  bpf.c cache.c dbus.c dhcp.c dnsmasq.c forward.c helper.c lease.c log.c \
                    netlink.c network.c option.c rfc1035.c rfc2131.c tftp.c util.c

LOCAL_MODULE := dnsmasq

LOCAL_C_INCLUDES := external/dnsmasq/src

# ** [start] Network - 20120612 to support IPv6 Dns server
# ** remove original source code ** \
LOCAL_CFLAGS := -O2 -g -W -Wall -D__ANDROID__ -DNO_IPV6 -DNO_TFTP -DNO_SCRIPT
# ** add new source code here **
LOCAL_CFLAGS := -O2 -g -W -Wall -D__ANDROID__ -DNO_TFTP -DNO_SCRIPT
# ** [end]
LOCAL_SYSTEM_SHARED_LIBRARIES := libc libcutils libnetutils

include $(BUILD_EXECUTABLE)

