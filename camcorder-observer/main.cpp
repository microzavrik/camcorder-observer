#include "TelegramBotConfigurator.hpp"
#include "TelegramBot.hpp"
#include "GetBotToken.hpp"
#include "FaceObserver.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    tg_bot::TelegramBot bot(config_tool::getTelegramToken("telegram_bot_config.cfg"));
    std::thread([&] {
        bot.Start();
        });
    FaceObserver observer(bot);
    std::thread([&] {
        observer.run();
        });

    TelegramBotConfigurator botConfigurator;
    botConfigurator.show();

    return app.exec();
}