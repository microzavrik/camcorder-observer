#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

class FaceDetector {
private:
    CascadeClassifier face_cascade;
    VideoCapture cap;

public:
    FaceDetector() {
        face_cascade.load("haarcascade_frontalface_default.xml");
        cap.open(0);
    }

    void detectAndSaveFace() {
        Mat frame;
        cap >> frame;

        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        vector<Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

        for (size_t i = 0; i < faces.size(); i++) {
            Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
            ellipse(frame, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4);

            Mat face_roi = frame(faces[i]);
            imwrite("detected_face.png", face_roi);
            cout << "Face detected and saved to 'detected_face.png'" << endl;
        }

        imshow("Face Detection", frame);
    }

    void run() {
        namedWindow("Face Detection", WINDOW_AUTOSIZE);

        while (true) {
            detectAndSaveFace();

            if (waitKey(1) == 'q')
                break;
        }

        cap.release();
        destroyAllWindows();
    }
};

int main() {
    FaceDetector faceDetector;
    faceDetector.run();

    return 0;
}