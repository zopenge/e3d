/**
 * @file e3d_const.h
 * @author zopenge (zopenge@126.com)
 * @brief The const and structure of E3D.
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

namespace E3D {

/**
 * @brief The seek flag.
 * 
 */
enum class SeekFlag {
	/**
	 * @brief Seek from beginning.
	 * 
	 */
	Begin,
	/**
	 * @brief Seek from current position.
	 * 
	 */
	Current,
	/**
	 * @brief Seek from end plus "offset".
	 * 
	 */
	End,
};

/**
 * @brief The encode type.
 * 
 */
enum class Encoding {
	/**
	 * @brief Unknown encoding.
	 * 
	 */
	Unknown,
	/**
	 * @brief ANSI encoding.
	 * 
	 */
	Ansi,
	/**
	 * @brief UTF-8 encoding.
	 * 7
	 */
	Utf8,
	/**
	 * @brief UTF-16 encoding.
	 * 
	 */
	Utf16,
};

/**
 * @brief The endian type.
 * 
 */
enum class Endian {
	/**
	 * @brief Unknown endian.
	 * 
	 */
	Unknown,
	/**
	 * @brief Little endian.
	 * 
	 */
	Little,
	/**
	 * @brief Big endian.
	 * 
	 */
	Big,
};

/**
 * @brief The domain family type
 * 
 */
enum class DomainFamilyType {
	INET,
	INET6,
};

/**
 * @brief The socket type
 * 
 */
enum class SocketType {
	Stream,
	Dgram,
	Raw,
	SeqPacket,
};

/**
 * @brief The file attribute
 * 
 */
namespace FileAttribute {
static unsigned int ReadOnly = 0x00000001;
static unsigned int Hidden = 0x00000002;
static unsigned int System = 0x00000004;
static unsigned int Directory = 0x00000010;
static unsigned int Archive = 0x00000020;
static unsigned int Device = 0x00000040;
static unsigned int Normal = 0x00000080;
static unsigned int Temporary = 0x00000100;
static unsigned int SparseFile = 0x00000200;
static unsigned int ReparsePoint = 0x00000400;
static unsigned int Compressed = 0x00000800;
static unsigned int Offline = 0x00001000;
static unsigned int NotContentIndexed = 0x00002000;
static unsigned int Encrypted = 0x00004000;
static unsigned int IntegrityStream = 0x00008000;
}; // namespace FileAttribute

} // namespace E3D