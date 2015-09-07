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

	typedef struct
	{
		PixelLoc_t x;
		PixelLoc_t y;
	}Pixels;

	typedef struct
	{
		UC8 red;
		UC8 green;
		UC8 blue;
	}krgb; //image component holder;

	typedef struct
	{
		Pixels pixel;
		krgb rgb;
	}colorUnit;

	///<summary>
	/// This is the class that reads the image and stores the data.
	/// This class acts as the interface to other modules to any image. The reading will be fast.
	///</summary>
	class ImageReader
	{
		//do not change the order of the declarations.
		std::string imageName;		//Image name
		std::string imageLoc;
		std::ifstream imageStream;

		I32 imageHeight,
			imageWidth;	// image height and width
		std::unique_ptr<char> imageDataArray;		//This is the pointer to the array that will hold the data. Change to byte array.

		bool getImage(); // Fetch image file and read the contents.


	public:


		///<image is in the application directory or sub-directory thereof.
		ImageReader(const std::string& imageName);


		///<Image by path and file name.
		ImageReader(const std::string& imageName, const std::string& imageLocation);


		///< move from another object, Since its a heavy resource
		ImageReader(ImageReader&& imgrdr);	//only movable.


		///<  Rule of five(?), any-ways, type is only move(assign)able
		ImageReader& operator=(ImageReader&& imgrdr);//only movable

		bool readImage(std::vector<colorUnit>& imageData, ImgFmt format = ImgFmt::B24);

		bool readPartly(std::vector<colorUnit>& imageData,I32 xStart,I32 yStart,I32 xEnd, I32 yEnd, ImgFmt format = ImgFmt::B24);

		inline void getProportion(I32& width,I32& height);

		inline std::string getImageName(bool includePath)const ;  //returns image name

		inline std::string getImageLoc() const;		//returns image location.

		inline krgb readPixel(Pixels loc); //read the data at the specified Pixels location.

		ImageReader(const ImageReader& ) = delete;	//this type is only move constructible
		ImageReader& operator=(const ImageReader&) = delete;	//this type is only moveable so delete the copy assignment op.

		~ImageReader()
		{
			//delete[] imageDataArray;
		}
	};



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
