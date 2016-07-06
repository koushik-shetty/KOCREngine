#ifndef EDGE_DETECTOR_H
#define EDGE_DETECTOR_H
#include <utility>
#include <vector>
#include <algorithm>
#include <../includes/Pixel.h>

typedef std:pair<PixelIterator,PixelIterator> PixelIteratorPair;

template<int MINDIFF, typename PixelIterator>
class EdgeDetector{
	PixelIterator start, end;
	std::vector<PixelIteratorPair> v;
	EdgeDetector(PixelIterator start , PixelIterator end) : start(start), end(end)
	{}

	PixelIteratorPair FirstEdge() {
		std::adjacent_find(start, end,[](char){
			
		});
	}

	std::vector<PixelIterator> AllEdges(){
		
	}

};


#endif // EDGE_DETECTOR_H
