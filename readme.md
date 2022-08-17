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
* [The Core Functionality](https://docs.opencv.org/4.x/de/d7a/tutorial_table_of_content_core.html)

  - Tutorial 01 `tut_01` [Getting Started with Images](https://docs.opencv.org/4.x/db/deb/tutorial_display_image.html)
  - Tutorial 02 `tut_02` [How to scan images, lookup tables and time measurement with OpenCV](https://docs.opencv.org/4.x/db/da5/tutorial_how_to_scan_images.html)
    * [Sample source code](https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/core/how_to_scan_images/how_to_scan_images.cpp)
  - Tutorial 03 `tut_03` [Mask operations on matrices](https://docs.opencv.org/4.x/d7/d37/tutorial_mat_mask_operations.html)
    * NOTE(ASz): maybe try doing your own version here, for comparison
  - Tutorial 04 `tut_04` [Operations with images](https://docs.opencv.org/4.x/d5/d98/tutorial_mat_operations.html)
    * [Sample source code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/core/mat_operations/mat_operations.cpp)
    * NOTE: Use `cv::imdecode` and `cv::imencode` to read and write an image from/to memory rather than a file.
  - Tutorial 05 `tut_05` [Adding (blending) two images using OpenCV](https://docs.opencv.org/4.x/d5/dc4/tutorial_adding_images.html)
    * [Sample source code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/core/AddingImages/AddingImages.cpp)
  - Tutorial 06 `tut_06` [Changing the contrast and brightness of an image!](https://docs.opencv.org/4.x/d3/dc1/tutorial_basic_linear_transform.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/ImgProc/BasicLinearTransforms.cpp)
    * Tutorial 06a `tut_06a` [Sample Source Code: Contrast and Brightness Adjustments, Gamma Correction](https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/ImgProc/changing_contrast_brightness_image/changing_contrast_brightness_image.cpp)
  - Tutorial 07 `tut_07` [Discrete Fourier Transform](https://docs.opencv.org/4.x/d8/d01/tutorial_discrete_fourier_transform.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/core/discrete_fourier_transform/discrete_fourier_transform.cpp)
    * Tutorial 07a `tut_07a` Practice based on **Result** paragraph from Tutorial 07 (using two text images)
  - Tutorial 08 `tut_08` [File Input and Output using XML and YAML files](https://docs.opencv.org/4.x/dd/d74/tutorial_file_input_output_with_xml_yml.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/master/samples/cpp/tutorial_code/core/file_input_output/file_input_output.cpp)
  - Tutorial 09 `tut_09` [How to use the OpenCV parallel_for_ to parallelize your code](https://docs.opencv.org/4.x/dc/ddf/tutorial_how_to_use_OpenCV_parallel_for_new.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/core/how_to_use_OpenCV_parallel_for_/how_to_use_OpenCV_parallel_for_new.cpp)
  - Tutorial 10 `tut_10` [Vectorizing your code using Universal Intrinsics](https://docs.opencv.org/4.x/d6/dd1/tutorial_univ_intrin.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/core/univ_intrin/univ_intrin.cpp)

* [Image Processing (imgproc module)](https://docs.opencv.org/4.x/d7/da8/tutorial_table_of_content_imgproc.html)
  
  - Tutorial 11 `tut_11` [Basic Drawing](https://docs.opencv.org/4.x/d3/d96/tutorial_basic_geometric_drawing.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgProc/basic_drawing/Drawing_1.cpp)
  - Tutorial 12 `tut_12` [Random generator and text with OpenCV](https://docs.opencv.org/4.x/df/d61/tutorial_random_generator_and_text.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgProc/basic_drawing/Drawing_2.cpp)
    * Tutorial 12a `tut_12a` Refactoring of `tut_12`
  - Tutorial 13 `tut_13` [Smoothing Images](https://docs.opencv.org/4.x/dc/dd3/tutorial_gausian_median_blur_bilateral_filter.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgProc/Smoothing/Smoothing.cpp)
    * modified to my needs
  - Tutorial 14 `tut_14` [Eroding and Dilating](https://docs.opencv.org/4.x/db/df6/tutorial_erosion_dilatation.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgProc/Morphology_1.cpp)
    * this one required modification, since `cv::createTrackbar` works in a different way now (tutorial is wrong).
  - Tutorial 15 `tut_15` [More Morphology Transformations](https://docs.opencv.org/4.x/d3/dbe/tutorial_opening_closing_hats.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgProc/Morphology_2.cpp)
    * as above, this one required modification, since `cv::createTrackbar` works in a different way now (tutorial is wrong).
  - Tutorial 16 `tut_16` [Hit-or-Miss](https://docs.opencv.org/4.x/db/d06/tutorial_hitOrMiss.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgProc/HitMiss/HitMiss.cpp)
  - Tutorial 17 `tut_17` [Extract horizontal and vertical lines by using morphological operations](https://docs.opencv.org/4.x/d7/da8/tutorial_table_of_content_imgproc.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgProc/morph_lines_detection/Morphology_3.cpp)
  - Tutorial 18 `tut_18`  [Image Pyramids](https://docs.opencv.org/4.x/d4/d1f/tutorial_pyramids.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgProc/Pyramids/Pyramids.cpp)
  - Tutorial 19 `tut_19` [Basic Thresholding Operations](https://docs.opencv.org/4.x/db/d8e/tutorial_threshold.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgProc/Threshold.cpp)
    * as above, this one required modification, since `cv::createTrackbar` works in a different way now (tutorial is wrong).
  - Tutorial 20 `tut_20` [Thresholding Operations using inRange](https://docs.opencv.org/4.x/da/d97/tutorial_threshold_inRange.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgProc/Threshold_inRange.cpp)
  - Tutorial 21 `tut_21` [Making your own linear filters!](https://docs.opencv.org/4.x/d4/dbd/tutorial_filter_2d.html)
    * [Sample Source Code](https://github.com/opencv/opencv/blob/4.x/samples/cpp/tutorial_code/ImgTrans/filter2D_demo.cpp)


## Useful Tips

- `git status -uall`
- Bit Hack: "even floor" `magnitude_image.cols & -2`

## How to build OpenCV 4.5.4-dev
Scratchpad notes version

`sudo apt install libgtk-3-dev pkg-config`

`cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D INSTALL_C_EXAMPLES=ON -D INSTALL_PYTHON_EXAMPLES=ON -D BUILD_EXAMPLES=ON -D WITH_QT=ON -D WITH_GTK=ON -D WITH_OPENGL=ON ../opencv`

After cloning OpenCV into `~/opencv`

`mkdir build && cd build`

`sudo cmake ../opencv`

`make -j2` as many processors as your system has, use `nproc` to tell.
`sudo make install`
`sudo ldconfig`
