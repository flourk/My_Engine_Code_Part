cmake_minimum_required(VERSION 3.10)

project(Assimp_Learn01)

set(Project_Dir ${CMAKE_SOURCE_DIR})
set(Project_Build_Dir ${CMAKE_BINARY_DIR})
set(Project_ThirdParty_Dir ${Project_Dir}/3rdParty)

set(Build_Editor OFF)
set(Build_Runtime ON)

include_directories(${Project_ThirdParty_Dir}/Assimp/include)
link_directories(${Project_ThirdParty_Dir}/Assimp/lib)

include_directories(${Project_ThirdParty_Dir}/glfw3/include)
link_directories(${Project_ThirdParty_Dir}/glfw3/lib)

include_directories(${Project_ThirdParty_Dir}/glew/include)
link_directories(${Project_ThirdParty_Dir}/glew/lib)

include_directories(${Project_ThirdParty_Dir}/vectormath/include)
add_definitions(-DVECTORMATH_FORCE_SCALAR_MODE)

include_directories(${Project_ThirdParty_Dir}/glm/include)
add_definitions(-DGLM_ENABLE_EXPERIMENTAL)

include_directories(${Project_ThirdParty_Dir}/stb/include)
include_directories(${Project_ThirdParty_Dir}/flex/include)


find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

include_directories(${Project_Dir})

set(SRC_LISTS
scene/camera.cpp
scene/model.cpp
scene/scene_node.cpp
scene/skinned_model.cpp
scene/light.cpp
scene/light_manager.cpp
scene/app.cpp

render/mesh.cpp
render/shader.cpp
render/renderer.cpp
render/texture.cpp
render/technique.cpp
render/pass.cpp
render/device/gl_helper.cpp
render/material.cpp
render/parameter.cpp
render/variant.cpp

resource/resource_mgr.cpp
resource/animation.cpp
resource/assimp_to_glm.cpp
resource/image.cpp

resource/loader/image_loader.cpp
resource/loader/resource_loader.cpp
resource/loader/texture_loader.cpp


core/log.cpp
core/timer.cpp

filesystem/path.cpp

shader_parser/lexer.c
shader_parser/parser.c
shader_parser/ast.c
shader_parser/shader_compiler.cpp
)

LIST(APPEND SRC_LISTS
    thread/windows/thread_utils_win.cpp
)

if(Build_Runtime)

    ## main
    # add_executable(main main.cpp ${SRC_LISTS})
    # target_link_libraries(main assimp-vc140-mt glfw3 glew32 ${OPENGL_LIBRARY})

    # add_custom_command(TARGET main
    # POST_BUILD
    # COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/Debug/data
    # COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/Debug/data
    # COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/dll ${CMAKE_BINARY_DIR}/Debug
    # )

    # # sample1
    # add_executable(sample1 samples/sample1.cpp ${SRC_LISTS})
    # target_link_libraries(sample1 assimp-vc140-mt glfw3 glew32 ${OPENGL_LIBRARY})

    # add_custom_command(TARGET sample1
    # POST_BUILD
    # COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/Debug/data
    # COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/Debug/data
    # COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/dll ${CMAKE_BINARY_DIR}/Debug
    # )

    # sample2
    add_executable(sample2 samples/sample2.cpp ${SRC_LISTS})
    target_link_libraries(sample2 assimp-vc140-mt glfw3 glew32 ${OPENGL_LIBRARY})

    add_custom_command(TARGET sample2
    POST_BUILD
    COMMAND cmake -E make_directory ${CMAKE_BINARY_DIR}/Debug/data
    COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/data ${CMAKE_BINARY_DIR}/Debug/data
    COMMAND cmake -E copy_directory ${CMAKE_SOURCE_DIR}/dll ${CMAKE_BINARY_DIR}/Debug
    )

endif()

#### editor

if(Build_Editor)
    SET(CMAKE_PREFIX_PATH D:/Development/Qt/Qt5.11.3/5.11.3/msvc2015/lib/cmake)

    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    find_package(Qt5Widgets CONFIG REQUIRED)

    set(EDITOR_SRC_LISTS
        editor/mainwindow.ui
        editor/mainwindow.cpp
        editor/openglwidget.cpp
        editor/treewidget.cpp
    )
    add_definitions(-DEditor)
    add_executable(yueditor  editor/editor_main.cpp ${EDITOR_SRC_LISTS} ${SRC_LISTS})
    target_link_libraries(yueditor Qt5::Widgets glew32 assimp-vc140-mt ${OPENGL_LIBRARY})
endif()