#ifndef PIXEL_H
#define PIXEL_H

#include <cstdint>
#include <memory>
#include <iterator>
#include <cmath>

#include "BitmapInfo.h"
#define DIFF 30

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
	}; //image pixel component holder;
	
	
	inline bool operator==(const krgb& lhs, const krgb& rhs) {
		auto diff = [](uint8_t a, uint8_t b) -> uint8_t {
			return uint8_t(std::abs(a - b))
		}
		return diff(lhs.red, rhs.red) >  DIFF
			|| diff(lhs.green, rhs.green) > DIFF
			|| diff(lhs.blue, rhs.blue) > DIFF
	} 
	
	inline bool operator!=(const krgb& lhs, const krgb& rhs) {
		return !(lhs == rhs);	
	}
	
	typedef std::unique_ptr<krgb[]> image_array;	
	
	struct colorUnit{
		PixelPoint pixel;
		krgb rgb;
	};

	inline uint32_t pointToIndex(PixelPoint pp, uint32_t width){
		return pp.x + pp.y * width;
	}
	
	inline uint64_t imageLength(prop_t prop) {
		return prop.width * prop.height;	
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
	///assumes that the underlying 
	///</summary>
	struct PixelIterator : public std::random_access_iterator_tag{
		krgb* pixel;
		int idx;
		uint64_t image_size; 
		ImageInfo image_info;

		PixelIterator(krgb* pixel, ImageInfo imageInfo)
		: pixel(pixel)
		, idx(0)
		, image_info(imageInfo) {
			image_size = imageLength(imageInfo.size);
		}

		PixelIterator& operator ++() {
			idx++;
			return *this;
		}
		
		PixelIterator& operator--() {
			idx--;
			return *this;
		}
		
		PixelIterator& operator +=(int n) {
			idx += n;
			return *this; 
		}
		
		PixelIterator& operator -=(int n) {
			return operator+=(-1 * n);
		}	
		
		krgb& operator *() {
			return *(pixel + idx);				
		}
	};
}

#endif // PIXEL_H
