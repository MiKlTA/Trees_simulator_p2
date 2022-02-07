cmake_minimum_required(VERSION 3.5)

project(MEGA_tree_simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(MEGA_tree_simulator
    
    main.cpp
    
    opengl.h
    window.h
    window.cpp
    rect.h
    rect.cpp
    triangle.h
    triangle.cpp
    circle.h
    circle.cpp
    
    id_object.h
    interpolation.h
    
    simulation_core.h
    simulation_core.cpp
    dna.h
    dna.cpp
    tree.h
    tree.cpp
    tree_part.h
    tree_part_manager.h
    tree_part_manager.cpp
    planet.h
    planet.cpp
    )

include_directories(D:/mingw32_810/LIBS/opencl/source/external/OpenCL-Headers)
include_directories(D:/mingw32_810/LIBS/opencl/source/external/OpenCL-CLHPP/include)
target_link_libraries(
    MEGA_tree_simulator
    D:/mingw32_810/LIBS/opencl/lib/libOpenCL.a
    )
target_link_libraries(MEGA_tree_simulator Cfgmgr32.lib)

include_directories(D:/mingw32_810/LIBS/glew/include)
target_link_libraries(
    MEGA_tree_simulator
    D:/mingw32_810/LIBS/glew/lib/glew32s.lib
    )
target_link_libraries(MEGA_tree_simulator opengl32.a)

include_directories(D:/mingw32_810/LIBS/glfw/source/include)
target_link_libraries(
    MEGA_tree_simulator
    D:/mingw32_810/LIBS/glfw/lib/libglfw3.a
    )

include_directories(D:/mingw32_810/LIBS/glm)
target_link_libraries(
    MEGA_tree_simulator
    D:/mingw32_810/LIBS/glm/lib/libglm_static.a
    )

