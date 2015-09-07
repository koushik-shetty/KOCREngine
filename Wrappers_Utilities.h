#ifndef WRAP_UTIL
#define WRAP_UTIL


#define PRINT_DBG(A,STR) #ifdef (A) std::cerr << #STR; #endif

typedef uint8_t UC8;
typedef char C8;
typedef uint32_t UI32;
typedef int32_t PixelLoc_t;
typedef int32_t I32;

enum BITMAPOFFSET{  IMGWDT = 0x12				//Image width Location.
							, IMGHGT = 0x16				//Image Height Location.
							, IMGDATASIZE = 0x22		//Image Pixel array size.
							, IMGBPP = 0x1C
							, IMGOFFSET = 0x0A			//Image Pixel array offset.
};


enum BITMAPFIELDSSIZE{	 IMGWDTSZ = 0x04
						,IMGHGTSZ = 0x04
						,IMGDATASIZESZ = 0x04
};

enum MASK{	 BLUEMASK = 0x0FF
					,GREENMASK = 0x0FF00
					,REDMASK = 0x0FF0000
};

enum class ImgFmt{
					B8 = 1,
					B16,
					B24,
					B32,
					};

class CharArrtoInt
{
	CharArrtoInt(const char* arr);
	CharArrtoInt(std::string& str);
	CharArrtoInt(std::string&& str);
};

template<typename T>
T arrElem(T*arr,int row,int col,int maxcol)
{
	return *(arr + (row)*(maxcol-1) +(col));
}

#endif // WRAP_UTIL

