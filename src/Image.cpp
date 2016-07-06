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
	{
		image_info.name = imageName;
		if(!getImage())
			std::cout<<"Failed to get image\naborting operation..";
	}


	///<summary>
	///move from another objects.
	///</summary>
	Image::Image(Image&& img)
	:	image_data_array(std::move(img.image_data_array)),//the image resource
		image_info(std::move(img.image_info))
		{
			img.image_info.name = "";
			//img.imageDataArray = nullptr;
		}



	///<summary>
	///move assign from another object.
	///</summary>
	Image& Image::operator=(Image&& img)
	{
		//moving all the members.
		using namespace std;
		image_data_array = std::move(img.image_data_array);
		image_info = std::move(img.image_info);
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


	void toKRGB(std::unique_ptr<char[]>& source, std::unique_ptr<krgb[]>& dest, ImageInfo image_info){
		int width = image_info.size.width, 
			height = image_info.size.height;
		for(int32_t i = 0; i < height; ++i){
			for(int32_t j = 0; j < width; ++j){
				auto point = PixelPoint{j, i};
				dest[pointToIndex(point, width)] = readPixel(source, point, width, image_info.format);
			}
		}
	}

	///<summary>
	///getImage method is the private method of the Image class.
	///Image will be the interface to the other parts of the
	///application providing the image format.
	///</summary>
	bool Image::getImage()	{
		auto imageStream = std::ifstream{image_info.name, std::ios_base::in | std::ios_base::binary};

		if(!imageStream.is_open() || !imageStream.good())
			return false;		//failed to open image or the stream is bad.

		//get image width and height
		imageStream.seekg(BITMAPOFFSET::IMGWDT, std::ios::beg)	//seek to the image width info in the file.
		.read(reinterpret_cast<char*>(&(image_info.size.width)), BITMAPFIELDSSIZE::IMGWDTSZ)
		.read(reinterpret_cast<char*>(&(image_info.size.height)), BITMAPFIELDSSIZE::IMGHGTSZ);

		int16_t bits = 8; 
		imageStream.seekg(BITMAPOFFSET::IMGBPP,std::ios::beg)
		.read(reinterpret_cast<char*>(&bits),2);

		auto fmt = formatByteSize(imageFormat(bits));
		image_info.format = imageFormat(bits);
		auto imageLength = image_info.size.height * image_info.size.width;
		image_data_array = std::make_unique<krgb[]>( imageLength );	//create an array of colour PixelPoint(32 bit data).
		auto tempDataArray = std::make_unique<char[]>( imageLength * fmt );

		int32_t pixelArrayLoc = 0;
		//load the image array
		imageStream.seekg(BITMAPOFFSET::IMGOFFSET,std::ios::beg)
		.read(reinterpret_cast<char*>(&pixelArrayLoc),4)
		.seekg(pixelArrayLoc,std::ios::beg)
		.read(tempDataArray.get(), imageLength * fmt);



		ConsLog("count: ", imageStream.gcount(),"good:",imageStream.good());
		toKRGB(tempDataArray, image_data_array, image_info);

		return (imageStream.rdstate() == std::ios::goodbit);
	}

}
