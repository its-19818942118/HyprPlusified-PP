cmake_minimum_required (
    VERSION 3.10
)

project ( hyprScripts++
    VERSION 0.1
    LANGUAGES CXX
)

set ( CMAKE_STOP_ON_ERROR 1 )
set ( CMAKE_CXX_STANDARD 26 )
set ( CMAKE_CXX_STANDARD_REQUIRED true )
# set(CMAKE_CXX_CLANG_TIDY "clang-tidy;-checks=*,-llvm-header-guard,-clang-analyzer-*")


option ( FORCE_COLORED_OUTPUT
    "Always produce ANSI-colored output (GNU/Clang only)." TRUE
)

if ( ${FORCE_COLORED_OUTPUT} )
    if ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" )
        add_compile_options ( -fdiagnostics-color=always )
    elseif ( "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" )
        add_compile_options ( -fcolor-diagnostics )
    endif ( )
endif ( )

find_package ( fmt REQUIRED )

add_compile_options (
    -O3
    -Oz
    -Os
    -Ofast
    -fno-signed-zeros
    -fno-trapping-math
    -fcx-limited-range
    # -Wall
    -flto
    # -Wextra
    # -Werror
    -ffast-math
    -march=native
    -mtune=native
    -flto=jobserver
    # -Wunused-result
    # -Wstrict-prototypes
    -fdiagnostics-color=always
    -DNDEBUG
)

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "$ENV{HOME}/.local/share/bin/"
)

# include_directories ( include/
#     include/MonitorsMangler/
# )

# set ( SOURCES_MON_MANGLER++
#     src/monitorsMangler.cpp
#     include/MonitorsMangler/src/mangler.cpp
#     include/MonitorsMangler/src/argsParser.cpp
# )

# add_executable ( MonitorsMangler++
#     ${SOURCES_MON_MANGLER++}
# )

# target_link_libraries ( MonitorsMangler++
#     PRIVATE
#     fmt::fmt
# )

# add_executable ( Parser++
#     src/argsIterator.cpp
# )

# target_link_libraries ( Parser++
#     PRIVATE
#     fmt::fmt
# )

add_executable ( VolumeControl
    # src/volumeControl_im.cpp
    src/volumeControl.cpp
)

target_link_libraries ( VolumeControl
    PRIVATE
    fmt::fmt
)


# add_executable ( PrintScr src/prtsc.cpp )

# add_executable ( specialWorkspaces src/specialWorkspaces.cpp )


# add_executable ( a.out src/test.cpp ) 
# add_executable ( a.out src/greetings.cpp ) 
# add_executable ( a.out src/t2.cpp ) 

# add_executable ( a.out src/slsctty-utf8.cpp )
# add_executable ( VolumeControl++ src/volumeControl_im.cpp )

# add_executable ( a.out src/demo.cpp )
# add_executable ( a.out src/tqoutes.cpp )

# add_executable ( a.out src/warda.cpp )

# add_executable ( a.out src/cli.cpp )
