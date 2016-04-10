#ifndef PIXEL_H
#define PIXEL_H

#include <cstdint>
#include <memory>
#include <iterator>

#include "BitmapInfo.h"

namespace KOCREngine{
	
	typedef char C8;
	typedef uint32_t UI32;
	typedef int32_t PixelLoc_t;
	typedef int32_t I32;

	struct PixelPoint{
		PixelLoc_t x;
		PixelLoc_t y;
	};

	struct krgb{
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;
	}; //image component holder;

	typedef std::unique_ptr<krgb[]> image_array;	
	
	struct colorUnit{
		PixelPoint pixel;
		krgb rgb;
	};

	inline uint32_t pointToIndex(PixelPoint pp, uint32_t width){
		return pp.x + pp.y * width;
	}

	inline ImgFmt imageFormat(int16_t bits){
		switch(bits){
			case 0x8:	return ImgFmt::B8;
			case 16:	return ImgFmt::B16;
			case 24:	return ImgFmt::B24;
			case 32:	return ImgFmt::B32;
		}
		return ImgFmt::B32;
	}

	inline int formatByteSize(ImgFmt fmt) {
		int offset = 0;
		switch (fmt) {
			case ImgFmt::B32 : 
				++offset;
			case ImgFmt::B24:
				++offset;
			case ImgFmt::B16:
				++offset;
			case ImgFmt::B8:
				++offset;
		}
		return offset;
	}
	
	///<summary>
	///Iterator to the image data
	///takes the image data
	///</summary>
	struct PixelIterator : public std::bidirectional_iterator_tag{
		// image_array& imageDataArray;
		// int idx, offset;

		// PixelIterator(image_array& imageData, ImgFmt format = ImgFmt::B24) : imageDataArray(imageData), idx(0) {
		// 	offset = formatByteSize(format);
		// }

		// PixelIterator& operator ++() {
		// 	idx += offset;
		// 	return *this;
		// }

		// PixelIterator& operator *() {
		// 	return 
		// }
	};
}

#endif // PIXEL_H
