//#include <opencv2/opencv.hpp>
//#include <iostream>
//#include <random>
//
//using namespace cv;
//using namespace std;
//
//int main() {
//
//    const int width = 1000;
//    const int height = 800;
//
//    Mat canvas(height, width, CV_8UC3, Scalar(255, 255, 255));
//    line(canvas, Point(50, 50), Point(200, 50), Scalar(0, 0, 255), 2);
//    rectangle(canvas, Point(50, 100), Point(200, 200), Scalar(0, 255, 0), 2);
//    circle(canvas, Point(350, 150), 50, Scalar(255, 0, 0), FILLED);
//    ellipse(canvas, Point(550, 150), Size(80, 40), 0, 0, 360, Scalar(0, 255, 255), 2);
//    vector<Point> polygon = {
//        { 100, 400 },
//        { 200, 350 },
//        { 250, 450 },
//        { 150, 500 },
//        { 50, 450 }
//    };
//    polylines(canvas, vector<vector<Point>>{polygon}, true, Scalar(255, 0, 255), 2);
//    putText(canvas, "22-AM-2 Smirnov", Point(300, 550),
//        FONT_HERSHEY_DUPLEX, 1.0, Scalar(0, 0, 0), 2);
//    imshow("Рисовашка", canvas);
//    waitKey(0);
//    imwrite("output.png", canvas);
//
//
//    string text = "22-AM-2 Smirnov";
//    int fontFace = FONT_HERSHEY_SIMPLEX;
//    double fontScale = 1.0;
//    int thickness = 2;
//    Scalar textColor(0, 0, 0);
//
//    int baseline;
//    Size textSize = getTextSize(text, fontFace, fontScale, thickness, &baseline);
//    int textWidth = textSize.width;
//    int textHeight = textSize.height;
//    int ascent = textHeight - baseline;
//    int descent = baseline;
//    int minX = 0;
//    int maxX = width - 1 - textWidth;
//    int minY = ascent;
//    int maxY = height - 1 - descent;
//
//    int x = (minX + maxX) / 2;
//    int y = (minY + maxY) / 2;
//
//    VideoWriter video("wooow.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 30, Size(width, height));
//    if (!video.isOpened()) {
//        cerr << "ERR\n";
//        return -1;
//    }
//
//    random_device rd;
//    mt19937 gen(rd());
//    uniform_int_distribution<> dx(-3, 3);
//    uniform_int_distribution<> dy(-3, 3);
//
//    while (true) {
//        Mat frame = canvas.clone();
//
//        x += dx(gen);
//        y += dy(gen);
//
//        if (x < minX) { x = minX + (minX - x); }
//        if (x > maxX) { x = maxX - (x - maxX); }
//        if (y < minY) { y = minY + (minY - y); }
//        if (y > maxY) { y = maxY - (y - maxY); }
//        putText(frame, text, Point(x, y), fontFace, fontScale, textColor, thickness);
//
//        imshow("трясучка", frame);
//        video.write(frame);
//
//        char key = waitKey(30);
//        if (key == 27) break;
//    }
//
//    video.release();
//    destroyAllWindows();
//
//
//    return 0;
//}