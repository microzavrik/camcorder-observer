#include "TelegramBotConfigurator.hpp"

TelegramBotConfigurator::TelegramBotConfigurator(QWidget* parent) : QWidget(parent)
{
    setWindowTitle("Telegram Bot Configurator");
    setStyleSheet("background-color: #333; color: white;");

    tokenEdit = new QLineEdit(this);
    tokenEdit->setPlaceholderText("Enter Bot Token");

    userIdsEdit = new QLineEdit(this);
    userIdsEdit->setPlaceholderText("Enter User IDs (comma-separated)");

    saveButton = new QPushButton("Save Configuration", this);
    connect(saveButton, &QPushButton::clicked, this, &TelegramBotConfigurator::saveConfiguration);

    startButton = new QPushButton("Start Bot", this);
    startButton->setStyleSheet("background-color: green; color: white;");
    connect(startButton, &QPushButton::clicked, this, &TelegramBotConfigurator::startBot);

    offButton = new QPushButton("Off Bot", this);
    offButton->setStyleSheet("background-color: red; color: white;");
    connect(offButton, &QPushButton::clicked, this, &TelegramBotConfigurator::stopBot);

    statusLabel = new QLabel("Bot Status: Off");
    statusLabel->setStyleSheet("color: red; font-weight: bold;");

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Telegram Bot Configuration"));
    layout->addWidget(tokenEdit);
    layout->addWidget(userIdsEdit);
    layout->addWidget(saveButton);
    layout->addWidget(statusLabel);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(startButton);
    buttonLayout->addWidget(offButton);
    layout->addLayout(buttonLayout);

    setLayout(layout);
}

void TelegramBotConfigurator::saveConfiguration()
{
    libconfig::Config cfg;
    cfg.getRoot().add("bot_token", libconfig::Setting::TypeString) = tokenEdit->text().toStdString();
    libconfig::Setting& userIdsSetting = cfg.getRoot().add("user_ids", libconfig::Setting::TypeArray);
    QStringList userIds = userIdsEdit->text().split(",");
    userIds.removeAll("");

    for (const QString& userId : userIds)
    {
        userIdsSetting.add(libconfig::Setting::TypeString) = userId.toStdString();
    }

    try
    {
        cfg.writeFile("telegram_bot_config.cfg");
    }
    catch (const libconfig::FileIOException& ex)
    {
        qDebug() << "Error writing config file: " << ex.what();
    }
}

void TelegramBotConfigurator::startBot()
{
    statusLabel->setText("Bot Status: On");
    statusLabel->setStyleSheet("color: green; font-weight: bold; text-shadow: 0 0 10px green;");

}

void TelegramBotConfigurator::stopBot()
{
    statusLabel->setText("Bot Status: Off");
    statusLabel->setStyleSheet("color: red; font-weight: bold; text-shadow: 0 0 10px red;");
}