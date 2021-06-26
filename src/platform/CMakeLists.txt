project(platform)

add_library(platform PlatformPCH.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_SOURCE_DIR}/include;${ROOT_DIR}/libs
)

include(${ROOT_DIR}/cmake/macros.cmake)

# Tell compiler to use C++20 features. The code doesn't actually use any of them.
target_compile_features(platform PUBLIC cxx_std_20)