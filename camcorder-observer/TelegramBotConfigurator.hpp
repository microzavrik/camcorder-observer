#pragma once

#include <QApplication>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QFile>
#include <QTextStream>
#include <libconfig.h++>

#include "TelegramBot.hpp"

class TelegramBotConfigurator : public QWidget
{
	Q_OBJECT
public:
	TelegramBotConfigurator(QWidget* parent = nullptr);
public slots:
	void saveConfiguration();
	void startBot();
	void stopBot();
private:
	QLineEdit* tokenEdit;
	QLineEdit* userIdsEdit;
	QPushButton* saveButton;
	QPushButton* startButton;
	QPushButton* offButton;
	QLabel* statusLabel;
};