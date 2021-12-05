# OpenCV Tutorials
Me doing tutorials from [OpenCV Tutorials](https://docs.opencv.org/4.x/d9/df8/tutorial_root.html) site.


## How to start new tutorial and how to build
1. Copy skeleton directory to a new one, for example: `cp -r _skeleton/ tut_01/`
2. Go to new direcrory `cd tut_01/`, change source file `source.cpp`
3. (optional) if not present make `build/` directory
4. Go to build directory and cmake, then make and run
```
mkdir build
cd build/
cmake ..
make
./app
```

## Tutorial list
- Tutorial 01 `tut_01` [Getting Started with Images](https://docs.opencv.org/4.x/db/deb/tutorial_display_image.html)
- Tutorial 02 [How to scan images, lookup tables and time measurement with OpenCV](https://docs.opencv.org/4.x/db/da5/tutorial_how_to_scan_images.html)
  * [Full source code](https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/core/how_to_scan_images/how_to_scan_images.cpp)
- Tutorial 03 [Mask operations on matrices](https://docs.opencv.org/4.x/d7/d37/tutorial_mat_mask_operations.html)
  * NOTE(ASz): maybe try doing your own version here, for comparison

## Useful Tips

`git status -uall`

## How to build OpenCV 4.5.4-dev
Scratchpad notes version

Is this really necessary?
`sudo apt install libgtk2.0-dev pkg-config`

This seems to to the job
`sudo apt install libgtk-3-dev`

Probably `PYTHON` stuff isn't really needed, but oh well.
`cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_GTK=ON -D WITH_OPENGL=ON ../opencv`

After cloning OpenCv into `~/opencv`

`mkdir build && cd build` This should have a better name, but oh well.

`sudo cmake ../opencv`

`make -j2` as many processors as your system has, use `nproc` to tell.
`sudo make install`
`sudo ldconfig`
