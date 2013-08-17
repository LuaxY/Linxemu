#include "ConfigGame.h"

Config* Config::m_pInstance = NULL;

Config* Config::Instance()
{
    if(!m_pInstance)
        m_pInstance = new Config;

    return m_pInstance;
}

void Config::init(string config_file)
{
    INIReader reader(config_file);

    /** game **/
    port = reader.GetInteger("game", "port", 5555);
    max_user = reader.GetInteger("game", "max_user", 200);
    requiredVersion = reader.GetInteger("game", "requiredVersion", 0);
    currentVersion = reader.GetInteger("game", "currentVersion", 0);

    /** database **/
    host = reader.Get("database", "host", "127.0.0.1");
    username = reader.Get("database", "username", "root");
    password = reader.Get("database", "password", "");
    database = reader.Get("database", "database", "linxemu_jiva");
    login_db = reader.Get("database", "login_db", "linxemu_login");
}
