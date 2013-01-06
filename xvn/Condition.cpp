#include "Condition.h"

const string Condition::CONDITIONS[] = {
	"is_equal_to",
	"is_not_equal_to",
	"is_less_than",
	"is_less_than_or_equal_to",
	"is_greater_than",
	"is_greater_than_or_equal_to",
	"is_equal_to_variable",
	"is_not_equal_to_variable",
	"is_less_than_variable",
	"is_less_than_or_equal_to_variable",
	"is_greater_than_variable",
	"is_greater_than_or_equal_to_variable"
};

Condition::Condition() : mIsInitialised(false), mCondition(-1) { }

bool Condition::initialise(const xml_node& node)
{
	if(!mIsInitialised)
	{
		// The node must contain a variable to compare, as defined by the variable attribute
		if(node.attribute("variable"))
		{
			// Get the variable name
			mVariableName = node.attribute("variable").as_string();

			// Iterate over all valid condition strings
			mCondition = 0;
			for(auto condition : CONDITIONS)
			{
				// Find the first attribute that matches a condition string name
				if(node.attribute(condition.c_str()))
				{
					if(mCondition <= 5)
						mComparisonValue = node.attribute(condition.c_str()).as_string();
					else
						mCompairsonVariableName = node.attribute(condition.c_str()).as_string();
					break;
				}
				// If the string did not match any attributes, search the next condition string
				else
					mCondition++;
			}

			if(mCompairsonVariableName.empty() || mCompairsonVariableName.empty())
				mIsInitialised = true;
			else
				mIsInitialised = false;
		}
		else
			mIsInitialised = false;
	}
	return mIsInitialised;
}

bool Condition::conditionMet(const map<string, string>& variables)
{
	if(mIsInitialised)
	{
		string value;
		if(variables.find(mVariableName) != variables.end())
			value = variables.at(mVariableName);
		else
			value = "0";
		float value_float = stof(value);

		string comparison_value;
		if(mComparisonValue.empty())
		{
			if(variables.find(mCompairsonVariableName) != variables.end())
				comparison_value = variables.at(mCompairsonVariableName);
			else
				comparison_value = "0";
		}
		else
			comparison_value = mComparisonValue;
		float comparison_value_float = stof(comparison_value);

		// Index maps to a comparison string in CONDITIONS
		switch(mCondition)
		{
		// Is Equal to
		case (0):
		case (6):
			return value == comparison_value;
		// Is Not Equal to
		case (1):
		case (7):
			return value != comparison_value;
		// Is Less Than
		case (2):
		case (8):
			// TODO
			return false;
			break;
		// Is Less Than Or Equal To
		case (3):
		case (9):
			// TODO
			return false;
			break;
		// Is Greater Than
		case (4):
		case (10):
			// TODO
			return false;
			break;
		// Is Greater Than Or Equal To
		case (5):
		case (11):
			// TODO
			return false;
			break;
		};
	}
	else
		return false;
}