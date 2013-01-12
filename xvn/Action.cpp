#include "action.h"

const string Action::ACTIONS[] = {
	"set",
	"increase",
	"decrease",
	"multiply",
	"divide"
};

bool Action::initialise(const xml_node& node)
{
	// The result of the initialisation
	bool result = true;

	// Set the path
	mPath = xvnu::path(node);

	// Get the action name
	string action = node.name();
	// Iterate over all valid action strings
	bool action_is_valid = false;
	for(string str : ACTIONS)
	{
		// If it is a valid action, set the flag true and break from the loop
		if(str == action)
		{
			action_is_valid = true;
			break;
		}
	}

	// If the boolean flag is still in a false state, no match was found. Report error and set results flag false.
	if(action_is_valid == false)
	{
		cout << "Error@" << mPath << " - \"" << action << "\" is not a valid action" << endl;
		result = false;
	}

	// Set the action
	mAction = action;

	// If the node has an attribute for the first variable, set it
	if(node.attribute("variable"))
		mVariableName = node.attribute("variable").as_string();
	// If it does not contain this attribute, report the error and set the result flag to false
	else
	{
		cout << "Error@" << mPath << " - \"variable\" attribute not found" << endl;
		result = false;
	}

	// Iterate over all attributes to find the second effector attribute
	for(auto& attribute : node.attributes())
	{
		// Get the attributes name
		string attribute_name = attribute.name();

		// Only consider attributes with names starting with "as", "to" or "by" as effector attributes.
		if(attribute_name.substr(0,2) == "as" || attribute_name.substr(0,2) == "to" || attribute_name.substr(0,2) == "by")
		{
			// If the end of the attributes name is "_variable", the attribute value is the effector variables name
			if(attribute_name.rfind("_") != string::npos && attribute_name.substr(attribute_name.rfind("_")) == "_variable")
				mEffectorVariableName = attribute.value();
			// Else the attribute value is the effector's literal value i.e. "123"
			else
				mEffectorVariableValue = attribute.value();
			break;
		}
	}

	// If both effector strings are empty, no suitable attribute was found. Report the error and set the result flag to false.
	if(mEffectorVariableValue.empty() && mEffectorVariableName.empty())
	{
		cout << "Error@" << mPath << " - no valid effector attribute found" << endl;
		result = false;
	}

	// Return the result of the initialise
	return result;
}

void Action::performAction(map<string, string>& variables)
{
	string variable;
	// If mVariableName has a value in variables, set variable as this 
	if(variables.find(mVariableName) != variables.end())
		variable = variables.at(mVariableName);
	else
	{
		// If it does not have a value, flag a warning and default its value to "0"
		// Only flag this info if the action IS NOT set (set should be used to initialise this variable!)
		if(mAction != "set")
			cout << "Info@" << mPath << " - " <<  mVariableName << " not initialised, considered as \"0\"" << endl;
		variable = "0";
	}
	double variable_as_number = stod(variable);

	string effector_variable = mEffectorVariableValue;
	// If mEffectorVariableValue is empty, the effector is not a literal and is a variable
	if(effector_variable.empty())
	{
		// If mComparisonVariableName has a value in variables, set comparison_variable as this
		if(variables.find(mEffectorVariableName) != variables.end())
			effector_variable = variables.at(mEffectorVariableName);
		else
		{
			// If it does not have a value, flag a warning and default its value to "0".
			cout << "Info@" << mPath << " - " <<  mEffectorVariableName << " not initialised, considered as \"0\"" << endl;
			effector_variable = "0";
		}
	}
	double comparison_variable_as_numer = stod(effector_variable);

	// Find the correct action operation
	if(mAction == "set")
		variables[mVariableName] = effector_variable;
	else if(mAction == "increase")
		variables[mVariableName] = to_string(variable_as_number + comparison_variable_as_numer);
	else if(mAction == "decrease")
		variables[mVariableName] = to_string(variable_as_number - comparison_variable_as_numer);
	else if(mAction == "multiply")
		variables[mVariableName] = to_string(variable_as_number * comparison_variable_as_numer);
	else if(mAction == "divide")
		variables[mVariableName] = to_string(variable_as_number + comparison_variable_as_numer);

	// Report the result of the action
	cout << "Info@" << mPath << " - " << mVariableName << " = " << variables[mVariableName] <<
		" [from (" << variable << ") by " << mAction << " " << mEffectorVariableName << "(" << effector_variable << ")]" << endl;
}