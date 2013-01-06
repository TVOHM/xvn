#include <vector>

#include"Action.h"
#include "Condition.h"

class Control
{
public:
	Control();
	bool initialise(const xml_node& node, const xml_node& game);
	bool conditionsMet(const map<string, string>& variables);
	void doActions();
protected:
	virtual bool virtualInitialise(const xml_node& node)=0;
	bool mIsInitialised;
private:
	vector<Condition> mConditions;
	vector<Action> mActions;
};