#include "AuthConfig.h"

AuthConfig* AuthConfig::m_pInstance = NULL;

AuthConfig* AuthConfig::Instance()
{
    if(!m_pInstance)
        m_pInstance = new AuthConfig;

    return m_pInstance;
}

void AuthConfig::init(string config_file)
{
    INIReader reader(config_file);

    /** auth **/
    port = reader.GetInteger("auth", "port", 1337);
    max_user = reader.GetInteger("auth", "max_user", 200);

    /** database **/
    host = reader.Get("database", "host", "127.0.0.1");
    username = reader.Get("database", "username", "root");
    password = reader.Get("database", "password", "");
    database = reader.Get("database", "database", "linxemu");
}
