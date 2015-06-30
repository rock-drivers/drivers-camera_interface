# CMakeLists.txt has to be located in the project folder and cmake has to be
# executed from 'project/build' with 'cmake ../'.
cmake_minimum_required(VERSION 2.7)
find_package(Rock)
rock_init(camera_interface 1.0)
rock_standard_layout()
set(PROJECT_DESCRIPTION "Dummy project just to show how the infrastructure is working")
