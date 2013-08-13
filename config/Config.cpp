#include "Config.h"

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

    /** auth **/
    port = reader.GetInteger("auth", "port", 1337);
    max_user = reader.GetInteger("auth", "max_user", 200);
    max_user = reader.GetInteger("auth", "requiredVersion", 0);
    max_user = reader.GetInteger("auth", "currentVersion", 0);

    /** database **/
    host = reader.Get("database", "host", "127.0.0.1");
    username = reader.Get("database", "username", "root");
    password = reader.Get("database", "password", "");
    database = reader.Get("database", "database", "linxemu");
}
