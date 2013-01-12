#ifndef CONTROL_H
#define CONTROL_H

#include <vector>

#include "action.h"
#include "condition.h"

/// <summary>Control class used by the Text class to determine what happens after the text is displayed.</summary>
class Control
{
public:
	/// <summary>Initialises the control.</summary>
	/// <param name="node">The action node to load the control from.</param>
	/// <returns>True if initialisation ok, false if failed.</returns>
	/// <remarks>If initialisation fails, error is printed to console.</remarks>
	bool initialise(const xml_node& node);

	/// <summary>Performs all the child actions of this control.</summary>
	/// <param name="variables">The current state of the game variables.</param>
	void performActions(map<string, string>& variables);

	/// <summary>Asserts all child conditions of this control.</summary>
	/// <param name="variables">The current state of the game variables.</param>
	/// <returns>True if ALL child conditions were met, else returns false.</returns>
	bool conditionsMet(const map<string, string>& variables);

	/// <summary>Gets the text of this control.</summary>
	/// <returns>The well-formatted contents of the controls text node(s).</returns>
	string getText();

	/// <summary>Gets the chance of this control.</summary>
	/// <returns>Chance as an integer.</returns>
	int getChance();
private:
	/// <summary>The child conditions of this control.</summary>
	vector<Condition> mConditions;

	/// <summary>The child actions of this control.</summary>
	vector<Action> mActions;

	/// <summary>The chance of this control.</summary>
	/// <remarks>Defaults to 1 if not defined in the node.</remarks>
	int mChance;

	/// <summary>The well-formatted text of this control.</summary>
	string mText;
};

#endif /* CONTROL_H */