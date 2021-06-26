/**
 * @file headers.h
 * @author zopenge (zopenge@126.com)
 * @brief The headers for WIN platform.
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

// Exclude rarely-used stuff from Windows headers
#ifndef WIN32_LEAN_AND_MEAN
#	define WIN32_LEAN_AND_MEAN
#endif

// We initialize GUID in static library way
#ifndef INITGUID
#	define INITGUID
#endif

// The windows base header file
#include <windows.h>
// The IP header file
#include <IPHlpApi.h>

//#if !defined(strdup)
//	#define strdup _strdup
//#endif
