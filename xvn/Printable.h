#include <string>
using namespace std;

#include "pugixml.hpp"
using namespace pugi;

class Printable
{
public:
	Printable();
	string getText();
	string getText(int substring_length);
protected:
	void initialise(const xml_node& node);
	bool mIsInitialised;
private:
	string mText;
};