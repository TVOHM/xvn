#ifndef CONDITION_H
#define CONDITION_H

#include <map>

#include "xvnutil.h"

/// <summary>Condition class used to control which controls are visible based upon game variables.</summary>
class Condition
{
public:
	/// <summary>Initialises the condition.</summary>
	/// <param name="node">The condition node to load the condition from.</param>
	/// <returns>True if initialisation ok, false if failed.</returns>
	/// <remarks>If initialisation fails, error is printed to console.</remarks>
	bool initialise(const xml_node& node);

	/// <summary>Determines if the condition is currently true or false.</summary>
	/// <param name="variables">The current game variable map.</param>
	/// <returns>True if the condition is met, else returns false.</returns>
	/// <remarks>If a tested variable is not present in the variables map, it is assume to be "0".</remarks>
	bool conditionMet(const map<string, string>& variables);
private:
	/// <summary>Contains all valid condition strings</summary>
	const static string CONDITIONS[];

	/// <summary>The name of the first variable to compare.</summary>
	string mVariableName;

	/// <summary>The name of the second variable to compare.</summary>
	/// <remarks>If this is empty, the second comparison value is a constant value found in mComparisonVariableValue.</remarks>
	string mComparisonVariableName;

	/// <summary>The constant value to compare the first variable against.</summary>
	/// <remarks>If this is empty, the second comparison value is a variable whose name is found in mComparisonVariableName.</remarks>
	string mComparisonVariableValue;

	/// <summary>The string represnting the type of comparison.</summary>
	string mComparison;

	/// <summary>The path of the node this Condition was constructed from.</summary>
	string mPath;
};

#endif /* CONDITION_H */