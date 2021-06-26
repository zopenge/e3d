/**
 * @file networks.h
 * @author zopenge (zopenge@126.com)
 * @brief The networks for ios platforms.
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <signal.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#ifndef SOCKET
#	define SOCKET int
#endif

#ifndef MSG_NOSIGNAL
#	define MSG_NOSIGNAL 0
#endif

#ifndef INVALID_SOCKET
#	define INVALID_SOCKET (SOCKET)(~0)
#endif

#define closesocket close
#define ioctlsocket ioctl

//! The socket handle
typedef SOCKET _socket;