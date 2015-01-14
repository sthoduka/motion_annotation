Motion Annotation
================

Logs selected bounding boxes (where motion is present) frame by frame through user interaction
### Clone
    git clone git@github.com:sthoduka/motion_annotation.git

### Build
    cd motion_annotation
    mkdir build
    cd build
    cmake ..
    make

### Run
    ./motion_annotation path/to/video/file path/to/log/file

### Usage
- To select bounding boxes for a displayed frame, press 'y'
    - Click two points on the new window to define the bounding box where there is motion (top left, bottom right)
    - Press 'y' if you're satisfied or any other key to restart
- To add another box to the same frame, press 'c'
    - Same procedure as for the previous box
- To skip the frame, press any key except 'y', 'x' or 'c'
- To quit, press 'x'
