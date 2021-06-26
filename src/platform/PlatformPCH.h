#pragma once

// Standard Files
#include <cstdint>
#include <limits>
#include <math.h>
#include <wchar.h>

#ifdef __cplusplus
extern "C" {
#endif

// Unicode Char Files
#include "uchar/uchar.h"

// pthread Files
#if USE_PTHREAD
#	include "pthread.h"
#endif

#ifdef __cplusplus
}
#endif

// Win32 Platform
#if PLATFORM_WIN

// Windows Header Files
#	include "os/win/headers.h"
// System Files
#	include <dbghelp.h>
#	include <iptypes.h>
#	include <lm.h>
#	include <mmsystem.h>
#	include <objbase.h>
#	include <tlhelp32.h>
#	include <ws2tcpip.h>
// Redefined Windows Variables and Functions
#	include "os/win/macros.h"
// Network
#	include "os/win/networks.h"

// Libraries Files
#	pragma comment(lib, "version")
#	pragma comment(lib, "wininet")
#	pragma comment(lib, "netapi32")
#	pragma comment(lib, "winmm")
#	pragma comment(lib, "Iphlpapi")
#	pragma comment(lib, "ws2_32.lib")

// Some rename functions
#	define strtoull _strtoui64

#	if USE_PTHREAD
typedef int (*__pthread_attr_init)(pthread_attr_t* attr);
typedef int (*__pthread_create)(pthread_t* tid, const pthread_attr_t* attr, void*(PTW32_CDECL* start)(void*), void* arg);
typedef int (*__pthread_detach)(pthread_t tid);
typedef int (*__pthread_attr_setdetachstate)(pthread_attr_t* attr, int detachstate);
typedef int (*__pthread_attr_destroy)(pthread_attr_t* attr);
typedef pthread_t (*__pthread_self)(void);
typedef int (*__pthread_attr_setschedpolicy)(pthread_attr_t*, int);
typedef int (*__pthread_attr_setschedparam)(pthread_attr_t* attr, const struct sched_param* param);
typedef int (*__pthread_kill)(pthread_t thread, int sig);
typedef int (*__pthread_join)(pthread_t thread, void** value_ptr);

extern __pthread_attr_init _pthread_attr_init;
extern __pthread_create _pthread_create;
extern __pthread_detach _pthread_detach;
extern __pthread_attr_setdetachstate _pthread_attr_setdetachstate;
extern __pthread_attr_destroy _pthread_attr_destroy;
extern __pthread_self _pthread_self;
extern __pthread_attr_setschedpolicy _pthread_attr_setschedpolicy;
extern __pthread_attr_setschedparam _pthread_attr_setschedparam;
extern __pthread_kill _pthread_kill;
extern __pthread_join _pthread_join;
#	endif

int gettimeofday(struct timeval* tp, struct timezone* tzp);

// IOS Platform
#elif PLATFORM_IOS

// Use pthread
#	ifndef USE_PTHREAD
#		define USE_PTHREAD
#	endif

// Foundation Files
#	ifdef __OBJC__
#		import <Availability.h>
#		import <Foundation/Foundation.h>
#	endif

// System Files
#	import <cerrno>
#	import <dirent.h>
#	import <fcntl.h>
#	import <mach/mach.h>
#	import <pthread.h>
#	import <sys/mman.h>
#	import <sys/signal.h>
#	import <sys/stat.h>
#	import <sys/time.h>
#	import <sys/types.h>
#	import <unistd.h>

// Objective-C Files
#	import "Platform/ios/NSPlatform.h"
#	ifdef __OBJC__
#		import "Platform/ios/NSMappedFile.h"
#	endif

// Some header files must be included after the namespace using declaration,
// otherwise compile failed
#	import <net/if_dl.h>
#	import <sys/sysctl.h>

// Network
#	include "os/ios/networks.h"

// Enable custom C Function Implementation
#	define ENABLE_CUSTOM_C_FUNC_IMPL

// Android Platform
#elif PLATFORM_ANDROID

// Use pthread
#	ifndef USE_PTHREAD
#		define USE_PTHREAD
#	endif

// System Files
#	include <cerrno>
#	include <dirent.h>
#	include <fcntl.h>
#	include <pthread.h>
#	include <signal.h>
#	include <sys/stat.h>
#	include <sys/time.h>
#	include <sys/wait.h>
#	include <unistd.h>

// NDK Files
#	include <android/asset_manager.h>
#	include <android/asset_manager_jni.h>
#	include <android/log.h>

// NDK-Tools Files
#	include "cpufeatures/cpu-features.h"

// Network
#	include "os/android/networks.h"

// Enable custom C Function Implementation
#	define ENABLE_CUSTOM_C_FUNC_IMPL

// Linux Platform
#elif PLATFORM_LINUX

// Use pthread
#	ifndef USE_PTHREAD
#		define USE_PTHREAD
#	endif
#	include <pthread.h>

// Enable custom C Function Implementation
#	define ENABLE_CUSTOM_C_FUNC_IMPL

#endif

// Implementation of standard C functions
#if ENABLE_CUSTOM_C_FUNC_IMPL

#	ifdef __cplusplus
extern "C" {
#	endif
char* __itoa__(int value, char* result, int base);
char* __utoa__(unsigned int value, char* result, int base);
char* __i64toa__(signed long long value, char* result, int base);
char* __u64toa__(unsigned long long value, char* result, int base);
wchar_t* __itow__(int value, wchar_t* result, int base);
wchar_t* __utow__(unsigned int value, wchar_t* result, int base);
wchar_t* __i64tow__(signed long long value, wchar_t* result, int base);
wchar_t* __u64tow__(unsigned long long value, wchar_t* result, int base);
#	ifdef __cplusplus
}
#	endif
#	define itoa __itoa__
#	define utoa __utoa__

#endif

// E3D Headers
#include "e3d.h"

// Any-OS Files
#include "os/anyPlatform.h"

using namespace E3D;