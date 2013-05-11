#include "ConfigManager.h"

ConfigManager::ConfigManager(string configFile)
{
	debugInfo = configFile;
	groupStack.push_front(this);

	FILE* in = fopen(configFile.c_str(), "r");

	if(!in)
	{
		cerr << "cannot open input file '" << configFile << "'" << endl;
		exit(2);
	}

	char buff[1024];

	while (fgets(buff, 1024, in))
	{
		string line=buff;

		if((line.length() > 2) && (line[0] != '#') && (line.find(')') == string::npos))
		{
			string name;
			string value;
			split(line, name, value, '=');

			/*if(value == "(")
			{
				ConfigManager* newGroup = new ConfigManager(name, debugInfo);
				groupStack.front()->groups[name] = newGroup;
				groupStack.push_front(newGroup);
			}
			else
			{*/
				for(list<ConfigManager*>::reverse_iterator i = groupStack.rbegin(); i != groupStack.rend(); ++i)
				{
					(*i)->symbolExpand(value);
				}

				symbolExpand(value);
				groupStack.front()->add(name, value);
			//}
		}

		if((line.length() > 0) && (line[0] != '#') && (line.find(')') != string::npos))
		{
			groupStack.pop_front();
		}
	}

	fclose(in);
}

ConfigManager::~ConfigManager()
{
	for(map<string, ConfigManager*>::iterator i = groups.begin(); i != groups.end(); ++i)
	{
		delete i->second;
	}
}

void ConfigManager::add(string name, string value)
{
	symbols[name] = value;
}

void ConfigManager::split(string in, string& left, string& right, char c)
{
	size_t pos = in.find_first_of(c);

	if(pos == string::npos)
	{
		left = in;
		trim(left);
		right = "";
	}
	else if(pos <= 1)
	{
		left = "";
		right = in.substr(pos+1, string::npos);
		trim(right);
	}
	else
	{
		left = in.substr(0, pos-1);
		trim(left);
		right = in.substr(pos+1, string::npos);
		trim(right);
	}
}

void ConfigManager::trim(string& s)
{
	while((s.length() > 1) && ( (s[0] == ' ') || (s[0] =='\t')))
	{
		s = s.substr(1, string::npos);
	}

	while((s.length() > 1) &&
             ((s[s.length()-1] == ' ')  ||
			  (s[s.length()-1] == '\t') ||
			  (s[s.length()-1] == '\n') ||
			  (s[s.length()-1] == '\r') ))
    {
		s = s.substr(0, s.length()-1);
	}

	if((s.length() > 1) && (s[0] == '"'))
	{
		s = s.substr(1, string::npos);
	}

	if((s.length() > 1) && (s[s.length()-1] == '"'))
	{
		s = s.substr(0, s.length()-1);
	}
}

void ConfigManager::symbolExpand(string& s)
{
	symbolExpand(symbols, s);
}

void ConfigManager::symbolExpand(map<string, string>& symbols, string& s)
{
	bool expanded;

	do
	{
		expanded = false;
		for(map<string, string>::iterator i = symbols.begin(); i != symbols.end(); ++i)
		{
			string search = "%" + i->first + "%";
			string replace = i->second;
			size_t pos = s.find(search);

			if(pos != string::npos)
			{
				expanded = true;
				s.replace(pos, search.length(), replace);
			}
		}
	}
	while(expanded);
}

string ConfigManager::getString(string name)
{
	map<string, string>::iterator i = symbols.find(name);

	if(i == symbols.end())
	{
		//cout << "access of missing property '" << name << "' (" << debugInfo << ")" << endl;
		exit(4);
	}

	return i->second;
}

bool ConfigManager::getBool(string name)
{
	string val = getString(name);

	if((val == "yes")  ||
       (val == "Yes")  ||
       (val == "YES")  ||
       (val == "oui")  ||
       (val == "Oui")  ||
       (val == "OUI")  ||
       (val == "true") ||
       (val == "True") ||
       (val == "TRUE"))
	{
		return true;
	}

	return false;
}

double ConfigManager::getDouble(string name)
{
	string val = getString(name);

	return atof(val.c_str());
}

int ConfigManager::getInt(string name)
{
	string val = getString(name);

	return atoi(val.c_str());
}
