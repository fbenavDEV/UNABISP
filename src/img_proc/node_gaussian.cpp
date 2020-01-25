#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include "node_gaussian.h"
#include "pack_img.h"

namespace img_proc
{
	protocol::Pack* NodeGaussian::Process(protocol::Pack* input) const
	{
		PackImg* np = new PackImg();				
		PackImg* ip = static_cast<PackImg*>(input);
		cv::Mat gaussian;
		cv::GaussianBlur(ip->Image_Matrix(), gaussian, cv::Size(15, 15), 0);
		np->Set_Image(gaussian);
		return(np);
	}
}
