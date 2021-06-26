/**
 * @file macros.h
 * @author zopenge (zopenge@126.com)
 * @brief The macros for WIN platform.
 * @version 0.1
 * @date 2021-06-26
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#pragma once

// Undef some macros from 'windows.h' file to ignore the 'A' and 'W' suffix name
#undef CreateFont
#undef CreateFile
#undef CreateProcess
#undef CreateWindow
#undef CompareString
#undef CopyFile
#undef DeleteFile
#undef DrawText
#undef EnumResourceNames
#undef EncryptFile
#undef FindResource
#undef GetCurrentDirectory
#undef GetTempFileName
#undef GetFileVersionInfo
#undef GetFileVersionInfoSize
#undef GetModuleHandle
#undef GetModuleFileName
#undef GetObject
#undef GetWindowText
#undef LoadCursorFromFile
#undef LoadLibrary
#undef LoadImage
#undef MoveFile
#undef MessageBox
#undef OutputDebugString
#undef PostMessage
#undef PlaySound
#undef RegisterClass
#undef SendMessage
#undef SetCurrentDirectory
#undef GetCurrentDirectory
#undef UpdateResource
#undef UnloadImage
#undef WriteConsole
#undef WaitNamedPipe
#undef RegisterClass