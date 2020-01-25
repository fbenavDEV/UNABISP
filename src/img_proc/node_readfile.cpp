#include <string>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "node_readfile.h"
#include "pack_img.h"

namespace img_proc
{
	using std::string;

	NodeReadFile::NodeReadFile()
	{
		this->_id = 0;
		this->_sizeImgsToProcess = 64;
	}

	void NodeReadFile::AddFileName(const string& filename)
	{
		this->_imageNames.push(filename);
	}

	void NodeReadFile::Set_Directory(const string& directory)
	{
		this->_directory = directory;
	}

	string NodeReadFile::Directory() const
	{
		return(this->_directory);
	}

	void NodeReadFile::Fill_Images()
	{
		uint k = 0;
		while ((k < this->_sizeImgsToProcess) && (!this->_imageNames.empty()))
		{
			ImageLoaded img_loaded;
			string filename = this->_imageNames.front();
			img_loaded._name = filename;
			filename = this->_directory + filename;
			this->_imageNames.pop();
			img_loaded._image = cv::imread(filename);
			this->_imagesToProcess.push(img_loaded);
			++k;
		}
	}

	void NodeReadFile::Process()
	{
		if (this->_imagesToProcess.empty())
		{
			this->Fill_Images();
		}
		if (!this->_imagesToProcess.empty())
		{
			ImageLoaded img = this->_imagesToProcess.front();
			PackImg* pckimg = new PackImg();
			pckimg->Set_Image(img._image);			
			this->Add_To_Dictionary(img._name,pckimg);
			this->Broadcast(pckimg);
		}
	}
}