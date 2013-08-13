#ifndef DATABASE_H
#define DATABASE_H

#include "mysql++.h"
#include "../config/Config.h"
#include "../utils/utils.h"

using namespace std;

class Database
{
    public:
        static Database* Instance();
        void init();
        void selectLogin();
        mysqlpp::Connection* db;

    private:
        Database(){};
        Database(Database const&){};
        Database& operator=(Database const&){};
        static Database* m_pInstance;
};

#endif // DATABASE_H
