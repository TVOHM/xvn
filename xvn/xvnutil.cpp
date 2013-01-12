#include "xvnutil.h"

int xvnu::index(const pugi::xml_node& node)
{
	// If node has a parent
	if(node.parent())
	{
		// Iterate over all the parents children, incrementing index
		int idx = 0;
		for(auto& child : node.parent())
		{
			// If the child node matches the node parameter, reutrn the index of the node
			if(child == node)
				return idx;
			// If it is not a match, incremement the counter and continue
			else
				idx++;
		}
		// Should never reach here
		return -1;
	}
	// If the node has no parent return -1
	else
		return -1;
}

std::string xvnu::path(const pugi::xml_node& node)
{
	// Get the string for this node
	string str = "(" + std::to_string(xvnu::index(node)) + ")" + string(node.name());

	// If the node has a parent, recursivly call this function, adding this nodes location to the end of the string
	if(node.parent() && node.parent().type() != xml_node_type::node_document)
		return xvnu::path(node.parent()) + " " + str;
	// If the node has no parent, return and empty string and end the recursive loop
	else
		return string();
}

std::string xvnu::text(const pugi::xml_node& node)
{
	// TODO
	return "";
}