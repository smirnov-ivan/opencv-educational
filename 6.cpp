#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    String face_cascade_path = "E:\\opencv\\sources\\data\\haarcascades\\haarcascade_frontalface_default.xml";
    String eye_cascade_path = "E:\\opencv\\sources\\data\\haarcascades\\haarcascade_eye.xml";
    String smile_cascade_path = "E:\\opencv\\sources\\data\\haarcascades\\haarcascade_smile.xml";

    CascadeClassifier face_cascade, eye_cascade, smile_cascade;

    face_cascade.load(face_cascade_path);
    eye_cascade.load(eye_cascade_path);
    smile_cascade.load(smile_cascade_path);

    VideoCapture cap("ZUA.mp4");

    Mat frame, gray;

    while (1) {
        cap >> frame;
        if (frame.empty()) break;

        cvtColor(frame, gray, COLOR_BGR2GRAY);
        equalizeHist(gray, gray);

        vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.3, 10, 0, Size(60, 60));

        for (const auto& face : faces) {
            rectangle(frame, face, Scalar(255, 0, 0), 2);

            Mat faceROI_gray = gray(face);
            Mat faceROI_color = frame(face);

            vector<Rect> eyes;
            eye_cascade.detectMultiScale(faceROI_gray, eyes, 1.6, 15, 0, Size(20, 20));

            for (auto& eye : eyes) {
                Point eye_center(face.x + eye.x + eye.width / 2,
                    face.y + eye.y + eye.height / 2);
                int radius = cvRound((eye.width + eye.height) * 0.25);
                circle(frame, eye_center, radius, Scalar(0, 255, 0), 2);
            }

            vector<Rect> smiles;
            smile_cascade.detectMultiScale(faceROI_gray, smiles, 1.2, 30, 0, Size(30, 30));

            for (const auto& smile : smiles) {
                Rect smile_global(face.x + smile.x, face.y + smile.y,
                    smile.width, smile.height);
                rectangle(frame, smile_global, Scalar(0, 0, 255), 2);
            }
        }

        imshow("okak", frame);
        if (waitKey(30) == 27) break;
    }

    cap.release();
    destroyAllWindows();
    return 0;
}