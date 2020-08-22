rock_library(camera_interface
	SOURCES CamInterface.cpp BrightnessIndicator.cpp ExposureController.cpp
	HEADERS CamInterface.h AutoWhiteBalance.h BrightnessIndicator.h ExposureController.h CamInfoUtils.h CamTypes.h
	DEPS_PKGCONFIG base-types opencv${opencv_pkgconfig_suffix})
