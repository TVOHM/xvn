#include "text.h"

int main(int argc, char* argv[])
{
	pugi::xml_document doc;
	doc.load_file("game.xml");
	map<string, string> var;
	/*
	// Enable CImg quiet exception mode
	cimg::exception_mode(0);
	CImg<unsigned char> img("images//char.png");
	CImg<unsigned char> render(img.width(),img.height(),1,3,255);
	render.draw_image(0,0,0,0,img,img.get_channel(3),1,255).display();
	*/
	return 0;
}