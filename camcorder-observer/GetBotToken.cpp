#include "GetBotToken.hpp"

namespace config_tool
{
    std::string getTelegramToken(const std::string& configFile)
    {
        libconfig::Config cfg;
        std::string botToken;

        try
        {
            cfg.readFile(configFile.c_str());
            const libconfig::Setting& root = cfg.getRoot();

            if (root.exists("bot_token"))
            {
                botToken = root["bot_token"].c_str();
            }
            else
            {
                printf("Error: 'bot_token' setting not found in the config file.\n");
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

        return botToken;
    }
}