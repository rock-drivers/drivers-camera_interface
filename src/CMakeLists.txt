set(CAM_HDRS
    CamInterface.h
    AutoWhiteBalance.h
    BrightnessIndicator.h
    ExposureController.h
    )

set(CAM_SRCS
    CamInterface.cpp
    BrightnessIndicator.cpp
    ExposureController.cpp
    )

add_library(${PROJECT_NAME} SHARED ${CAM_SRCS})

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${OPENCV_LIBRARIES})

 install(TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION bin
		LIBRARY DESTINATION lib
    )
