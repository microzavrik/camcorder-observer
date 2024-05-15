#include "FaceObserver.hpp"

FaceObserver::FaceObserver(tg_bot::TelegramBot& bot) : tg_bot_ref(bot)
{
	faceCascade.load("haarcascade_frontalface_default.xml");
	cap.open(0);
}

void FaceObserver::detectAndSaveFace()
{
	cv::Mat frame;
	cap >> frame;

	cv::Mat gray;
	cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

	std::vector<cv::Rect> faces;
	faceCascade.detectMultiScale(gray, faces, 1.1, 2, 0 | cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

	for (size_t i = 0; i < faces.size(); i++) 
	{
		cv::Point center(faces[i].x + faces[i].width / 2,
			faces[i].y + faces[i].height / 2);
		cv::ellipse(frame, center, cv::Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360, 
			cv::Scalar(255, 0, 255), 4);

		cv::Mat face_roi = frame(faces[i]);
		cv::imwrite("detected_face.png", face_roi);
		std::cout << "Face detected and saved to 'detected_face.png'" << std::endl;
	}
	cv::imshow("Face Detection", frame);
}

void FaceObserver::run()
{
	cv::namedWindow("Face Detection", cv::WINDOW_AUTOSIZE);

	while (true)
	{
		detectAndSaveFace();

		if (cv::waitKey(1) == 'q')
			break;
	}

	cap.release();
	cv::destroyAllWindows();
}