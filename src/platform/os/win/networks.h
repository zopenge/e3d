/**
 * @file networks.h
 * @author zopenge (zopenge@126.com)
 * @brief The networks for win platforms.
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <WinSock2.h>
#include <errno.h>

#define MSG_NOSIGNAL 0

//! The socket handle
typedef SOCKET _socket;