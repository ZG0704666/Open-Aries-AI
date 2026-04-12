cmake_minimum_required(VERSION 3.20)
project(OpenAriesAI VERSION 1.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(aries_agent aries_agent.cpp)

if (WIN32)
    target_link_libraries(aries_agent PRIVATE
        gdiplus
        gdi32
        ws2_32
        crypt32
        wininet
        winhttp
    )
endif()

target_compile_definitions(aries_agent PRIVATE
    ARIES_PROJECT_VERSION="${PROJECT_VERSION}"
)
