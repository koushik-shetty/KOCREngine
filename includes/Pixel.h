#ifndef PIXEL_H
#define PIXEL_H
#include <cstdint>
namespace KOCREngine{
	
	typedef uint8_t UC8;
	typedef char C8;
	typedef uint32_t UI32;
	typedef int32_t PixelLoc_t;
	typedef int32_t I32;

	struct PixelPoint{
		PixelLoc_t x;
		PixelLoc_t y;
	};

	struct krgb{
		UC8 red;
		UC8 green;
		UC8 blue;
	}; //image component holder;

	struct colorUnit{
		PixelPoint pixel;
		krgb rgb;
	};

	template<typename T>
	T arrElem(T* arr,int row,int col,int maxcol)
	{
		return *(arr + (row)*(maxcol-1) +(col));
	}
}

#endif // PIXEL_H
