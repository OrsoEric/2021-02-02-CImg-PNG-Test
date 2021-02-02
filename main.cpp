//  Cimg +jpeg
//https://stackoverflow.com/questions/46055720/cannot-load-any-image-with-cimg/46058914#
//  Compile jpeglib
//https://stackoverflow.com/questions/12652178/compiling-libjpeg

//tried libjpeg
//tried msys with mingw
//give up
//try libpng http://www.libpng.org/pub/png/libpng.html
//Need zlib as well -.-

//CIMG reference
//https://cimg.eu/reference/structcimg__library_1_1CImg-members.html

//Build option:
//-std=gnu++11

//STD
#include <string>
//CImg
#define cimg_use_png
#define cimg_display 0
#include "CImg.h"
using namespace cimg_library;
//PNG library
#include "png.h"
/*
struct Color
{
    Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0) :
        rgba{r, g, b, a}
    {}

    // ...
    unsigned char rgba[4]{};
};
*/

//CImg wrapper. Add an abstraction layer to CImg to use less verbose Point and Color structures
class CImg_wrapper
{
	public:
		//2D Point
		typedef struct _Point_2d
		{
			int g_s32_x, g_s32_y;
		} Point_2d;
		//3 channel color
		typedef struct _Color_3u8
		{
			unsigned char g_u8p_rgb[3];
		} Color_3u8;
		//Draw text on an image
		template<typename T>
		static void draw_text(CImg<T>& image, Point_2d origin, std::string text, Color_3u8 foreground_color, float opacity, int font_size )
		{
			image.draw_text(origin.g_s32_x, origin.g_s32_y, text.c_str(), foreground_color.g_u8p_rgb, 0, opacity, font_size);
			return;
		}
		//Draw a line on an image
		template<typename T>
		static void draw_line(CImg<T>& image, Point_2d p1, Point_2d p2, Color_3u8 color, float transparency)
		{
			image.draw_line(p1.g_s32_x, p1.g_s32_y, p2.g_s32_x, p2.g_s32_y, color.g_u8p_rgb, transparency);
			return;
		}
};	//CImg_wrapper

//DEMO
int main(int argc, char** argv)
{
	//Create image
    CImg<float> image
    (
		//width
		200,
		//height
		100,
		//Depth. 1 for a 2D image
		1,
		//Number of channels
		3
    );
	//draw text on the image
	CImg_wrapper::draw_text(image, (CImg_wrapper::Point_2d){20, 10}, std::string("Shaka"), (CImg_wrapper::Color_3u8){0,0,255}, 0.9f, 24 );
	//draw a line on the image
	CImg_wrapper::draw_line(image, (CImg_wrapper::Point_2d){20, 90}, (CImg_wrapper::Point_2d){190, 10}, (CImg_wrapper::Color_3u8){0,255,0}, 0.9f );
	//The compiler is able to deduce the type from just the brackets if needed
	//CImg_wrapper::draw_line(image, {20, 90}, {190, 10}, {0,255,0}, 0.9f );
	//Save image on file
    image.save("file.png");

    return 0;
}
