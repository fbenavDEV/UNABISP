#include "pack_img.h"

namespace img_proc
{
	using protocol::Pack;

	PackImg::PackImg()
	{
		this->_imgMatrix = 0;
	}

	void PackImg::Set_Image(const Mat& img)
	{
		this->_imgMatrix = img.clone();
	}

	Pack* PackImg::Create_Clone() const
	{
		PackImg* np = new PackImg();
		np->_imgMatrix = this->_imgMatrix.clone();
		return(np);
	}
}