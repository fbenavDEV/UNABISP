#ifndef PACK_IMG
#define PACK_IMG

#include "protocol/pack.h"
#include "opencv2/core.hpp"

namespace img_proc
{
	using cv::Mat;

	class PackImg : public protocol::Pack
	{
	private:
		Mat _imgMatrix;
	public:
		PackImg();
		void Set_Image(const cv::Mat& mat);
		cv::Mat Image_Matrix() const;
		Pack* Create_Clone() const;
	};

	inline cv::Mat PackImg::Image_Matrix() const
	{
		return(this->_imgMatrix);
	}
}

#endif
