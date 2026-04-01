//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <string>
//#include <sstream>
//#include <iomanip>
//
//using namespace cv;
//using namespace std;
//
//string getShapeName(const vector<Point>& contour, double perimeter, double area) {
//    vector<Point> approx;
//    double epsilon = 0.02 * perimeter;
//    approxPolyDP(contour, approx, epsilon, true);
//
//    int vertices = (int)approx.size();
//    if (vertices == 3) {
//        return "Triangle";
//    }
//    else if (vertices == 4) {
//        Rect rect = boundingRect(approx);
//        double rectArea = rect.width * rect.height;
//        double areaRatio = area / rectArea;
//        if (areaRatio > 0.9) {
//            if (abs(rect.width - rect.height) < min(rect.width, rect.height) * 0.1)
//                return "Square";
//            else
//                return "Rectangle";
//        }
//        return "Quadrilateral";
//    }
//    else {
//        double circularity = 4 * CV_PI * area / (perimeter * perimeter);
//        if (circularity > 0.7)
//            return "Circle";
//        else
//            return "Polygon";
//    }
//}
//
//int main(int argc, char** argv) {
//    string imagePath = "shapes.png";
//    Mat original = imread(imagePath, IMREAD_COLOR);
//
//    Mat img;
//    const int MAX_WIDTH = 1200;
//    const int MAX_HEIGHT = 800;
//    double scale = 1.0;
//    if (original.cols > MAX_WIDTH || original.rows > MAX_HEIGHT) {
//        scale = min((double)MAX_WIDTH / original.cols, (double)MAX_HEIGHT / original.rows);
//        Size newSize((int)(original.cols * scale), (int)(original.rows * scale));
//        resize(original, img, newSize);
//    }
//    else {
//        img = original.clone();
//    }
//
//    Mat gray;
//    cvtColor(img, gray, COLOR_BGR2GRAY);
//    Mat blurred;
//    GaussianBlur(gray, blurred, Size(5, 5), 1.5);
//    Mat edges;
//    Canny(blurred, edges, 50, 150);
//    vector<vector<Point>> contours;
//    vector<Vec4i> hierarchy;
//    findContours(edges, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//    for (int i = 0; i < contours.size(); ++i) {
//        double area = contourArea(contours[i]);
//        if (area < 100) continue;
//        double perimeter = arcLength(contours[i], true);
//        Moments m = moments(contours[i]);
//        if (m.m00 == 0) continue;
//        Point2f centroid(m.m10 / m.m00, m.m01 / m.m00);
//        string shapeName = getShapeName(contours[i], perimeter, area);
//        stringstream ss;
//        ss << shapeName << ", P: " << fixed << setprecision(2) << perimeter;
//        string label = ss.str();
//        drawContours(img, contours, (int)i, Scalar(0, 255, 0), 2);
//        int fontFace = FONT_HERSHEY_SIMPLEX;
//        double fontScale = 0.5;
//        int thickness = 1;
//        int baseline = 0;
//        Size textSize = getTextSize(label, fontFace, fontScale, thickness, &baseline);
//        Point textOrg(centroid.x - textSize.width / 2, centroid.y + textSize.height / 2);
//        putText(img, label, textOrg, fontFace, fontScale, Scalar(255, 0, 0), thickness);
//        circle(img, Point((int)centroid.x, (int)centroid.y), 3, Scalar(0, 0, 255), FILLED);
//    }
//    namedWindow("Detected shapes", WINDOW_NORMAL);
//    resizeWindow("Detected shapes", 1200, 800);
//    imshow("Detected shapes", img);
//    waitKey(0);
//    return 0;
//}