#include "Engine.h"

const string Engine::CONDITIONS[] = {
	"is_equal_to",
	"is_not_equal_to",
	"is_less_than",
	"is_less_than_or_equal_to",
	"is_greater_than",
	"is_greater_than_or_equal_to",
	"is_equal_to_variable",
	"is_not_equal_to_variable",
	"is_less_than_variable",
	"is_less_than_or_equal_to_variable",
	"is_greater_than_variable",
	"is_greater_than_or_equal_to_variable"
};

const string Engine::ACTIONS[] = {
	"set",
	"multiply",
	"divide",
	"increase",
	"decrease"
};

bool Engine::load(string file)
{
	// The result of the load process, will be flagged as false if anything fails
	bool result = true;

	xml_parse_result parse_result = mDocument.load_file(file.c_str());

	// If the parse failed, report the reason and return false
	if(parse_result == false)
	{
		cout << "Error: Could not load file " << file << endl << parse_result.description() << endl;
		result = false;
		return result;
	}

	// Set the game as the first child of the document node
	mGame = mDocument.first_child();

	// Validate all elements in the game
	result = validateElements();

	// If the result was ok, display the main window
	if(result == true)
	{
		int width = 800;
		if(mGame.attribute("width"))
			width = mGame.attribute("width").as_int();
		int height = 600;
		if(mGame.attribute("height"))
			height = mGame.attribute("height").as_int();
		string title = "xvn "XVN_VERSION;
		if(mGame.attribute("title"))
			title = mGame.attribute("title").as_string();
		mDisplay.assign(width, height, title.c_str());
	}

	return result;
}

bool Engine::validateElements()
{
	bool result = true;

	// Iterate over each child (element) in the game and validate it
	for(auto& element : mGame)
	{
		// Ensure that there is only 1 element present in the game with this name
		string element_name = element.name();
		int num_name = 0;
		for(auto child : mGame.children(element_name.c_str()))
			num_name++;
		if(num_name > 1)
		{
			cout << "Error: Duplicate name " << element_name << endl;
			result = false;
		}

		// If the element contains a character image, attempt to load it
		if(element.attribute("character"))
		{
			string character_image_name = element.attribute("character").as_string();
			// Only attempt to load the image if this image has not already been loaded
			if(mImages.find(character_image_name) == mImages.end())
			{
				CImg<unsigned char> character;
				try
				{
					character.load(character_image_name.c_str());
					mImages[character_image_name] = character;
				}
				catch(...)
				{
					cout << "Error @ " << element_name << ": Could not load character image " << character_image_name << endl;
					result = false;
				}
			}
		}

		// If the element contains a background image, attempt to load it
		if(element.attribute("background"))
		{
			string background_image_name = element.attribute("background").as_string();
			// Only attempt to load the image if this image has not already been loaded
			if(mImages.find(background_image_name) == mImages.end())
			{
				CImg<unsigned char> background;
				try
				{
					background.load(background_image_name.c_str());
					mImages[background_image_name] = background;
				}
				catch(...)
				{
					cout << "Error @ " << element_name << ": Could not load character image " << background_image_name << endl;
					result = false;
				}
			}
		}

		// Validate the controls contained by this element
		if(validateControls(element) == false)
			result = false;
	}

	return result;
}

bool Engine::validateControls(const xml_node& element)
{
	bool result = true;

	string element_name = element.name();

	// Keep track of the control number
	int control_index = 1;

	// Iterate over all controls in the element
	for(auto& control : element.children())
	{
		// The destination for this control is its name
		string destination = control.name();

		bool destination_exists = false;
		// Ensure the destination exists, iterate over all elements and check their names
		for(auto& game_element : mGame)
		{
			string name = game_element.name();
			if(name == destination)
			{
				destination_exists = true;
				break;
			}
		}

		//If the destination does not exist, report an error
		if(destination_exists == false)
		{
			cout << "Error @ " << element_name << " " << "Control " << control_index << ": Invalid destination \"" << destination << "\"" << endl;
			result = false;
		}

		// Validate the actions of this control
		if(validateActions(control, control_index) == false)
			result = false;

		// Validate the conditions of the control
		if(validateConditions(control, control_index) == false)
			result = false;

		control_index++;
	}

	return result;
}

bool Engine::validateConditions(const xml_node& control, int control_index)
{
	bool result = true;

	// Get the name of the parent element
	string element_name = control.parent().name();

	// Keep track of the condition index
	int condition_index = 1;
	for(auto& condition : control.children("if"))
	{
		// The control must contain a variable to compare, as defined by the variable attribute
		if(condition.attribute("variable") == false)
		{
			cout << "Error @ " << element_name << " " << "Control " << control_index << " Condition " << condition_index 
				<< ": Missing required \"variable\" attribute" << endl;
			result = false;
		}

		// Iterate through all valid condition strings and assert it contains one of them as an attribute
		bool valid_condition_found = false;
		for(auto condition_string : CONDITIONS)
		{
			if(condition.attribute(condition_string.c_str()))
			{
				valid_condition_found = true;
				break;
			}
		}
		 // If there was no match found, report an error
		if(valid_condition_found == false)
		{
			cout << "Error @ " << element_name << " " << "Control " << control_index << " Condition " << condition_index 
				<< ": Missing valid condition attribute" << endl;
			result = false;
		}

		//Increase the condition index
		condition_index++;
	}
	return result;
}

bool Engine::validateActions(const xml_node& control, int control_index)
{
	bool result = true;

	// Get the name of the parent element
	string element_name = control.parent().name();

	// Keep track of the condition index
	int action_index = 1; // Iterate over all children in the control
	for(auto& action : control.children())
	{
		string name = action.name();
		// Every child without the name "if" is an action
		if(name != "if")
		{
			// The name of the action is the operation, check it is a valid one
			bool valid_action_found = false;
			for(auto action_string : ACTIONS)
			{
				if(action_string == name)
				{
					valid_action_found = true;
					break;
				}
			}

			// If it does not match, report an error
			if(valid_action_found == false)
			{
				cout << "Error @ " << element_name << " " << "Control " << control_index << " Condition " << action_index 
					<< ": Unknown operation \"" << name << "\"" << endl;
				result = false;
			}

			// The action must contain a variable to act on, as defined by the variable attribute
			if(action.attribute("variable") == false)
			{
				cout << "Error @ " << element_name << " " << "Control " << control_index << " Condition " << action_index 
					<< ": Missing required \"variable\" attribute" << endl;
				result = false;
			}
			int num_attributes = 0;
			for(auto attribute : action.attributes())
				num_attributes++;
			// The action should only contain two attributes
			if(num_attributes != 2)
			{
				cout << "Error @ " << element_name << " " << "Control " << control_index << " Condition " << action_index 
					<< ": Invalid number of attributes (expects 2)" << endl;
				result = false;
			}

			//Increase the action index
			action_index++;
		}
	}
	return result;
}