cmake_minimum_required(VERSION 3.8)
project(AAL_OpenGL_Visualization)

#find_package(OpenGL REQUIRED)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenGL REQUIRED)

set(SOURCE_FILES main.cpp Scene.cpp)
set(HEADER_FILES Scene.h
        include/GL/freeglut.h include/GL/freeglut_ext.h include/GL/freeglut_std.h include/GL/glut.h CuboidContainer.cpp CuboidContainer.h Cuboid.cpp Cuboid.h FileParser.cpp FileParser.h)
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

add_executable(AAL_OpenGL_Visualization ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(AAL_OpenGL_Visualization PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/lib/>
        )

link_directories(${OPENGL_gl_LIBRARY})

target_link_libraries(AAL_OpenGL_Visualization
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfreeglut.a
        ${CMAKE_CURRENT_SOURCE_DIR}/lib/libfreeglut_static.a
        ${OPENGL_gl_LIBRARY}
         GLU32.lib)


