//#include <iostream>
//#include <chrono>
//#include <complex>
//#include <opencv2/opencv.hpp>
//#include <omp.h>
//using namespace std;
//
//const int WIDTH = 1000;
//const int HEIGHT = 1000;
//const double X_MIN = -2.5;
//const double X_MAX = 1.0;
//const double Y_MIN = -1.5;
//const double Y_MAX = 1.5;
//const int MAX_ITER = 256;
//
//cv::Vec3b getColor(int iter, const std::complex<double>& z) {
//    if (iter == MAX_ITER) return cv::Vec3b(0, 0, 0);
//    double smooth = iter + 1 - log(log(std::abs(z))) / log(2.0);
//    double t = smooth / MAX_ITER;
//    uchar r = (uchar)(255 * t);
//    uchar g = (uchar)(255 * (1 - t));
//    uchar b = (uchar)(128 * (1 - std::sin(t * CV_PI)));
//    return cv::Vec3b(b, g, r);
//}
//
//int mandelbrot(const complex<double>& c) {
//    complex<double> z(0.0, 0.0);
//    int iter = 0;
//    while (iter < MAX_ITER && norm(z) <= 4.0) {
//        z = z * z + c;
//        ++iter;
//    }
//    return iter;
//}
//
//void computeMandelbrot(cv::Mat& img, bool parallel) {
//    int rows = img.rows, cols = img.cols;
//    if (parallel) {
//        #pragma omp parallel for schedule(dynamic, 1)
//        for (int y = 0; y < rows; ++y) {
//            double imag = Y_MIN + y * (Y_MAX - Y_MIN) / rows;
//            cv::Vec3b* row = img.ptr<cv::Vec3b>(y);
//            for (int x = 0; x < cols; ++x) {
//                double real = X_MIN + x * (X_MAX - X_MIN) / cols;
//                std::complex<double> c(real, imag);
//                std::complex<double> z(0, 0);
//                int iter = 0;
//                while (iter < MAX_ITER && std::norm(z) <= 4.0) {
//                    z = z * z + c;
//                    ++iter;
//                }
//                row[x] = getColor(iter, z);
//            }
//        }
//    }
//    else {
//        for (int y = 0; y < rows; ++y) {
//            double imag = Y_MIN + y * (Y_MAX - Y_MIN) / rows;
//            cv::Vec3b* row = img.ptr<cv::Vec3b>(y);
//            for (int x = 0; x < cols; ++x) {
//                double real = X_MIN + x * (X_MAX - X_MIN) / cols;
//                std::complex<double> c(real, imag);
//                std::complex<double> z(0, 0);
//                int iter = 0;
//                while (iter < MAX_ITER && std::norm(z) <= 4.0) {
//                    z = z * z + c;
//                    ++iter;
//                }
//                row[x] = getColor(iter, z);
//            }
//        }
//    }
//}
//
//int main() {
//    cv::Mat seqImg(HEIGHT, WIDTH, CV_8UC3);
//    cv::Mat parImg(HEIGHT, WIDTH, CV_8UC3);
//    auto start = chrono::high_resolution_clock::now();
//    computeMandelbrot(seqImg, false);
//    auto end = chrono::high_resolution_clock::now();
//    double seqTime = chrono::duration<double, milli>(end - start).count();
//    cout << "Sequential time: " << seqTime << " ms\n";
//    vector<int> threadCounts = { 1, 2, 3, 4, 5, 6, 7, 8 };
//    cout << "\nParallel times and speedups:\n";
//    for (int threads : threadCounts) {
//        omp_set_num_threads(threads);
//        start = chrono::high_resolution_clock::now();
//        computeMandelbrot(parImg, true);
//        end = chrono::high_resolution_clock::now();
//        double parTime = chrono::duration<double, milli>(end - start).count();
//        double speedup = seqTime / parTime;
//        cout << "Threads = " << threads
//            << " -> time = " << parTime << " ms"
//            << ", ratio = " << speedup << "\n";
//    }
//    cv::imshow("Mandelbrot set", seqImg);
//    cout << "\nOkak...\n";
//    cv::waitKey(0);
//
//    return 0;
//}