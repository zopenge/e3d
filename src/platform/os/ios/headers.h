/**
 * @file headers.h
 * @author zopenge (zopenge@126.com)
 * @brief The headers for IOS platform.
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// So strange, the XCODE compile report this function is not implement yet
inline void __eprintf(const char* fmt, const char* file, unsigned line, const char* e) {
	fprintf(stderr, fmt, file, line, e);
}