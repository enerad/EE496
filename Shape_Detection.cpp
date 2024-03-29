#include "Shape_Detection.h"

//using namespace cv;

/** @function main */
Mat Shape_Detection(Mat frame)
{
	Mat src, src_gray;

	/// Read the image
	//src = imread("test-img.png");
	//src = imread("test-img.png", 1); 
	src = frame;
	//resize(src, src, Size(1366, 768));

	if (!src.data)
	{
		printf("frame coudl not be read \n");
		exit(EXIT_FAILURE);
	}

	/// Convert it to gray
	cvtColor(src, src_gray, CV_BGR2GRAY);

	/// Reduce the noise so we avoid false circle detection
	GaussianBlur(src_gray, src_gray, Size(9, 9), 2, 2);

	/* check for image's greyscale */
	//namedWindow("Gaussian Blur", CV_WINDOW_AUTOSIZE);
	//imshow("Gaussian Blur", src_gray);

	vector<Vec3f> circles;

	/// Apply the Hough Transform to find the circles
	HoughCircles(src_gray, circles, CV_HOUGH_GRADIENT, 1.0, src_gray.rows / 8, 140, 40, 0, 0); // original: 1, src_gray.rows / 4, 100, 25, 0, 0. improved? : 1.0, src_gray.rows / 8, 140, 40, 0, 0
	//HoughCircles(src, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 8, 200, 100, 0, 0); // for non converted image

	/// Draw the circles detected
	for (size_t i = 0; i < circles.size(); i++)
	{
		Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
		int radius = cvRound(circles[i][2]);
		// circle center
		circle(src, center, 3, Scalar(0, 255, 0), -1, 8, 0);
		// circle outline
		circle(src, center, radius, Scalar(0, 0, 255), 3, 8, 0);
	}

	/// Show your results
/*	namedWindow("Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE);
	imshow("Hough Circle Transform Demo", src);
	waitKey(0);
*/

	return src;
}