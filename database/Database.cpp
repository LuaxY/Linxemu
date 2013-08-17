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

    const string database = config->database;
    const string host = config->host;
    const string username = config->username;
    const string password = config->password;

    db = new mysqlpp::Connection(false);
    if(!db->connect(database.c_str(), host.c_str(), username.c_str(), password.c_str()))
    {
        Logger::Log(ERROR, sLog(), "Unable to connect to the database '" + database + "' (" + username + ":" + password + "@" + host + ")");
        exit(1);
    }
}

void Database::selectDefault()
{
    Config* config = Config::Instance();
    db->select_db(config->database);
}
