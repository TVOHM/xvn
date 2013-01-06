#include "pugixml.hpp"
using namespace pugi;

#define cimg_use_png
#include "CImg.h"
using namespace cimg_library;

#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <random>
using namespace std;

#define XVN_VERSION "0.0.2 DEVELOPMENT"

class Engine
{
public:
	bool load(string file);
	void run();
private:
	bool validateElements();
	bool validateConditions(const xml_node& control, int control_index);
	bool validateActions(const xml_node& control, int control_index);
	bool validateControls(const xml_node& element);
	enum ControlType { XVN_CONTROL_TYPE_FLOW, XVN_CONTROL_TYPE_PROMPT };
	vector<xml_node&> getControls(ControlType control_type, const xml_node& element);
	void executeActions(const xml_node& control);

	CImgDisplay mDisplay;
	map<string, string> mVariables;
	map<string, CImg<unsigned char>> mImages;
	xml_document mDocument;
	xml_node mGame;

	const static string CONDITIONS[];
	const static string ACTIONS[];
};