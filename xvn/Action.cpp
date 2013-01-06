#include "Action.h"

const string Action::ACTIONS[] = {
	"set",
	"multiply",
	"divide",
	"increase",
	"decrease"
};

Action::Action() : mIsInitialised(false), mAction(-1) { }

bool Action::initialise(const xml_node& node)
{
	if(!mIsInitialised)
	{
		if(node.attribute("variable"))
		{
			mVariableName = node.attribute("variable").as_string();

			mAction = 0;
			string name = node.name();
			for(auto& action : ACTIONS)
			{
				if(name == action)
				{
					string last_attribute = node.last_attribute().name();
					if(last_attribute.substr(last_attribute.rfind('_')) == "variable")
						mEffectorVariableName = node.last_attribute().value();
					else
						mEffectorValue = node.last_attribute().value();
					break;
				}
				else
					mAction++;
			}

			if(!mEffectorVariableName.empty() || !mEffectorValue.empty())
				mIsInitialised = true;
			else
				mIsInitialised = false;
		}
		else
			mIsInitialised = false;
		}
	return mIsInitialised;
}

void Action::doAction(map<string, string>& variables)
{
	// If acting_variable_value is empty, no valid action was found
	if(mIsInitialised)
	{
		string value;
		if(variables.find(mVariableName) != variables.end())
			value = variables.at(mVariableName);
		else
			value = "0";
		float value_float = stof(value);

		string effector_value;
		if(mEffectorValue.empty())
		{
			if(variables.find(mEffectorVariableName) != variables.end())
				effector_value = variables.at(mEffectorVariableName);
			else
				effector_value = "0";
		}
		else
			effector_value = mEffectorValue;
		float effector_value_float = stof(effector_value);

		// Index maps to a comparison string in ACTIONS
		switch(mAction)
		{
		// Set
		case (0):
			variables[mVariableName] = effector_value;
			return;
		// Multiply
		case (1):
			variables[mVariableName] = to_string(value_float * effector_value_float);
			return;
		// Divide
		case (2):
			variables[mVariableName] = to_string(value_float / effector_value_float);
			return;
		// Increase
		case (3):
			variables[mVariableName] = to_string(value_float + effector_value_float);
			return;
		// Decrease
		case (4):
			variables[mVariableName] = to_string(value_float - effector_value_float);
			return;
		};
	}
}