# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.

cmake_minimum_required(VERSION 3.9)
project(camera_interface
        VERSION 1.0
        DESCRIPTION "Base interface for other camera drivers in Rock")
find_package(Rock)
rock_init()

rock_opencv_autodetect(OPENCV_PACKAGE)
rock_standard_layout()
