#include "Database.h"

Database* Database::m_pInstance = NULL;

Database* Database::Instance()
{
    if(!m_pInstance)
        m_pInstance = new Database;

    return m_pInstance;
}

void Database::init()
{
    Config* config = Config::Instance();

    const char* database = config->database.c_str();
    const char* host = config->host.c_str();
    const char* username = config->username.c_str();
    const char* password = config->password.c_str();

    db = new mysqlpp::Connection(true);
    db->connect(database, host, username, password);
}
