#include "control.h"

bool Control::initialise(const xml_node& node)
{
	bool result = true;

	// If the node contains a chance attribute, use it to set the chance
	// else default chance to 1
	if(node.attribute("chance"))
		mChance = node.attribute("chance").as_int();
	else
		mChance = 1;

	// Iterate over all "if" child nodes to initialse child conditions
	for(auto& child : node.children("if"))
	{
		// Attempt to initalise them, setting the result flag to false if any fail
		Condition condition;
		if(condition.initialise(child) == false)
			result = false;
		else
			mConditions.push_back(condition);
	}

	// Iterate over all child nodes to initialse child actions
	for(auto& child : node.children())
	{
		string name = child.name();
		// Only use nodes that have a name (ignoring text nodes) and the name is not if (ignoring condition nodes)
		if(!name.empty() && name != "if")
		{
			// Attempt to initalise them, setting the result flag to false if any fail
			Action action;
			if(action.initialise(child) == false)
				result = false;
			else
				mActions.push_back(action);
		}
	}

	return result;
}

void Control::performActions(map<string, string>& variables)
{
	// Iterate over all child actions, calling their performAction method
	// with the variables as a parameter
	for(Action action : mActions)
		action.performAction(variables);
}

bool Control::conditionsMet(const map<string, string>& variables)
{
	bool result = true;

	// Iterate over all child conditions, calling their conditionMet method
	// with the variables as a parameter
	// If any of these conditions returns false, the conditions are not met.
	for(Condition condition : mConditions)
	{
		if(condition.conditionMet(variables) == false)
			result = false;
	}

	return result;
}

int Control::getChance()
{
	// Return chance
	return mChance;
}

string Control::getText()
{
	// Return text
	return mText;
}