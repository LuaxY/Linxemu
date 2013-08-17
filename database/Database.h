#ifndef DATABASE_H
#define DATABASE_H

#include "mysql++.h"
#ifdef GAME
#include "../config/ConfigGame.h"
#else
#include "../config/ConfigLogin.h"
#endif
#include "../utils/utils.h"

using namespace std;

class Database
{
    public:
        static Database* Instance();
        void init();
        void selectDefault();
        mysqlpp::Connection* db;

    private:
        Database(){};
        Database(Database const&){};
        Database& operator=(Database const&){};
        static Database* m_pInstance;
};

#endif // DATABASE_H
