#include"../includes/ImageAcquition.h"

using namespace KOCREngine;
//Constructor of the class ImageAcquition class, current directory
ImageAcquition::ImageAcquition(ImageReader& imagerdr)
 : imageName(imagerdr.getImageName(false)), imageLocation(imagerdr.getImageLoc())
{
	//nothing to be done here
}

ImageAcquition::ImageAcquition(ImageReader&& imagerdr)
: imageName(std::move(imagerdr.getImageName(false))), imageLocation(std::move(imagerdr.getImageLoc()))

{
	//nothing to be done here
}


bool KOCREngine::ImageAcquition::fillArray()
{
	bool status = false;

	//TODO

	return status;
}






