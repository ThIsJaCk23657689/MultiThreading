cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# 設定變數
set(MY_PROJECT "Multi-Threading OpenMP")
set(MY_EXECUTABLE "multi_threading_openmp")

# 定義專案屬性
project(${MY_PROJECT})

# 建立二進位執行檔目標
add_executable(${MY_EXECUTABLE} main.cpp)

# 設定目標屬性: C++ 語言
set_target_properties(${MY_EXECUTABLE}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSION OFF
)

# 顯示相關資訊
message(STATUS)
message(STATUS "========== Build Information ==========")
message(STATUS "\tHost System Name:         ${CMAKE_HOST_SYSTEM_NAME}")
message(STATUS "\tHost System Version:      ${CMAKE_HOST_SYSTEM_VERSION}")
message(STATUS "\tHost System Processor:    ${CMAKE_HOST_SYSTEM_PROCESSOR}")
message(STATUS)
message(STATUS "\tC++ Compiler:             ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "\tC++ Compiler Path:        ${CMAKE_CXX_COMPILER}")
message(STATUS)

if (MSVC)
    message(STATUS "\tMSVC Version:             ${MSVC_VERSION}")
    message(STATUS "\tMSVC Toolset:             ${MSVC_TOOLSET_VERSION}")
endif ()
message(STATUS)

message(STATUS "\tVCPKG Path:               ${CMAKE_TOOLCHAIN_FILE}")
message(STATUS)
message(STATUS "========================================")

message(STATUS)

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    target_link_libraries(${MY_EXECUTABLE} PUBLIC OpenMP::OpenMP_CXX)
endif()

# 針對不同的編譯器有不同的引入設定
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9)
        target_link_libraries(${MY_EXECUTABLE} PRIVATE stdc++fs) # C++ filesystem
    endif ()
endif ()