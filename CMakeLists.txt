cmake_minimum_required(VERSION 2.8)

project(motion_annotation)

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_executable(motion_annotation_video
    src/main.cpp
    src/video_interaction.cpp
    src/contour_selection.cpp
    src/box_selection.cpp
    src/motion_logger.cpp
)
add_executable(motion_annotation_image
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

include_directories(
    include/
    ${OpenCV_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(motion_annotation_video
    ${OpenCV_LIBRARIES}
    ${Boost_LIBRARIES}
)

target_link_libraries(motion_annotation_image
    ${OpenCV_LIBRARIES}
    ${Boost_LIBRARIES}
)

target_link_libraries(inspector
    ${OpenCV_LIBRARIES}
    ${Boost_LIBRARIES}
)
