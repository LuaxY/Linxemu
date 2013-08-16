#ifndef CONFIG_H
#define CONFIG_H

#include "INIReader.h"

using namespace std;

class Config
{
    public:
        static Config* Instance();
        void init(string);

        /** game **/
        unsigned short port;
        unsigned short max_user;

        /** database **/
        string host;
        string username;
        string password;
        string database;

    private:
        Config(){};
        Config(Config const&){};
        Config& operator=(Config const&){};
        static Config* m_pInstance;
};

#endif // CONFIG_H
