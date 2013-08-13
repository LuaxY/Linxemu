#ifndef AUTH_CONFIG_H
#define AUTH_CONFIG_H

#include "INIReader.h"

using namespace std;

class AuthConfig
{
    public:
        static AuthConfig* Instance();
        void init(string);

        /** auth **/
        unsigned short port;
        unsigned short max_user;

        /** database **/
        string host;
        string username;
        string password;
        string database;

    private:
        AuthConfig(){};
        AuthConfig(AuthConfig const&){};
        AuthConfig& operator=(AuthConfig const&){};
        static AuthConfig* m_pInstance;
};

#endif // AUTH_CONFIG_H
