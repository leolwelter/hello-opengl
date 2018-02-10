cmake_minimum_required(VERSION 3.9)
project(textgame)

set(CMAKE_CXX_STANDARD 11)

# openGL
find_package(OpenGL REQUIRED)
if (NOT OPENGL_FOUND)
    message("ERROR: OpenGL not found")
endif (NOT OPENGL_FOUND)


# Source files
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(LIB_DIR "/usr/local/lib")
set(SOURCES ${SRC_DIR}/main.cpp ${SRC_DIR}/glad.c src/Creature.cpp src/Creature.h src/Game.cpp src/Game.h src/GameObject.h src/GameObject.cpp)

include_directories(
        /home/leo/work/include/glad
        /home/leo/work/include/
)
link_directories(
        /home/leo/work/lib/
        /usr/lib/
        /usr/local/lib
)

# these are precious babies and can not be in the wrong order
find_library(
        dl
        Xinerama
        Xcursor
        GL
        GLU
        glfw3
        X11
        Xxf86vm
        Xrandr
        pthread
        Xi
        rt
        m
        Xext
        Xrender
        Xfixes
        xcb
        Xau
        Xdmcp
)
set(GL_LIBS
        Xi
        glfw3
        rt
        m
        dl
        Xrandr
        Xinerama
        Xxf86vm
        Xext
        Xcursor
        Xrender
        Xfixes
        X11
        pthread
        xcb
        Xau
        Xdmcp
)

# compile target from sources
add_executable(open_gl_game ${SOURCES})

# link the libraries above to the compiled target
target_link_libraries(open_gl_game ${GL_LIBS})