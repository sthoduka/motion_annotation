cmake_minimum_required(VERSION 2.8)

project(motion_annotation)

find_package(OpenCV REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_executable(motion_annotation
    src/main.cpp
    src/video_interaction.cpp
    src/contour_selection.cpp
    src/motion_logger.cpp
)

include_directories(motion_annotation
    include/
    ${OpenCV_INCLUDE_DIRS}
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(motion_annotation
    ${OpenCV_LIBRARIES}
    ${Boost_LIBRARIES}
)
