cmake_minimum_required(VERSION 3.19)

project(
    console_colors

    LANGUAGES
    "C" "CXX"
)

set(CONSOLE_COLORS_COPY_POST_BUILD OFF CACHE BOOL "When enabled, copies the output binary to the specified directory." OFF)
set(CONSOLE_COLORS_COPY_DIRECTORY "" CACHE STRING "The directory to copy the binary to.")

set(
    SRC

    src/console_colors.cc src/console_colors.h

    src/GarrysMod/Lua/Interface.h
    src/GarrysMod/Lua/LuaBase.h
    src/GarrysMod/Lua/SourceCompat.h
    src/GarrysMod/Lua/Types.h
    src/GarrysMod/Lua/UserData.h
)

add_library(
    console_colors

    SHARED

    ${SRC}
)

target_compile_definitions(
    console_colors

    PRIVATE CONSOLE_COLORS_DEBUG
)

if (WIN32)
    if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
        set(CONSOLE_COLORS_SUFFIX "win64")
    else ()
        set(CONSOLE_COLORS_SUFFIX "win32")
    endif ()
else ()
    message(FATAL_ERROR "Invalid platform, only Windows is supported.")
endif ()

set_target_properties(console_colors PROPERTIES SUFFIX "_${CONSOLE_COLORS_SUFFIX}.dll" PREFIX "gmsv_")

if (CONSOLE_COLORS_COPY_POST_BUILD)
    add_custom_command(
        TARGET console_colors
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:console_colors> ${CONSOLE_COLORS_COPY_DIRECTORY}
    )
endif ()