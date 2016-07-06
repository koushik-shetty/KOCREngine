#include "Image.h"
#include "error_cluster.hpp"
#include "BitmapInfo.h"
#include <utility>



namespace KOCREngine
{
	//CLS = constinuous line segment
	typedef std::pair<Image::iterator, Image::iterator> CLS;//continuous line segment(continuous wrt pixels).


	//scan_block function scans a block of pixels i.e it scans height * imageWidth;
	error<bool> scan_block( Image::iterator img_begin, Image::iterator img_end,
							prop_t proportion
							);

	//scans a single line in the image.
	error<std::vector<std::pair<Image::iterator, Image::iterator >>>
		scan_line( Image::iterator begin, Image::iterator end );

	//gets whether the line is in the shadow of the umbrella_line.
	bool is_connected_CLS( X_terminals umbrella_line, X_terminals shadow_line, percentage<30> percent );

}