# OpenCV Tutorials
Me doing tutorials from [OpenCV Tutorials](https://docs.opencv.org/4.x/d9/df8/tutorial_root.html) site.


## How to start new tutorial and how to build
1. Copy skeleton directory to a new one, for example: `cp -r _skeleton/ tut_01/`
2. Go to new direcrory `cd tut_01/`, change source file `source.cpp`
3. Go to build directory and cmake, then make and run
```
cd build/
cmake ..
make
./app
```

## Tutorial list
- Tutorial 01 `tut_01` [Getting Started with Images](https://docs.opencv.org/4.x/db/deb/tutorial_display_image.html)

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
