#include "condition.h"

const string Condition::CONDITIONS[] = {
	"is_equal_to",
	"is_not_equal_to",
	"is_less_than",
	"is_less_than_or_equal_to",
	"is_greater_than",
	"is_greater_than_or_equal_to"
};

bool Condition::initialise(const xml_node& node)
{
	// The result of the initialisation
	bool result = true;

	// Set the path
	mPath = xvnu::path(node);

	// If the node has an attribute for the first variable, set it
	if(node.attribute("variable"))
		mVariableName = node.attribute("variable").as_string();
	// If it does not contain this attribute, report the error and set the result flag to false
	else
	{
		cout << "Error@" << mPath << " - \"variable\" attribute not found" << endl;
		result = false;
	}

	// Flag to determine if a valid string was found
	bool contains_valid_comparison = false;

	// Iterate over all valid condition strings
	for(string condition : CONDITIONS)
	{
		// If the an attribute is found that matches this string exactly, it is a constant literal value
		// Set the v strialueng and break from the loop
		if(node.attribute(condition.c_str()))
		{
			mComparison = condition;
			mComparisonVariableValue = node.attribute(condition.c_str()).as_string();
			contains_valid_comparison = true;
			break;
		}
		// Else if the an attribute is found that matches this string + "_variable" it is a variable name
		// Set the variable name string and break from the loop
		else if(node.attribute(string(condition + "_variable").c_str()))
		{
			mComparison = condition;
			mComparisonVariableName = node.attribute(string(condition + "_variable").c_str()).as_string();
			contains_valid_comparison = true;
			break;
		}
	}

	// If the condition did not contain a valid string, report the error and set the result flag to false
	if(contains_valid_comparison == false)
	{
		cout << "Error@" << mPath << " - Valid comparison not found" << endl;
		result = false;
	}

	// Return the result of the initialise
	return result;
}

bool Condition::conditionMet(const map<string, string>& variables)
{
	string variable;
	// If mVariableName has a value in variables, set variable as this 
	if(variables.find(mVariableName) != variables.end())
		variable = variables.at(mVariableName);
	else
	{
		// If it does not have a value, flag a warning and default its value to "0"
		cout << "Info@" << mPath << " - " <<  mVariableName << " not initialised, considered as \"0\"" << endl;
		variable = "0";
	}
	double variable_as_number = stod(variable);

	string comparison_variable = mComparisonVariableValue;
	// If mComparisonVariableValue is empty, the comparison is not a literal and is a variable
	if(comparison_variable.empty())
	{
		// If mComparisonVariableName has a value in variables, set comparison_variable as this
		if(variables.find(mComparisonVariableName) != variables.end())
			comparison_variable = variables.at(mComparisonVariableName);
		else
		{
			// If it does not have a value, flag a warning and default its value to "0"
			cout << "Info@" << mPath << " - " <<  mComparisonVariableName << " not initialised, considered as \"0\"" << endl;
			comparison_variable = "0";
		}
	}
	double comparison_variable_as_numer = stod(comparison_variable);

	// The result of the condition
	bool result;

	// Find the correct comparison operation
	if(mComparison == "is_equal_to")
		result = variable == comparison_variable;
	else if(mComparison == "is_not_equal_to")
		result = variable != comparison_variable;

	string str = (result == true) ? "TRUE" : "FALSE";

	cout << "Info@" << mPath << " - " << str << " - "<< mVariableName 
		<< "(" << variable << ") " << mComparison << " " << mComparisonVariableName << "(" << comparison_variable << ")" << endl;

	// Return the result
	return result;
}