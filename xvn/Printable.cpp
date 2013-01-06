#include "Printable.h"

Printable::Printable() : mIsInitialised(false) { }

void Printable::initialise(const xml_node& node)
{
	mText = node.text().as_string();
}

