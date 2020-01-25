#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "node_copyfile.h"

namespace img_proc
{
	NodeCopyFile::NodeCopyFile()
	{
		this->_dictionary = 0;		
		this->_sizeImgsToProcess = 64;
		this->Set_Maibox_Empty_Event(this);
	}

	void NodeCopyFile::operator()()
	{
		this->Save_Queue();
	}

	void NodeCopyFile::Save_Queue()
	{
		while (!this->_imagesToSave.empty())
		{
			ImageToSave ims = this->_imagesToSave.front();
			this->_imagesToSave.pop();
			string fname = this->_path + ims._filename;
			cv::imwrite(fname, ims._image);
		}
	}

	void NodeCopyFile::Set_Dictionary(const protocol::Dictionary& dictionary)
	{
		this->_dictionary = &dictionary;
	}

	protocol::Pack* NodeCopyFile::Process(protocol::Pack* input) 
	{
		PackImg* ii = static_cast<PackImg*>(input);
		cv::Mat img = ii->Image_Matrix();
		if (this->_dictionary)
		{
			string fname = this->_dictionary->Pick_Word(ii->Pack_Id());			
			ImageToSave ims;
			ims._image = img;
			ims._filename = fname;
			this->_imagesToSave.push(ims);
		}
		else
		{
			std::stringstream sf;
			sf << ii->Pack_Id();
			string fname = sf.str();
			ImageToSave ims;
			ims._image = img;
			ims._filename = fname;
			this->_imagesToSave.push(ims);
		}
		if (this->_imagesToSave.size() > this->_sizeImgsToProcess)
		{
			this->Save_Queue();
		}
		protocol::Pack* op = ii->Clone();
		return(op);
	}
}