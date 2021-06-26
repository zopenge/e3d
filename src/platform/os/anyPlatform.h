/**
 * @file anyPlatform.h
 * @author zopenge (zopenge@126.com)
 * @brief The system functions for any platform.
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

namespace E3D {

/**
 * @brief 
 * anyPlatform
 */
class anyPlatform {

public:
	/**
	 * @brief Initialize.
	 * 
	 * @return _boolean 
	 */
	static _boolean Initialize();

	/**
	 * @brief Finalize.
	 * 
	 * @return _void 
	 */
	static _void Finalize();
};

} // namespace EGE