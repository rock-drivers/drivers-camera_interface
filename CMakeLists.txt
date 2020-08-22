# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.

cmake_minimum_required(VERSION 3.9)
project(camera_interface
        VERSION 1.0
        DESCRIPTION "Base interface for other camera drivers in Rock")
find_package(Rock)
rock_init()

option(OPENCV4 "Whether OpenCV 4 or later should be used" OFF)
if (OPENCV4)
    set(opencv_pkgconfig_suffix 4)
endif()

rock_standard_layout()
set(PROJECT_DESCRIPTION "Dummy project just to show how the infrastructure is working")
