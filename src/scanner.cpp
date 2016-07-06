#include<algorithm>
#include<functional>
#include<iostream>
#include<array>
#include<memory>
#include<iterator>
#include "scanner.hpp"
#include "Pixel.h"

namespace KOCREngine{

		
		//internal function to scan the input line for one CLS
	inline static CLS
	CLS_scan_line(Image::iterator begin, Image::iterator end)	{
		//using inverted predicate to find adjacent mismatch
		auto first_color_end = std::adjacent_find( begin, end, std::not_equal_to<krgb>());
		decltype(first_color_end) second_color_end = end; 
		if( first_color_end != end) {
			second_color_end = std::adjacent_find(first_color_end + 1, end);			
		}
		return std::make_pair(first_color_end + 1, second_color_end);
	}


	//scans a line and gets an array of CLS group data.
	inline std::vector<CLS>
	scan_line(Image::iterator begin, Image::iterator end)	{
		std::vector<CLS> cls_groups{};
		CLS cls{begin, begin};//initialize.
		do{
			//each iteration start from the end of the previous mismatch
			cls = CLS_scan_line(cls.second, end);
			//all the group to the vector. 
			cls_groups.push_back( cls );			
		}
		while ( cls.second != end )//if the mismatching pixels are not found then the end iterator is returned.
		return std::move(cls_groups);
	}



	std::vector<std::vector<CLS>>
	scan_block( Image::iterator begin
		, Image::iterator end
		, prop_t img_prop )
	{
		auto from = begin,
			to = end;
			
		std::vector<std::vector<CLS>> CLS_lines;
		for(int i = 0; i <  img_prop.height; i++) {
			from = begin + (i * img_prop.width);
			to = from +  img_prop.width;
			CLS_lines.push_back(scan_line(from, to));
		}
		
		return CLS_lines;
	}




	bool KOCREngine::is_connected_CLS( KOCREngine::X_terminals top_line
		, KOCREngine::X_terminals bottom_line
		, KOCREngine::percentage<30> percent = KOCREngine::percentage<30>() )//percentage indicates the least amount of pixels 
		//of bottom line to be under the shadow of top.
	{
		//if bottomm line's start is between top line segment
		if ( top_line.x_start <= bottom_line.x_start && bottom_line.x_start <= top_line.x_end )
		{
			//the distance from the start of bottom line to end of second must be >= 30% of bottom segment's length.
			return ( top_line.x_end - bottom_line.x_start ) >= ( percent % ( bottom_line.x_end - bottom_line.x_start ) );
		}
		else //if bottom line's end is between top line segment
		if ( top_line.x_start <= bottom_line.x_end && bottom_line.x_end <= top_line.x_end )
		{
			return ( bottom_line.x_end - top_line.x_start ) >= ( percent % ( bottom_line.x_end - bottom_line.x_start ) );
		}
		else
		{
			//if top line falls within the bigger bottom line.
			return top_line.x_start >= bottom_line.x_start && top_line.x_end <= bottom_line.x_end ;
		}

	}
	
}
