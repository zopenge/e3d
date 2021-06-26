/**
 * @file e3d_arch.h
 * @author zopenge (zopenge@126.com)
 * @brief The architecture macro of platform.
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

// Windows Platform
#if PLATFORM_WIN

#	if defined(_WIN64)
#		define _PLATFORM_ARCH_64 1
#	else
#		define _PLATFORM_ARCH_32 1
#	endif

// IOS Platform
#elif PLATFORM_IOS

#	import <targetconditionals.h>

#	if (TARGET_IPHONE_SIMULATOR == 1)
#		define _TARGET_OS_SIMULATOR_ 1
#	else
#		define _TARGET_OS_SIMULATOR_ 0
#	endif

#	if defined(__LP64__) || defined(__arm64__) || defined(__x86_64__)
#		define _PLATFORM_ARCH_64 1
#	else
#		define _PLATFORM_ARCH_32 1
#	endif

// Only work for OBJ-C mode.
#	ifdef __OBJC__
#		import <Availability.h>
#		import <Foundation/Foundation.h>
#	endif

// Android Platform
#elif PLATFORM_ANDROID

#	define _TARGET_OS_SIMULATOR_ 0

#	if defined(__aarch64__) || defined(__x86_64__)
#		define _PLATFORM_ARCH_64 1
#	else
#		define _PLATFORM_ARCH_32 1
#	endif

#	define NS_EXPORT

#	ifdef _cplusplus
extern "C" {
#	endif
/*
 * To work around http://code.google.com/p/android/issues/detail?id=23203
 * we don't link with the crt objects. In some configurations, this means
 * a lack of the __dso_handle symbol because it is defined there, and
 * depending on the android platform and ndk versions used, it may or may
 * not be defined in libc.so. In the latter case, we fail to link. Defining
 * it here as weak makes us provide the symbol when it's not provided by
 * the crt objects, making the change transparent for future NDKs that
 * would fix the original problem. On older NDKs, it is not a problem
 * either because the way __dso_handle was used was already broken (and
 * the custom linker works around it).
 */
NS_EXPORT __attribute__((weak)) void* __dso_handle;
#	ifdef _cplusplus
}
#	endif

#	include <jni.h>

#endif

#include <assert.h>
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>