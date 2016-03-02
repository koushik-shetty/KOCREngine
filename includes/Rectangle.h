#ifdef _RECTANGLE_H_
#define _RECTANGLE_H_
#include "Pixel.h"

namespace KOCREngine
{
    class Rectangle{
        PixelPoint top_left, bottom_right;
        Rectangle(PixelPoint topLeft, PixelPoint bottomRight) : top_left(topLeft), bottom_right(bottomRight) 
        {}
        
        Rectangle(PixelLoc_t top, PixelLoc_t left, PixelLoc_t bottom, PixelLoc_t right) 
        : top_left(PixelPoint{top,left}), bottom_right(PixelPoint{bottom,right}) 
        {}
           
        PixelLoc_t GetTop(){return top_left.x;}
        PixelLoc_t GetLeft(){return top_left.y;}
        PixelLoc_t GetBottom(){return bottom_right.x;}
        PixelLoc_t GetRight(){return bottom_right.y;}
        
        PixelLoc_t SetTop(PixelLoc_t x){ top_left.x = x;}
        PixelLoc_t SetLeft(PixelLoc_t y){ top_left.y = y;}
        PixelLoc_t SetBottom(PixelLoc_t x){ bottom_right.x = x;}
        PixelLoc_t SetRight(PixelLoc_t y){ bottom_right.y = y;}        
    };   
}
 
#endif // !_RECTANGLE_H_