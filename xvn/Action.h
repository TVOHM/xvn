#ifndef ACTION_H
#define ACTION_H

#include "pugixml.hpp"
using namespace pugi;

#include <map>
#include <string>
using namespace std;

class Action
{
public:
	Action();
	bool initialise(const xml_node& node);
	void doAction(map<string, string>& variables);
private:
	bool mIsInitialised;
	const static string ACTIONS[];
	string mVariableName, mEffectorVariableName, mEffectorValue;
	int mAction;
};

#endif /* ACTION_H */