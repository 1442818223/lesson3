LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

# Sets the name of the library.
LOCAL_MODULE := sutemplate

LOCAL_LDLIBS := -llog
# # Sets the library as a shared library.
#
LOCAL_LDLIBS +=-L$(SYSROOT)/usr/lib -lm -llog   #一定要这样写才行对应cmake中的find_library(log-lib log)

# Provides a relative path to your source file(s).
LOCAL_SRC_FILES := main.cpp

include $(BUILD_SHARED_LIBRARY)
