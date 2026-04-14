//#include <opencv2/opencv.hpp>
//#include <opencv2/imgproc.hpp>
//#include <iostream>
//#include <vector>
//#include <string>
//
//using namespace cv;
//using namespace std;
//
//string classifyShape(const vector<Point>& contour, double& confidence) {
//    double perimeter = arcLength(contour, true);
//    if (perimeter < 1e-6) return "unknown";
//
//    vector<Point> approx;
//    approxPolyDP(contour, approx, 0.02 * perimeter, true);
//    int vertices = (int)approx.size();
//    double area = contourArea(contour);
//    if (area < 10) return "unknown";
//
//    Rect bbox = boundingRect(contour);
//    double width = bbox.width;
//    double height = bbox.height;
//    double aspectRatio = width / height;
//    double solidity = area / (width * height);
//
//    if (vertices == 3) {
//        confidence = 1.0;
//        return "Triangle";
//    }
//    else if (vertices == 4) {
//        if (aspectRatio >= 0.85 && aspectRatio <= 1.15) {
//            confidence = 1.0;
//            return "Square";
//        }
//        else {
//            confidence = 0.9;
//            return "Rectangle";
//        }
//    }
//    else if (vertices >= 5 && vertices <= 6) {
//        if (aspectRatio >= 0.85 && aspectRatio <= 1.15 && solidity > 0.9) {
//            confidence = solidity;
//            return "Square";
//        }
//        else {
//            double circularity = 4 * CV_PI * area / (perimeter * perimeter);
//            if (circularity > 0.85) {
//                confidence = circularity;
//                return "Circle";
//            }
//        }
//    }
//    else {
//        double circularity = 4 * CV_PI * area / (perimeter * perimeter);
//        if (circularity > 0.85) {
//            confidence = circularity;
//            return "Circle";
//        }
//    }
//    return "unknown";
//}
//
//int main() {
//    VideoCapture cap("video.mkv");
//    if (!cap.isOpened()) {
//        cerr << "Cannot open video" << endl;
//        return -1;
//    }
//
//    namedWindow("Shape Detection", WINDOW_NORMAL);
//    setWindowProperty("Shape Detection", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);
//    namedWindow("Contours", WINDOW_NORMAL);
//
//    Mat frame, gray, clahe_out, edges, morph_edges, contourView;
//    Ptr<CLAHE> clahe = createCLAHE(3.0, Size(8, 8));
//    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
//
//    while (true) {
//        cap >> frame;
//        if (frame.empty()) break;
//
//        cvtColor(frame, gray, COLOR_BGR2GRAY);
//        clahe->apply(gray, clahe_out);
//        GaussianBlur(clahe_out, clahe_out, Size(3, 3), 0.5);
//        Canny(clahe_out, edges, 30, 90);
//        morphologyEx(edges, morph_edges, MORPH_CLOSE, kernel, Point(-1, -1), 1);
//
//        vector<vector<Point>> contours;
//        findContours(morph_edges, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
//
//        contourView = Mat::zeros(frame.size(), CV_8UC3);
//
//        for (const auto& contour : contours) {
//            double area = contourArea(contour);
//            double frameArea = frame.total();
//            if (area > frameArea * 0.9) continue;
//            if (area < 100) continue;
//            drawContours(contourView, vector<vector<Point>>{contour}, -1, Scalar(0, 0, 255), 1);
//        }
//
//        for (const auto& contour : contours) {
//            double area = contourArea(contour);
//            double minArea = 15;
//            double frameArea = frame.total();
//            if (area > frameArea * 0.9) continue;
//            if (area < minArea) continue;
//
//            double confidence;
//            string shapeName = classifyShape(contour, confidence);
//            if (shapeName == "unknown" || shapeName == "Rectangle") continue;
//
//            Rect bbox = boundingRect(contour);
//            Point center(bbox.x + bbox.width / 2, bbox.y + bbox.height / 2);
//
//            rectangle(frame, bbox, Scalar(0, 255, 0), 2);
//
//            int fontFace = FONT_HERSHEY_SIMPLEX;
//            double fontScale = 0.8;
//            int thickness = 2;
//            Size textSize = getTextSize(shapeName, fontFace, fontScale, thickness, nullptr);
//            Point textOrg(center.x - textSize.width / 2, center.y + textSize.height / 2);
//
//            rectangle(frame, Rect(textOrg.x - 5, textOrg.y - textSize.height - 5,
//                textSize.width + 10, textSize.height + 10), Scalar(0, 0, 0), FILLED);
//            putText(frame, shapeName, textOrg, fontFace, fontScale, Scalar(255, 255, 255), thickness);
//        }
//
//        imshow("Shape Detection", frame);
//        imshow("Contours", contourView);
//
//        if (waitKey(30) == 27) break;
//    }
//
//    cap.release();
//    destroyAllWindows();
//    return 0;
//}   