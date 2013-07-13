#pragma once

#include <string>

class Bitmap {
	/*************** Variables ***************/
public:
	enum Format {
		Format_Grayscale = 1,					/**< one channel: grayscale */
		Format_GrayscaleAlpha = 2,				/**< two channels: grayscale and alpha */
		Format_RGB = 3,							/**< three channels: red, green, blue */
		Format_RGBA = 4							/**< four channels: red, green, blue, alpha */
	};

private:
	//Format of the colors for the Bitmap.
	Format							_format;

	//Width and height of the bitmap.
	unsigned						_width;
	unsigned						_height;

	//An array of pixels to hold the entirety of the bitmap.
	unsigned char*					_pixels;

	/*************** Methods ***************/
public:        
    Bitmap(unsigned width, unsigned height, Format format, const unsigned char* pixels = NULL);
    Bitmap(const Bitmap& other);
    Bitmap& operator =(const Bitmap& other);
    ~Bitmap();

	//Reads a bitmap from a path that you send.
    static Bitmap					bitmapFromFile(std::string filePath);
	
	//Returns a pointer to the start of the pixel at the given coordinates. The size of the pixel depends on the `Format` of the image.
    unsigned char*					getPixel(unsigned int column, unsigned int row) const;

	//Sets the raw pixel data at the given coordinates. The size of the pixel depends on the `Format` of the bitmap.
    void							setPixel(unsigned int column, unsigned int row, const unsigned char* pixel);

	//Vertically flips the bitmap (duh!).
    void							flipVertically();

	//Rotates the bitmap 90 degrees CCW.
    void							rotate90CounterClockwise();

	//Copies a rectangular area from the given source bitmap into this bitmap.
    void							copyRectFromBitmap(const Bitmap& src, unsigned srcCol, unsigned srcRow, 
													   unsigned destCol, unsigned destRow,
													   unsigned width, unsigned height);

    unsigned						width() const;
    unsigned						height() const;
    Format							format() const;
    unsigned char*					pixelBuffer() const;
        
private:
	void							_set(unsigned width, unsigned height, Format format, const unsigned char* pixels);
	static void						_getPixelOffset(unsigned col, unsigned row, unsigned width, unsigned height, Format format);
};
