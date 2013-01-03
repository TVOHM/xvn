#define cimg_use_png
#include "CImg.h"
using namespace cimg_library;

int main(int argc, char* argv[])
{
	CImg<unsigned char> img("images//char.png");
	CImg<unsigned char> render(img.width(),img.height(),1,3,255);
	render.draw_image(0,0,0,0,img,img.get_channel(3),1,255).display();
	return 0;
}