#ifndef IMG_ACQ
#define IMG_ACQ

#include <iostream>
#include <fstream>
#include <stdint.h>
//#include <windows.h>

#include <vector>
#include <exception>
#include <utility>
#include <memory>
//#include<stdexception>
//#include<wingdi.h>

//Custom Headers

#include "BitmapInfo.h"
#include "Image.h"


namespace KOCREngine
{
	///<summary>
	///Class to Prepare and load and hold the image.
	///This acts as the image interface to the rest of the engine.
	///</summary>
	class ImageAcquition
	{
		const std::string imageName;		//image name
		const std::string imageLocation;	//image location
		uint32_t imageHeight, imageWidth;	//image height and width
		uint32_t *imageDataArray;		//This is the pointer to the array that will hold the data

	public:
		ImageAcquition(Image& imageName);
		ImageAcquition(Image&& imageName);
		bool fillArray();
	};

}



#endif //IMG_ACQ
