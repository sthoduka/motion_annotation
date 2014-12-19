Motion Annotation
================

Logs selected contours (where motion is present) frame by frame through user interaction
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
- To select contours for a displayed frame, press 'y'
    - Click on the new window to select the points of your contour
    - Press 'x' to close the contour
    - Press 'y' if you're satisfied or any other key to restart
- To add another contour to the same frame, press 'c'
    - Same procedure as for the previous contour
- To skip the frame, press any key except 'y', 'x' or 'c'
- To quit, press 'x'
