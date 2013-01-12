#ifndef XVNUTIL_H
#define XVNUTIL_H

#include <iostream>
#include <sstream>
using namespace std;

#include "pugixml.hpp"
using namespace pugi;

/// <summary>xvn utility namespace</summary>
namespace xvnu
{
	/// <summary>Returns the index of a pugi node within its parent.</summary>
	/// <param name="node">The subject node.</param>
	/// <returns>The index of the node. If the node has no parent, returns -1.</returns>
	int index(const xml_node& node);

	/// <summary>Generates a string representing the path of a node.</summary>
	/// <param name="node">The subject node.</param>
	/// <returns>The path of the node as a string.</returns>
	string path(const xml_node& node);
	
	/// <summary>Returns well-formatted text from the inner of the node.</summary>
	/// <param name="node">The subject node.</param>
	/// <returns>The well-formatted text of the inner of the node in a string.</returns>
	string text(const xml_node& node);
}

#endif /* XVN_UTIL_H */