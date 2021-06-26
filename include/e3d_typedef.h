/**
 * @file e3d_typedef.h
 * @author zopenge (zopenge@126.com)
 * @brief The type define for platform.
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#ifdef PLATFORM_IOS
#	include <sys/types.h>
#endif

namespace E3D {

// 8-bits ANSI character.
typedef char _chara;
// 16-bits UNICODE character.
typedef wchar_t _charw;
// Signed 8-bits integer.
typedef signed char _tiny;
// Signed 16-bits integer.
typedef signed short _short;
// Signed 32-bits integer.
typedef signed int _int;
// Unsigned 8-bits integer.
typedef unsigned char _byte;
// Unsigned 16-bits integer.
typedef unsigned short _word;
// Unsigned 32-bits integer.
// @remark: Be careful, we use 'unsigned long' before, but the arm64 compile will make it as 64-bits data type ! so here we use 'unsigned int' to replace it.
typedef unsigned int _dword;
// Signed 64-bits integer.
typedef signed long long _large;
// Unsigned 64-bits integer.
typedef unsigned long long _qword;
// Signed 32/64-bits integer, (Base on compiler, BE CAREFUL TO USE IT !!!)
typedef long _long;
// 32-bits floating point number.
typedef float _float;
// 64-bits floating point number.
typedef double _double;
// Boolean value ( 8 Bits ), 0 indicates false, other values indicate true.
typedef bool _boolean;
// Any type.
typedef void _void;
// Handle to a win32 kernel object.
typedef void* _handle;
// A time value in seconds.
typedef time_t _time_t;
// The unsigned int pointer
typedef uintptr_t _uintptr_t;

//	The arguments list
typedef va_list _va_list;

// The thread ID
typedef _qword _thread_id;
//	The thread return type
#if PLATFORM_WIN
typedef _dword _thread_ret;
#else
typedef void* _thread_ret;
#endif

} // namespace EGE

#define TYPE_CHECKER(x)     \
	namespace E3D {         \
	template <>             \
	struct TypeChecker<x> { \
		TypeChecker(x) {    \
		}                   \
	};                      \
	}

// We will declare type checker class here
template <class T>
struct TypeChecker;

// Common types
TYPE_CHECKER(_chara*)
TYPE_CHECKER(_charw*)
TYPE_CHECKER(const _chara*)
TYPE_CHECKER(const _charw*)
TYPE_CHECKER(const _void*)
TYPE_CHECKER(_void*)
TYPE_CHECKER(_chara)
TYPE_CHECKER(_charw)
TYPE_CHECKER(_tiny)
TYPE_CHECKER(_short)
TYPE_CHECKER(_byte)
TYPE_CHECKER(_word)
TYPE_CHECKER(_int)
TYPE_CHECKER(_dword)
TYPE_CHECKER(_long)
TYPE_CHECKER(_large)
TYPE_CHECKER(_qword)
TYPE_CHECKER(_float)
TYPE_CHECKER(_double)
TYPE_CHECKER(_boolean)

// Enable the type checker
#ifdef _DEBUG
#	define CHECK_ARG(i, var) TypeChecker<T##i> checker##i(var)
// Disable the type checker
#else
#	define CHECK_ARG(i, var)
#endif