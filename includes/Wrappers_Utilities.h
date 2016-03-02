#ifndef WRAP_UTIL
#define WRAP_UTIL
#include <string>

#define PRINT_DBG(STR,STREAM) do{ \
	if(DEBUG) \
	{ \
		(STREAM) << "File : "<< __FILE__  << ", Line : " <<__LINE__ << ", msg : "<< #STR <<"\n";  \
	}

enum BITMAPOFFSET{  IMGWDT = 0x12			//Image width Location.
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



#endif // WRAP_UTIL

