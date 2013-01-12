#ifndef ACTION_H
#define ACTION_H

#include <map>

#include "xvnutil.h"

/// <summary>Action class used by controls to act upon internal system variables.</summary>
class Action
{
public:
	/// <summary>Initialises the action.</summary>
	/// <param name="node">The action node to load the action from.</param>
	/// <returns>True if initialisation ok, false if failed.</returns>
	/// <remarks>If initialisation fails, error is printed to console.</remarks>
	bool initialise(const xml_node& node);

	/// <summary>Performs the action.</summary>
	/// <param name="variables">The current game variable map. This will be modified by this call.</param>
	/// <remarks>If any variable is not present in the variables map, it is assume to be "0".</remarks>
	void performAction(map<string, string>& variables);
private:
	/// <summary>Contains all valid action strings</summary>
	const static string ACTIONS[];

	/// <summary>The name of the variable to act on.</summary>
	string mVariableName;

	/// <summary>The name of the variable to be used in conjuction with the action on the subject variable.</summary>
	/// <remarks>If this is empty, the effector value is a constant value found in mEffectorVariableValue.</remarks>
	string mEffectorVariableName;

	/// <summary>The constant value used in conjuction with the action on the subject variable.</summary>
	/// <remarks>If this is empty, the second comparison value is a variable whose name is found in mEffectorVariableName.</remarks>
	string mEffectorVariableValue;

	/// <summary>The string represnting the type of action to be done.</summary>
	string mAction;

	/// <summary>The path of the node this Action was constructed from.</summary>
	string mPath;
};

#endif /* ACTION_H */