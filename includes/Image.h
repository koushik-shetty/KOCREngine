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
	///<summary>
	/// This is the class that reads the image and stores the data.
	/// This class acts as the interface to other modules to any image. The reading will be fast.
	///</summary>
	class Image {
		//do not change the order of the declarations.
		typedef PixelIterator iterator;
		typedef const PixelIterator const_iterator;
		image_array image_data_array;		//This is the pointer to the array that will hold the data. Change to byte array.
		ImageInfo image_info;
		bool getImage();

	public:

		///<Image by path and file name.
		Image(const std::string& imageName);

		///< move from another object, Since its a heavy resource
		Image(Image&& img);	//only movable.

		///<  Rule of five(?), any-ways, type is only move(assign)able
		Image& operator=(Image&& img);//only movable

		inline prop_t getProportion(){ return image_info.size; }

		inline std::string getImageName(){return image_info.name;}  //returns image name
		
		iterator begin() {
			return PixelIterator{&image_data_array[0], image_info};
		}
		
		const_iterator cbegin() {
			return begin();
		}
		
		iterator end() {
			return PixelIterator{
				image_data_array.get() + imageLength(image_info.size)
				, image_info				
			};
		}
		
		const_iterator cend() {
			return end();
		}
		
		Image(const Image& ) = delete;	//this type is only move constructible
		
		Image& operator=(const Image&) = delete;	//this type is only moveable so delete the copy assignment op.

		~Image()
		{
			//delete[] imageDataArray;
		}
	};

	

}

#endif //_IMAGEHEADER_H_
