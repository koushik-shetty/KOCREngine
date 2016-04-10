#ifndef _IMAGEHEADER_H_
#define _IMAGEHEADER_H_

#include <vector>
#include <string>
#include <utility>
#include <iterator>
#include <fstream>

#include "BitmapInfo.h"
#include "Rectangle.h"
#include "Pixel.h"

namespace KOCREngine
{


	struct ImageInfo {
		std::string name;
		prop_t size;
		ImgFmt format;
	};

	///<summary>
	/// This is the class that reads the image and stores the data.
	/// This class acts as the interface to other modules to any image. The reading will be fast.
	///</summary>
	class Image	{
		//do not change the order of the declarations.
		typedef PixelIterator Iterator;		  

		image_array imageDataArray;		//This is the pointer to the array that will hold the data. Change to byte array.
		ImageInfo imageInfo;
		bool getImage();

	public:

		///<Image by path and file name.
		Image(const std::string& imageName);

		///< move from another object, Since its a heavy resource
		Image(Image&& img);	//only movable.

		///<  Rule of five(?), any-ways, type is only move(assign)able
		Image& operator=(Image&& img);//only movable

		bool readImage(std::vector<colorUnit>& imageData, ImgFmt format = ImgFmt::B24);

		bool readPartly(std::vector<colorUnit>& imageData,I32 xStart,I32 yStart,I32 xEnd, I32 yEnd, ImgFmt format = ImgFmt::B24);

		inline prop_t getProportion(){ return imageInfo.size; }

		inline std::string getImageName(){return imageInfo.name;}  //returns image name

		// inline krgb readPixel(PixelPoint loc); //read the data at the specified PixelPoint location.

		// inline Iterator begin() {
		// 	return Iterator{imageDataArray};
		// }

		Image(const Image& ) = delete;	//this type is only move constructible
		Image& operator=(const Image&) = delete;	//this type is only moveable so delete the copy assignment op.

		~Image()
		{
			//delete[] imageDataArray;
		}
	};

	

}

#endif //_IMAGEHEADER_H_
