/**
 * @file e3d_macros.h
 * @author zopenge (zopenge@126.com)
 * @brief The macros for E3D.
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#define _WSTRING(s) L##s
#define _WIDEN(s) _WSTRING(s)

#define _FILENAME_A ((const _chara*)__FILE__)
#define _BUILDDATE_A ((const _chara*)__DATE__)
#define _BUILDTIME_A ((const _chara*)__TIME__)
#define _FUNCTION_A ((const _chara*)__FUNCTION__)

#define _FILENAME_W ((const _charw*)_WIDEN(__FILE__))
#define _BUILDDATE_W ((const _charw*)_WIDEN(__DATE__))
#define _BUILDTIME_W ((const _charw*)_WIDEN(__TIME__))
#define _FUNCTION_W ((const _charw*)_WIDEN(__FUNCTION__))

#define _LINENUMBER __LINE__

// Assert
#if PLATFORM_WIN
#	define _DEFAULT_ASSERT(x) ((x) ? (void)0 : _wassert(_WIDEN(#    x), _FILENAME_W, _LINENUMBER))
#	define _DEFAULT_ASSERT_WITH_DETAIL(x, linenumber, filename) (void)((!!(x)) || _wassert(_WIDEN(#    x), _WIDEN(#    filename), linenumber))
#elif PLATFORM_IOS
#	define _USE_STANDARD_MEM_OPERATOR_ // Ignore to use EGE's memory operation
#	define _USE_STANDARD_MALLOC_OPERATOR_ // Ignore to use EGE's malloc/free ... memory operation

#	define _DEFAULT_ASSERT(x) ((x) ? (void)0 : __assert(#    x, _FILENAME_A, _LINENUMBER))
#	define _DEFAULT_ASSERT_WITH_DETAIL(x, linenumber, filename) ((x) ? (void)0 : __assert(#    x, filename, linenumber))
#elif PLATFORM_ANDROID
#	define _USE_STANDARD_MEM_OPERATOR_ // Ignore to use EGE's memory operation
#	define _USE_STANDARD_MALLOC_OPERATOR_ // Ignore to use EGE's malloc/free ... memory operation

// Here we redefined the default assert macro, because the android NDK is different to IOS SDK
#	define _DEFAULT_ASSERT(x) ((x) ? (void)0 : __assert(#    x, _LINENUMBER, _FILENAME_A))
#	define _DEFAULT_ASSERT_WITH_DETAIL(x, linenumber, filename) ((x) ? (void)0 : __assert(#    x, linenumber, filename))
#endif

// #pragma - output string when compile
#define _PRAGMA_STR1(x) #x
#define _PRAGMA_STR2(x) _PRAGMA_STR1(x)
#define _NOTE(x) message(__FILE__ "(" _PRAGMA_STR2(__LINE__) ") : -NOTE- " #x)

// Debug Mode
#if defined(_DEBUG)
#	define _STATIC_ASSERT_ENABLE_ 1
#	define _ASSERT_ENABLE_ 1
#	define _VERIFY_ENABLE_ 1
// Release Mode
#else
#	define _STATIC_ASSERT_ENABLE_ 0
#	define _ASSERT_ENABLE_ 0
#	define _VERIFY_ENABLE_ 0
#endif

// CRASH
#define CRASH()                   \
	{                             \
		int* _crash_pointer_ = 0; \
		*_crash_pointer_ = 1;     \
	}

// Debug-Break
#ifdef PLATFORM_WIN
#	define DEBUG_BREAK() __asm {int 3}
#	define NOP() __asm NOP
#else
#	define DEBUG_BREAK() __asm__("trap")
#	define NOP() __asm {nop}
#endif

#if defined(__GNUC__) && !defined(__CC_ARM) && !defined(__ARMCC__)
#	define HIDDEN __attribute__((visibility("hidden")))
#else
#	define HIDDEN
#endif

// GNUC doesn't allow 'override' keyword
#ifdef __GNUC__
#	define override
#endif

// DLL-IN/OUT
#if defined PLATFORM_WIN
#	ifndef DLL_IN
#		define DLL_IN __declspec(dllimport)
#	endif
#	ifndef DLL_OUT
#		define DLL_OUT __declspec(dllexport)
#	endif
#endif

// NULL and BOOLEAN
#define _null 0
//! @remark: we do not use the boolean here because the C# get the return value from boolean function would only use the (low-16 bits) AL register value, but the high-16 bits is undefined.
#define _true (_dword) true
#define _false (_dword) false

// Static Assert
#if _DEBUG
extern "C" void __e3d__assert(const wchar_t* error, const wchar_t* filename, unsigned int linenumber);
#	ifdef PLATFORM_IOS
#		define E3D_STATIC_ASSERT(B, T) _Static_assert(B, T)
#	else
#		define E3D_STATIC_ASSERT(B, T) static_assert(B, T)
#	endif
#else
#	define E3D_STATIC_ASSERT(B, T)
#endif

// Assert
#if _DEBUG
#	define E3D_ASSERT(x)            \
		{                            \
			if (!(x))                \
				_DEFAULT_ASSERT(#x); \
		}
#	define E3D_ASSERT2(x, y)       \
		{                           \
			if (!(x))               \
				_DEFAULT_ASSERT(y); \
		}
#else
#	define E3D_ASSERT(x) \
		{                 \
		}
#	define E3D_ASSERT2(x, y) \
		{                     \
		}
#endif

// VAList
#define BEGIN_VA_LIST(args, format) \
	_va_list args;                  \
	va_start(args, format)
#define END_VA_LIST(args) va_end(args)
#ifndef va_copy
#	define va_copy(d, s) ((d) = (s))
#endif

#ifndef MAX
#	define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

#ifndef MIN
#	define MIN(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef CLAMP
#	define CLAMP(v, a, b) ((v < (a)) ? (a) : ((v > (b)) ? v : (b)))
#endif

// This macro is used to avoid warnings about unused variables.
// Usually where the variables are only used in debug mode.
#define UNUSED_VAR(x) (x) = (x)

// UTF-16 Header
#ifndef _UTF16_HEADER
#	define _UTF16_HEADER_0 0xFF
#	define _UTF16_HEADER_1 0xFE
#	define _UTF16_HEADER 0xFEFF
#endif

// UTF-8 Header
#ifndef _UTF8_HEADER
#	define _UTF8_HEADER_0 0xEF
#	define _UTF8_HEADER_1 0xBB
#	define _UTF8_HEADER_2 0xBF
#	define _UTF8_HEADER 0xBFBBEF
// Skip the UTF-8 header
#	define SKIP_UTF_CODE_BY_INDEX(string, size, index)      \
		if ((_byte)*string == (_byte)_UTF8_HEADER_##index) { \
			E3D_ASSERT(size != 0);                           \
			string++;                                        \
			size--;                                          \
		}
#	define SKIP_UTF_CODE(string, size)         \
		SKIP_UTF_CODE_BY_INDEX(string, size, 0) \
		SKIP_UTF_CODE_BY_INDEX(string, size, 1) \
		SKIP_UTF_CODE_BY_INDEX(string, size, 2)
#	define SKIP_UTF_CODE_WITHOUT_SIZE(string)             \
		{                                                  \
			_dword unused_size = 3;                        \
			SKIP_UTF_CODE_BY_INDEX(string, unused_size, 0) \
			SKIP_UTF_CODE_BY_INDEX(string, unused_size, 1) \
			SKIP_UTF_CODE_BY_INDEX(string, unused_size, 2) \
		}
#endif

// Force-inline
#ifndef INLINE
#	if defined(__GNUC__)
#		define INLINE __inline__
#	elif defined(_MSC_VER)
#		define INLINE __forceinline
#	else
#		define INLINE inline
#	endif
#endif

// No-inline
#ifndef NOINLINE
#	if defined(__GNUC__)
#		define NOINLINE __attribute((__noinline__))
#	else
#		define NOINLINE
#	endif
#endif

// PURE Virtual Interface
#define PURE = 0

// Helpful arguments tips
#ifndef IN
#	define IN
#endif
#ifndef OUT
#	define OUT
#endif

// KB, MB, GB
#define KB *1024ull
#define MB *1024ull KB
#define GB *1024ull MB

// Program entrance return code
#ifndef EXIT_SUCCESS
#	define EXIT_SUCCESS 0
#endif
#ifndef EXIT_FAILURE
#	define EXIT_FAILURE 1
#endif
#ifndef EXIT_RESTART
#	define EXIT_RESTART (-1)
#endif

// The exception code
#ifndef MS_CPP_EXCEPTION
#	define MS_CPP_EXCEPTION 0xE06D7363
#endif
#ifndef MS_VC_EXCEPTION
#	define MS_VC_EXCEPTION 0x406D1388
#endif

// This macro to prevent a copy from being made of your class
#define NO_COPY_OPERATIONS(classname) \
private:                              \
	classname(const classname&);      \
	const classname& operator=(const classname&);

// Define a singleton instance creator/accessors.
#define SINGLETON(c)                 \
private:                             \
	HIDDEN c();                      \
	HIDDEN ~c();                     \
                                     \
public:                              \
	HIDDEN static c& GetInstance() { \
		static c s##c;               \
		return s##c;                 \
	}

// Value combination
#define E3D_MAKEWORD(a, b) ((_word)(((_byte)(((_dword)(a)) & 0xff)) | ((_word)((_byte)(((_dword)(b)) & 0xff))) << 8))
#define E3D_MAKEDWORD(a, b) ((_dword)(((_word)(((_dword)(a)) & 0xffff)) | ((_dword)((_word)(((_dword)(b)) & 0xffff))) << 16))
#define E3D_MAKEQWORD(a, b) ((_qword)(((_dword)(((_qword)(a)) & 0xffffffff)) | ((_qword)((_dword)(((_qword)(b)) & 0xffffffff))) << 32))
#define E3D_LODWORD(l) ((_dword)(((_qword)(l)) & 0xffffffff))
#define E3D_HIDWORD(l) ((_dword)((((_qword)(l)) >> 32) & 0xffffffff))
#define E3D_LOWORD(l) ((_word)(((_dword)(l)) & 0xffff))
#define E3D_HIWORD(l) ((_word)((((_dword)(l)) >> 16) & 0xffff))
#define E3D_LOBYTE(w) ((_byte)(((_dword)(w)) & 0xff))
#define E3D_HIBYTE(w) ((_byte)((((_dword)(w)) >> 8) & 0xff))

// Build 32-bits ID ( example : PACK_ID( 'c', 'o', 'r', 'e' ) )
#define E3D_PACK_ID(a, b, c, d) (((d) << 24) | ((c) << 16) | ((b) << 8) | (a))
// Pack two 16-bits to 32-bits
#define E3D_PACK_DWORD(x, y) (((x) << 16) | (y))
// Unpack 32-bits to 16 bits
#define E3D_UNPACK_DWORD_X(v) (((v) >> 16) & 0x0000FFFF)
#define E3D_UNPACK_DWORD_Y(v) ((v)&0x0000FFFF)

// Free
#define E3D_FREE(x)      \
	{                    \
		if ((x)) {       \
			::free(x);   \
			(x) = _null; \
		}                \
	}

// Delete
#define E3D_DELETE(x)    \
	{                    \
		if ((x)) {       \
			delete (x);  \
			(x) = _null; \
		}                \
	}
#define E3D_DELETE_ARRAY(x) \
	{                       \
		if ((x)) {          \
			delete[](x);    \
			(x) = _null;    \
		}                   \
	}
#define E3D_RELEASE(x)      \
	{                       \
		if ((x)) {          \
			(x)->Release(); \
			(x) = _null;    \
		}                   \
	}

// Array
#define E3D_INIT(x) memset(&x, 0, sizeof(x))
#define E3D_INIT_ARRAY(x) memset(x, 0, sizeof(x))
#define E3D_ARRAY_NUMBER(x) (sizeof(x) / sizeof(x[0]))

// Ratio in percentage
#define E3D_RATIO(num, total_num) (((_float)(num)) / ((_float)(total_num)))
#define E3D_RATIO_D(num, total_num) (((_double)(num)) / ((_double)(total_num)))
// Float -> Integer (Round)
#define E3D_F2I_ROUND(x) ((_int)(((_float)(x)) > 0.0f ? (_float)(x) + 0.5f : (_float)(x)-0.5f))

// Buffer Offset
#define E3D_BUFFER_OFFSET(i) ((_byte*)_null + (i))
// This macro does basically the same thing as offsetof defined in stddef.h, 999 is a specific number to ignore the compiler warning
#define E3D_OFFSET_OF(s, m) ((size_t)(&reinterpret_cast<s*>(999)->m) - 999)

// If x isn't DWORD aligned, this will evaluate to next highest DWORD boundary, otherwise evaluates to x
#define E3D_ALIGN_UP32(x) ((((_dword)(x)) + 3) & 0xFFFFFFFC)

// Color Conversion
#define E3D_R5G6B5(r, g, b) (((((r) >> 3) & 0x1F) << 11) | ((((g) >> 2) & 0x3F) << 5) | (((b) >> 3) & 0x1F))
#define E3D_R5G5B5A1(a, r, g, b) (((((r) >> 3) & 0x1F) << 11) | ((((g) >> 3) & 0x1F) << 6) | ((((b) >> 3) & 0x1F) << 1) | (((a) ? 1 : 0)))
#define E3D_R4G4B4A4(a, r, g, b) (((((r) >> 4) & 0x0F) << 12) | ((((g) >> 4) & 0x0F) << 8) | ((((b) >> 4) & 0x0F) << 4) | (((a) >> 4) & 0x0F))
#define E3D_A8G8(a, r, g, b) ((((a)&0xFF) << 8) | ((((r) + (g) + (b)) / 3) & 0xFF))

// Is ptr within the range: [base, base+size]
#define E3D_PTR_IN_RANGE(ptr, base, size) (((_dword)(ptr) >= (_dword)(base)) && ((_dword)(ptr) < ((_dword)(base) + (_dword)(size))))

// Compare two value
#define E3D_COMPARE(f1, f2) \
	if ((f1) != (f2)) return ((f1) < (f2) ? -1 : 1)
#define E3D_COMPARE_BIG(f1, f2) \
	if ((f1) != (f2)) return ((f1) > (f2) ? _true : _false)
#define E3D_COMPARE_LESS(f1, f2) \
	if ((f1) != (f2)) return ((f1) < (f2) ? _true : _false)

// Convert time interval structure info to integer value
#define E3D_VALUE_TO_TIME(time_val, time)        \
	{                                            \
		time_val.tv_sec = time / 1000;           \
		time_val.tv_usec = (time % 1000) * 1000; \
	}
#define E3D_TIME_TO_DWORD(time) ((_dword)(time.tv_sec * 1000.0 + (time.tv_usec / 1000.0)))
#define E3D_TIME_TO_QWORD(time) ((_qword)(time.tv_sec * 1000.0 + (time.tv_usec / 1000.0)) & 0x00000000FFFFFFFFLL)

// Convert time in milliseconds to seconds
#define E3D_MS_TO_SEC(ms) (_time_t)((ms) / 1000ul)
#define E3D_SEC_TO_MS(s) (_time_t)((s)*1000ul)

// Atom Platform Detection
#if defined(_PLATFORM_WINDOWS_)
#	define _WINDOWS_ATOM_
#elif defined(_PLATFORM_ANDROID_) || defined(_PLATFORM_IOS_)
#	define _GCC_ATOM_
#endif

// Window Atom
#if defined(_WINDOWS_ATOM_)
#	define INTERLOCKED_INC(x) InterlockedIncrement(&x)
#	define INTERLOCKED_DEC(x) InterlockedDecrement(&x)
#	define INTERLOCKED_ADD(x, v) InterlockedExchangeAdd(&x, v)
#	define INTERLOCKED_SUB(x, v) InterlockedExchangeSubtract(&x, v)
#else
#	define INTERLOCKED_INC(x) __sync_add_and_fetch(&x, 1)
#	define INTERLOCKED_DEC(x) __sync_sub_and_fetch(&x, 1)
#	define INTERLOCKED_ADD(x, v) __sync_add_and_fetch(&x, v)
#	define INTERLOCKED_SUB(x, v) __sync_sub_and_fetch(&x, v)
#endif

//!	Memory operations.
#define E3D_MEM_SET(desbuffer, value, length) memset(desbuffer, value, length)
#define E3D_MEM_CMP(buffer1, buffer2, length) memcmp(buffer1, buffer2, length)
#define E3D_MEM_CPY(desbuffer, srcbuffer, length) memcpy(desbuffer, srcbuffer, length)
#define E3D_MEM_MOVE(desbuffer, srcbuffer, length) memmove(desbuffer, srcbuffer, length)

// Character operations.
#define E3D_TO_LOWER(c) tolower(c)
#define E3D_TO_UPPER(c) toupper(c)

// Here we make sure the 'wchar_t' is 2 bytes
#ifdef _DEBUG
E3D_STATIC_ASSERT(sizeof(wchar_t) == 2, "We use UTF-16 as wchar_t, not UTF-32");
#endif

// The memory operations
#ifndef _USE_STANDARD_MEM_OPERATOR_

#	ifdef PLATFORM_WIN

#		ifndef _USE_STANDARD_MALLOC_OPERATOR_
#			define E3D_HEAP_FREE_API _CRTNOALIAS
#			define E3D_HEAP_ALLOC_API _CRTNOALIAS _CRTRESTRICT

#			undef realloc
#			undef malloc
#			undef calloc
#			undef free

#			define free e3d_free
#			define calloc e3d_calloc
#			define malloc e3d_malloc
#			define realloc e3d_realloc

#			define e3d_malloc(s) _e3d_malloc(s, __FILE__, __LINE__)
#			define e3d_calloc(n, s) _e3d_calloc(n, s, __FILE__, __LINE__)
#			define e3d_realloc(p, s) _e3d_realloc(p, s, __FILE__, __LINE__)
#			define e3d_free(p) _e3d_free(p, __FILE__, __LINE__)

// Overload Malloc And Free Operations
#			ifdef _cplusplus
extern "C" {
#			endif
void _e3d_free(void* pointer, const char* filename, int linenumber);
void* _e3d_malloc(size_t size, const char* filename, int linenumber);
void* _e3d_calloc(size_t number, size_t size, const char* filename, int linenumber);
void* _e3d_realloc(void* pointer, size_t size, const char* filename, int linenumber);
#			ifdef _cplusplus
}
#			endif
#		endif

#	endif // _PLATFORM_WINDOWS_

#	ifndef _DISABLE_OVERLOAD_NEW_DELETE
// Overload New And Delete Operations
void* operator new(size_t size);
void* operator new(size_t size, const char* filename, int linenumber);
void* operator new[](size_t size);
void* operator new[](size_t size, const char* filename, int linenumber);
void operator delete(void* pointer);
void operator delete(void* pointer, const char* filename, int linenumber);
void operator delete[](void* pointer);
void operator delete[](void* pointer, const char* filename, int linenumber);

#		define new new (__FILE__, __LINE__)
#	endif // _DISABLE_OVERLOAD_NEW_DELETE

#endif // _USE_STANDARD_MEM_OPERATOR_

// Turn off STL debug iterators in release build
#ifndef _DEBUG
#	define _SECURE_SCL 0
#endif
