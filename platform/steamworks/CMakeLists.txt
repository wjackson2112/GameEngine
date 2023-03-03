# Make Steamworks SDK
project(steamworks_sdk)

add_library(steamworks_sdk INTERFACE)

set(STEAMWORKS_SDK_DIR $ENV{STEAMWORKS_SDK})

set(STEAMWORKS_INCLUDE_DIR "${STEAMWORKS_SDK_DIR}/public/steam")
set(STEAMWORKS_BINARY_DIR "${STEAMWORKS_SDK_DIR}/redistributable_bin/win64/steam_api64.lib")
set(STEAMWORKS_SHARED_DIR "${STEAMWORKS_SDK_DIR}/redistributable_bin/win64/steam_api64.dll")

target_include_directories(steamworks_sdk INTERFACE ${STEAMWORKS_INCLUDE_DIR})

target_link_libraries(steamworks_sdk INTERFACE ${STEAMWORKS_BINARY_DIR})

target_link_libraries(GameEngine steamworks_sdk)

# Make local sources
set(SOURCES
    Steamworks.cpp)

target_include_directories(GameEngine
        PUBLIC
        include)

target_sources(GameEngine
        PRIVATE
        ${SOURCES})