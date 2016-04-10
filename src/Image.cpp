#include <utility>
#include <iostream>
#include <istream>
#include <fstream>
#include <memory>

#include "../includes/Image.h"
#include "../includes/KOCREUtility.h"


namespace KOCREngine{

	///<summary>
	///Constructor with image name and image path. Reads, Loads and stores it in memory.
	///</summary>
	Image::Image(const std::string& imageName)
	:	imageInfo(ImageInfo{
			.name = imageName
		})
	{
		if(!getImage())
			std::cout<<"Failed to get image\naborting operation..";
	}


	///<summary>
	///move from another objects.
	///</summary>
	Image::Image(Image&& img)
	:	imageDataArray(std::move(img.imageDataArray)),//the image resource
		imageInfo(std::move(img.imageInfo))
		{
			img.imageInfo.name = "";
			//img.imageDataArray = nullptr;
		}



	///<summary>
	///move assign from another object.
	///</summary>
	Image& Image::operator=(Image&& img)
	{
		//moving all the members.
		using namespace std;
		imageDataArray = std::move(img.imageDataArray);
		imageInfo = std::move(img.imageInfo);
		return *this;
	}

	///<summary>
	///Read a pixel data from the image buffer
	///</summary>
	krgb readPixel(std::unique_ptr<char[]>& imageData, PixelPoint pxl, int width, ImgFmt fmt)
	{
		//UC8 * PixelData = reinterpret_cast<UC8*>(imageDataArray);
		auto bpp = formatByteSize(fmt);

		I32 loc = pointToIndex(pxl, width) * bpp;
		//TODO: make sure to include other bpp size
		return {uint8_t(imageData[loc + bpp - 1]),
				uint8_t(imageData[loc + bpp - 2]),
				uint8_t(imageData[loc + bpp - 3]),
				uint8_t(0)
			};

	}


	void toKRGB(std::unique_ptr<char[]>& source, std::unique_ptr<krgb[]>& dest, ImageInfo imageInfo){
		int width = imageInfo.size.width, 
			height = imageInfo.size.height;
		for(int32_t i = 0; i < height; ++i){
			for(int32_t j = 0; j < width; ++j){
				auto point = PixelPoint{j, i};
				dest[pointToIndex(point, width)] = readPixel(source, point, width, imageInfo.format);
			}
		}
	}

	///<summary>
	///getImage method is the private method of the Image class.
	///imageReader will be the interface to the other parts of the
	///application providing the image format.
	///</summary>
	bool Image::getImage()
	{
		auto imageStream = std::ifstream{imageInfo.name, std::ios_base::in | std::ios_base::binary};

		if(!imageStream.is_open() || !imageStream.good())
			return false;		//failed to open image or the stream is bad.

		//get image width and height
		imageStream.seekg(BITMAPOFFSET::IMGWDT, std::ios::beg)	//seek to the image width info in the file.
		.read(reinterpret_cast<char*>(&(imageInfo.size.width)), BITMAPFIELDSSIZE::IMGWDTSZ)
		.read(reinterpret_cast<char*>(&(imageInfo.size.height)), BITMAPFIELDSSIZE::IMGHGTSZ);

		int16_t bits = 8; 
		imageStream.seekg(BITMAPOFFSET::IMGBPP,std::ios::beg)
		.read(reinterpret_cast<char*>(&bits),2);

		auto fmt = formatByteSize(imageFormat(bits));
		imageInfo.format = imageFormat(bits);
		auto imageLength = imageInfo.size.height * imageInfo.size.width;
		imageDataArray = std::make_unique<krgb[]>( imageLength );	//create an array of colour PixelPoint(32 bit data).
		auto tempDataArray = std::make_unique<char[]>( imageLength * fmt );

		int32_t pixelArrayLoc = 0;
		//load the image array
		imageStream.seekg(BITMAPOFFSET::IMGOFFSET,std::ios::beg)
		.read(reinterpret_cast<char*>(&pixelArrayLoc),4)
		.seekg(pixelArrayLoc,std::ios::beg)
		.read(tempDataArray.get(), imageLength * fmt);



		ConsLog("count: ", imageStream.gcount(),"good:",imageStream.good());
		toKRGB(tempDataArray, imageDataArray, imageInfo);

		return (imageStream.rdstate() == std::ios::goodbit);
	}



	///<summary>
	///This is the interface that can be used to read the image from the imageArray
	///2 params :
	///1). ImgFmt: currently only 24bpp is supported.
	///2). The vector buffer to hold the color unit
	///
	///Desc. Future will make a generic container.
	///</summary>

	bool Image::readImage(std::vector<colorUnit>& imageBuf, ImgFmt format)	//make sure that only a existing vector is passed
	{
		using namespace std;
		static int i = 0;   //only for debug purpose
		bool status = false;	//status of read operation

		// try{
		// for(UI32 row = 0;row < imageHeight; row++)
		// 	for(UI32 column = 0;column < imageWidth-1; column += 3){
		// 		imageBuf.emplace_back({	//Create a temporary "ColorUnit" struct.
		// 			{column, row}	// Temporary "PixelPoint" struct.
		// 			,readPixel({column, row})	//Temporary "krgb" struct.
		// 		});
		// 	}
		// status = true;std::cout << i;
		// }
		// catch(const std::exception& ex)
		// {
		// 	status = false;
		// }
		return status;
	}

	///<summary>
	///read a part of the image from the location
	///</summary>
	bool Image::readPartly(std::vector<colorUnit>& imageData,I32 xStart,I32 yStart,I32 xEnd,I32 yEnd,ImgFmt format)
	{
		// for (I32 row = yStart; row <=  yEnd; row ++)
		// {
		// 	for (I32 column = xStart;column <= xEnd;column += 3)
		// 	{
		// 		imageData.push_back(
		// 								{	//Create a temporary "ColorUnit" struct.
		// 									{row,column}	// Temporary PixelPoint struct.
		// 									,readPixel({row,column})	// Temporary "krgb" struct.
		// 								}
		// 							);
		// 	}
		// }
		return true;
	}

}
