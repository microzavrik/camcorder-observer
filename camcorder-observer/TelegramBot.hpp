#pragma once

#include <tgbot/tgbot.h>
#include <thread>
#include <vector>
#include <string>

namespace tg_bot
{
	class TelegramBot
	{
	public:
		TelegramBot(const std::string& token);
		void Start();
		void PingUsersWithPhoto(const std::string& photoFilePath);
		void addUserId(const std::string& userId);
	private:
		TgBot::Bot bot;
		std::vector<std::string> userIds;

		void loadConfigFromFile(const std::string& configFile);
		void handleStartCommand(TgBot::Message::Ptr message);
		void handleConfigCommand(TgBot::Message::Ptr message);
		void handlePingHistoryCommand(TgBot::Message::Ptr message);
		void handleDevoloperInfoCommand(TgBot::Message::Ptr message);
		void handleHelpCommand(TgBot::Message::Ptr message);
	};
}