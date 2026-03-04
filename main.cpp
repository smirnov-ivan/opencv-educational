#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    Mat img = imread("marker.png");

    Mat hsv;
    cvtColor(img, hsv, COLOR_BGR2HSV);

    Mat mask1, mask2, mask;
    inRange(hsv, Scalar(0, 100, 100), Scalar(10, 255, 255), mask1);
    inRange(hsv, Scalar(170, 100, 100), Scalar(180, 255, 255), mask2);
    mask = mask1 | mask2;


    Mat kernel = getStructuringElement(MORPH_ELLIPSE, Size(5, 5));
    morphologyEx(mask, mask, MORPH_CLOSE, kernel);

    vector<vector<Point>> contours;
    findContours(mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

    double minArea = 500;

    Mat result = img.clone();
    for (size_t i = 0; i < contours.size(); i++) {
        double area = contourArea(contours[i]);
        if (area < minArea) continue;

        Rect rect = boundingRect(contours[i]);
        rectangle(result, rect, Scalar(0, 255, 0), 2);

        putText(result, "Marker", Point(rect.x, rect.y - 5),
            FONT_HERSHEY_SIMPLEX, 0.6, Scalar(0, 255, 0), 2);
    }

    imshow("Original", img);
    imshow("Mask", mask);
    imshow("Detected Markers", result);

    waitKey(0);
    return 0;
}