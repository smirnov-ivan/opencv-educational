//#include <opencv2/opencv.hpp>
//#include <iostream>
//
//using namespace cv;
//using namespace std;
//
//int main()
//{
//    string imagePath = "mukka.jpg";
//
//    Mat src = imread(imagePath);
//    if (src.empty())
//    {
//        cout << "Can't load" << imagePath;
//        return -1;
//    }
//
//    namedWindow("Source", WINDOW_AUTOSIZE);
//    imshow("Source", src);
//
//    Mat gray;
//    cvtColor(src, gray, COLOR_BGR2GRAY);
//    namedWindow("Gray", WINDOW_AUTOSIZE);
//    imshow("Gray", gray);
//
//    Mat resized;
//    resize(src, resized, Size(src.cols * 2, src.rows / 2));
//    namedWindow("Resized", WINDOW_AUTOSIZE);
//    imshow("Resized", resized);
//
//    Point2f center(src.cols / 2.0f, src.rows / 2.0f);
//    double angle = 45.0;
//    double scale = 1.0;
//    Mat rotMat = getRotationMatrix2D(center, angle, scale);
//
//    Rect2f bbox = RotatedRect(Point2f(), src.size(), angle).boundingRect2f();
//    rotMat.at<double>(0, 2) += bbox.width / 2.0 - src.cols / 2.0;
//    rotMat.at<double>(1, 2) += bbox.height / 2.0 - src.rows / 2.0;
//
//    Mat rotated;
//    warpAffine(src, rotated, rotMat, bbox.size());
//    namedWindow("Rotated", WINDOW_AUTOSIZE);
//    imshow("Rotated", rotated);
//
//    Mat blurred;
//    GaussianBlur(src, blurred, Size(5, 5), 0);
//    namedWindow("Blur", WINDOW_AUTOSIZE);
//    imshow("Blur", blurred);
//
//    Mat edges;
//    Canny(gray, edges, 50, 150);
//    namedWindow("Canny", WINDOW_AUTOSIZE);
//    imshow("Canny", edges);
//
//    imwrite("gray_output.jpg", gray);
//    imwrite("canny_output.jpg", edges);
//
//    waitKey(0);
//    destroyAllWindows();
//
//    return 0;
//}