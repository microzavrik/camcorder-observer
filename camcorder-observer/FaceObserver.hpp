#pragma once

#include <opencv2/opencv.hpp>

#include "TelegramBot.hpp"

class FaceObserver
{
public:
	FaceObserver(tg_bot::TelegramBot&);
	void detectAndSaveFace();
	void run();
private:
	cv::CascadeClassifier faceCascade;
	cv::VideoCapture cap;
	tg_bot::TelegramBot& tg_bot_ref;
};