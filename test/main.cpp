
BOOST_AUTO_TEST_CASE( check_simple_brightness_indicator )
{
	//Construct Test grayscale image
	cv::Mat mat(3,3, CV_8UC1);
	mat = cv::Scalar(128);

	//Check if the average brightness is determinend correctly
	SimpleBrightnessIndicator sbi;
	int val = sbi.getBrightness(mat);
	BOOST_CHECK_EQUAL(128, val);
}

BOOST_AUTO_TEST_CASE( check_weighted_brightness_indicator ) 
{
	//Construct Test grayscale image
	cv::Mat mat(10,10, CV_8UC1);
	mat = cv::Scalar(0);

	//Set the points in the middle of the image to a high brightness value
	cv::Mat(mat, cv::Rect(4,4,2,2)) = cv::Scalar(255);

	std::vector<WeightedRect> regions;
	regions.push_back(WeightedRect(-0.2,-0.2,0.2,0.2,8));
	WeightedBoxesBrightnessIndicator wbi(regions);
	int val = wbi.getBrightness(mat);
	BOOST_CHECK_EQUAL(255, val);

	regions.push_back(WeightedRect(0,0.2,1,1,2));
	wbi.setWeightedRegions(regions);
	int val2 = wbi.getBrightness(mat);
	BOOST_CHECK_EQUAL(204, val2);
}
