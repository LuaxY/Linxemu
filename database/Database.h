#ifndef DATABASE_H
#define DATABASE_H

#include "mysql++.h"
#include "../config/Config.h"

using namespace std;

class Database
{
    public:
        static Database* Instance();
        void init();
        mysqlpp::Connection* db;

    private:
        Database(){};
        Database(Database const&){};
        Database& operator=(Database const&){};
        static Database* m_pInstance;
};

#endif // DATABASE_H
