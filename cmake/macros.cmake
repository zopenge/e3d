# GLOBAL

# set(CMAKE_UNITY_BUILD ON)

set(ROOT_DIR ${CMAKE_SOURCE_DIR})

# PLATFORM_NAME

set(PLATFORM_NAME "WIN") #['WIN', 'IOS', 'ANDROID']
message("Building on '${PLATFORM_NAME}' platform ...")

if (PLATFORM_NAME STREQUAL "WIN")
    add_definitions(-DPLATFORM_WIN)
elseif (PLATFORM_NAME STREQUAL "IOS")
    add_definitions(-DPLATFORM_IOS)
elseif (PLATFORM_NAME STREQUAL "ANDROID")
    add_definitions(-DPLATFORM_ANDROID)
else()
    message(FATAL_ERROR "The platform name '${PLATFORM_NAME}' is unknown")
endif()

# THREAD

set(THREAD "pthread") #['system', 'pthread']
message("Enable '${THREAD}' thread mode ...")

if (THREAD STREQUAL "pthread")
    add_definitions(-DUSE_PTHREAD)
    if (PLATFORM_NAME STREQUAL "WIN")
        add_definitions(-DHAVE_STRUCT_TIMESPEC) # to fix error C2011: “timespec”:“struct” compile error with windows SDK 'time.h'
    endif()
endif()