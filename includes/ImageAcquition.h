#ifndef IMG_ACQ
#define IMG_ACQ

#include<iostream>
#include<fstream>
#include<stdint.h>
//#include<windows.h>

#include<vector>
#include<exception>
#include<utility>
#include<memory>
//#include<stdexception>
//#include<wingdi.h>

//Custom Headers

#include"Wrappers_Utilities.h"

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
		UI32 imageHeight, imageWidth;	//image height and width
		UI32 *imageDataArray;		//This is the pointer to the array that will hold the data

	public:
		ImageAcquition(ImageReader& imageName);
		ImageAcquition(ImageReader&& imageName);
		bool fillArray();
	};

}



#endif //IMG_ACQ
