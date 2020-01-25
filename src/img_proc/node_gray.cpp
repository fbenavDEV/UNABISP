#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "node_gray.h"
#include "pack_img.h"

namespace img_proc
{
	protocol::Pack* NodeGray::Process(protocol::Pack* input) const
	{
		PackImg* np = new PackImg();				
		PackImg* ip = static_cast<PackImg*>(input);
		cv::Mat gray;
		cv::cvtColor(ip->Image_Matrix(), gray, cv::COLOR_BGR2GRAY);
		np->Set_Image(gray);
		return(np);
	}
}
