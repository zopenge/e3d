project(platform)

add_library(platform PlatformPCH.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${ROOT_DIR}/include;${ROOT_DIR}/libs;${ROOT_DIR}/libs/crt;${ROOT_DIR}/libs/pthread/include
)

target_precompile_headers(platform
  PRIVATE
      PlatformPCH.h
)

include(${ROOT_DIR}/cmake/macros.cmake)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(platform PUBLIC cxx_std_20)