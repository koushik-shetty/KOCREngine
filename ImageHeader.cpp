#include"ImageAcquition.h"


using KOCREngine::ImageReader;define

///<summary>
///Constructor that sets the image name and reads the image
///from the file and stores it in memory.
///The image is read from the
///current directory as that of the application or the System Temp directory.
///</summary>
ImageReader(const std::string& imageName) : imageName(imageName),imageLoc() , imageStream(imageName)
{
	if(!getImage())
		std::cout<<"Failed to get image\naborting operation..";

}



///<summary>
///Constructor with image name and image path. Reads, Loads and stores it in memory.
///</summary>
ImageReader::ImageReader(const std::string& imageName,const std::string& imageLoc)
: imageName(imageName), imageLoc(imageLoc), imageStream(imageLoc+"\\"+imageLoc)
{
	if(!getImage())
		std::cerr<<"Failed to get image\naborting operation..";
}



///<summary>
///move from another objects.
///</summary>
ImageReader(ImageReader&& imgrdr)
:	imageName(std::move(imgrdr.imageName)),//imageName
	imageLoc(std::move(imgrdr.imageLoc)),//Image location
	imageStream(std::move(imgrdr.imageStream)),//The stream that interfaces the image
	imageDataArray(std::move(imgrdr.imageDataArray))//the image resource
	{
		imgrdr.imageName = "";
		imgrdr.imageLoc = "";
		//imgrdr.imageDataArray = nullptr;
	}



///<summary>
///move assign from another object.
///</summary>
ImageReader& operator=(ImageReader&& imgrdr)
{
	//moving all the members. please be correct.:-)
	using namespace std;
	imageName = move(imgrdr.imageName);
	imageLoc = move(imgrdr.imageLoc);
	imageStream = move(imgrdr.imageStream);
	imageDataArray = move(imgrdr.imageDataArray);
	return *this;
}




///<summary>
///getImage method is the private method of the ImageReader class.
///imageReader will be the interface to the other parts of the
///application providing the image format.
///</summary>
bool ImageReader::getImage()
{
	using namespace std;
	bool status = true;
	//C8 readBuffer[10] = {'\0'}; //utility buffer to hold the temporary data.
	I32 pixelArrayLoc = 0;

	//imageStream.open(this->imageLoc + this->imageName,std::ios::binary);//open a  stream containing the image

	if(!imageStream.is_open() || !imageStream.good())
		return false;		//failed to open image or the stream is bad.


	imageStream.seekg(BITMAPOFFSET::IMGWDT,ios::beg);	//seek to the image width info in the file.

	if(!imageStream.read(reinterpret_cast<char*>(&imageWidth),4))		//read image width from the file
		status = false;
		//TODO : instead of returning false throw(?)

	if(!imageStream.read(reinterpret_cast<char*>(&imageHeight),4))			//Load image height info.
		status = false;



	imageDataArray = unique_ptr<UC8[]>(new UC8[imageHeight * imageWidth * 4]);	//create an array of colour pixels(32 bit data).


	imageStream.seekg(BITMAPOFFSET::IMGOFFSET,ios::beg);	//Set to the position of the bitmap pixel array locator.

	if(!imageStream.read(reinterpret_cast<char*>(&pixelArrayLoc),4))
		status = false;		//get the location of the data array

	imageStream.seekg(pixelArrayLoc,ios::beg);

	imageStream.read(imageDataArray.get(),imageWidth*imageHeight*3);

#ifdef DBG
	switch(imageStream.rdstate())
	{
	case std::ios::failbit :
		status = false;
		PRINT_DBG(DBG,"imageStream failed\n")
		break;
	case std::ios::badbit :
		status = false;
		PRINT_DBG(DBG,"ImageStream was corrupted : stream in undefined state\n")
		break;
	case std::ios::eofbit :
		status = false;
		PRINT_DBG(DBG,"End-of-file was encountered\n")
		break;
	case std::ios::goodbit :
		status = true;
		PRINT_DBG(DBG,"Stream ok.\n")
		break;
	default :
		PRINT_DBG(DBG,"Unknown error!\n")
	}
#endif
#ifndef DBG
	if((imageStream.rdstate() != std::ios::goodbit)
		||	(imageStream.gcount() != imageWidth * imageHeight * 3)//or case is useless
		status = false;
#ifdef DBG
		//status = false;
	std::cerr << "data = " << imageStream.gcount()<<" "<<"\n";
	//status = true;
//std::cout<<"data = "<<*(imageDataArray)<<"\n";
#endif
	return status;
}


///<summary>
///Read a pixel data from the image buffer
///</summary>

krgb ImageReader::readPixel(Pixels pxl)
{
	//UC8 * PixelData = reinterpret_cast<UC8*>(imageDataArray);

	I32 loc = pxl.y * imageWidth * ImgFmt::B24 + pxl.x * ImgFmt::B24;//ImgFmt::B24 = 3 value

	//PixelData += loc;

	//return {*(PixelData + 2),*(PixelData + 1),*(PixelData + 0)};
	return {imageDataArray[loc+2],imageDataArray[loc+1],imageDataArray[]};

}


///<summary>
///This is the interface that can be used to read the image from the imageArray
///2 params :
///1). ImgFmt: currently only 24bpp is supported.
///2). The vector buffer to hold the color unit
///
///Desc. Future will make a generic container.
///</summary>

bool ImageReader::readImage(std::vector<colorUnit>& imageBuf, ImgFmt format)	//make sure that only a existing vector is passed
{
	using namespace std;
	static int i = 0;   //only for debug purpose
	bool status = false;	//status of read operation

	try{
	for(I32 row = 0;row < imageHeight; row++)
		for(I32 column = 0;column < imageWidth-1; column += 3)
		{
			imageBuf.emplace_back(
									{	//Create a temporary "ColorUnit" struct.
										{column, row}	// Temporary "Pixels" struct.
										,readPixel({column, row})	//Temporary "krgb" struct.
									}
								);
		}
	status = true;std::cout << i;
	}
	catch(const std::exception& ex)
	{
		status = false;
	}
	return status;
}




///<summary>
///Gets the image name of the current image
///</summary>
std::string ImageReader::getImageName(bool includePath) const
{
	if(includePath)
	return ImageReader::imageLoc + '/' + ImageReader::imageName;


	return ImageReader::imageName;
}


///<summary>
///Gets the location of the current image
///</summary>
std::string ImageReader::getImageLoc() const
{
	return ImageReader::imageLoc;
}


///<summary>
///read a part of the image from the location
///</summary>
bool ImageReader::readPartly(std::vector<colorUnit>& imageData,I32 xStart,I32 yStart,I32 xEnd,I32 yEnd,ImgFmt format)
{
	for (I32 row = yStart; row <=  yEnd; row ++)
	{
		for (I32 column = xStart;column <= xEnd;column += 3)
		{
			imageData.push_back(
									{	//Create a temporary "ColorUnit" struct.
										{row,column}	// Temporary Pixels struct.
										,readPixel({row,column})	// Temporary "krgb" struct.
									}
								);
		}
	}
	return true;
}


void ImageReader::getProportion(I32& Width, I32& Height)
{
	Width = imageWidth;
	Height = imageHeight;
}















