#ifndef __ENCAPSULATOR_H__
#define __ENCAPSULATOR_H__
#include "../include/Image.h"
#include <memory>

namespace KOCREngine {
	
	class Encapsulator {
		std::unique_ptr<Image> Image;
	public:
		Encapsulator(const Image& ir);
		Encapsulator(Image&& ir);
	};

}
#endif //__ENCAPSULATOR_H__