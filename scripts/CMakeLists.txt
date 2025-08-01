cmake_minimum_required (
    VERSION 3.10
)

project ( hyprScripts++
    VERSION 0.1
    LANGUAGES CXX
)

set ( CMAKE_CXX_STANDARD 26 )
set ( CMAKE_CXX_STANDARD_REQUIRED true )

add_compile_options (
    -O3
    -march=native
    -mtune=native
    -flto
    -static
    -ffast-math
    -flto=jobserver
)

set ( CMAKE_RUNTIME_OUTPUT_DIRECTORY
    "$ENV{HOME}/.local/share/bin/"
)

include_directories (
    include/MonitorsMangler/
)

set ( SOURCES_MON_MANGLER++
    src/monitorsMangler.cpp
    include/MonitorsMangler/src/mangle2.cpp
    include/MonitorsMangler/src/mangle3.cpp
)


# add_executable ( VolumeControl
#     src/volumeControl.cpp
# )

# add_executable ( VolumeControl++
#     src/volumeControl_im.cpp
# )

# add_executable ( HyprResize
#     src/hyprResize.cpp
# )

add_executable ( MonitorsMangler++
    ${SOURCES_MON_MANGLER++}
)

# add_executable ( MenuFinder
#     src/menuFinder.cpp
# )

# add_executable ( Config
#     src/config.cpp
# )

# add_executable ( Cli
#     src/cli.cpp
# )

# add_executable ( Dencoder
#     src/dencoder.cpp
# )

# add_executable ( MouseKeys
#     src/mousekeys.cpp
# )
