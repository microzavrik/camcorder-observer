#include "TelegramBotConfigurator.hpp"
#include "TelegramBot.hpp"
#include "GetBotToken.hpp"
#include "FaceObserver.hpp"
#include "windows_console.hpp"

int main(int argc, char* argv[])
{
    Console c;
    QApplication app(argc, argv);

    tg_bot::TelegramBot bot(config_tool::getTelegramToken("telegram_bot_config.cfg"));
    bot.loadConfigFromFile("telegram_bot_config.cfg");
    std::thread([&] {
        bot.Start();
        }).detach();
    FaceObserver observer(bot);
    std::thread([&] {
        observer.run();
        }).detach();

    TelegramBotConfigurator botConfigurator;
    botConfigurator.show();
    return app.exec();
}