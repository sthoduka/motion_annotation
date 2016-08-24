cmake_minimum_required(VERSION 2.8)

project(motion_annotation)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_executable(motion_annotation
    src/image_main.cpp
    src/video_interaction.cpp
    src/contour_selection.cpp
    src/box_selection.cpp
    src/motion_logger.cpp
)
add_executable(inspector
    src/inspector.cpp
    src/video_interaction.cpp
    src/contour_selection.cpp
    src/box_selection.cpp
    src/motion_logger.cpp
)

include_directories(motion_annotation
    include/
    ${OpenCV_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

#...: gnu++0x
if(CMAKE_COMPILER_IS_GNUCXX)
    execute_process(COMMAND ${CMAKE_C_COMPILER} -dumpversion OUTPUT_VARIABLE GCC_VERSION)
    if(GCC_VERSION VERSION_GREATER 4.6 OR GCC_VERSION VERSION_EQUAL 4.6)
        add_definitions(-std=gnu++0x)
    else()
        message(SEND_ERROR "You need GCC version 4.6 or greater to compile this package.")
    endif()
endif()

target_link_libraries(motion_annotation
    ${OpenCV_LIBRARIES}
    ${Boost_LIBRARIES}
)

target_link_libraries(inspector
    ${OpenCV_LIBRARIES}
    ${Boost_LIBRARIES}
)
