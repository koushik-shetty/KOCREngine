#ifndef __ENCAPSULATOR_H__
#define __ENCAPSULATOR_H__
#include "../include/ImageReader.h"
#include <memory>

namespace KOCREngine {
	
	class Encapsulator {
		std::unique_ptr<ImageReader> ImageReader;
	public:
		Encapsulator(const ImageReader& ir);
		Encapsulator(ImageReader&& ir);
	};

}
#endif //__ENCAPSULATOR_H__