#ifndef CONDITION_H
#define CONDITION_H

#include "pugixml.hpp"
using namespace pugi;

#include <map>
#include <string>
#include <iostream>
using namespace std;

class Condition
{
public:
	Condition();
	bool initialise(const xml_node& node);
	bool conditionMet(const map<string, string>& variables);
private:
	bool mIsInitialised;
	const static string CONDITIONS[];
	string mVariableName, mCompairsonVariableName, mComparisonValue;
	int mCondition;
};

#endif /* CONDITION_H */