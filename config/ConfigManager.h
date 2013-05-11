#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>
#include <map>
#include <list>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class ConfigManager
{
	public:
		ConfigManager(string configFile);
		~ConfigManager();

		string getString(string name);
		bool getBool(string name);
		double getDouble(string name);
		int getInt(string name);

		inline map<string, string>& getSymbols()
		{
			return symbols;
		}

		inline ConfigManager* group(string name)
		{
			return groups[name];
		}

		inline map<string, ConfigManager*>& getGroups()
		{
			return groups;
		}

	private:
		void add(string name, string value);
		void split(string in, string& left, string& right, char c);
		void trim(string& s);
		void symbolExpand(string& s);
		void symbolExpand(map<string, string>& symbols, string& s);
		void envSymbolExpand(string& s);

		map<string, string> symbols;
		map<string, string> envSymbols;
		map<string, ConfigManager*> groups;
		list<ConfigManager*> groupStack;
		string debugInfo;
};

#endif //CONFIG_MANAGER_H
