#ifndef NODE_READ_FILE_H
#define NODE_READ_FILE_H

#include <queue>
#include <string>
#include "opencv2/core.hpp"
#include "pack_img.h"
#include "protocol/pack.h"
#include "protocol/node_generator.h"

namespace img_proc
{
	using std::queue;
	using std::string;

	struct ImageLoaded
	{
		cv::Mat _image;
		string _name;
	};

	class NodeReadFile : public protocol::NodeGenerator
	{
	private:
		uint _sizeImgsToProcess;
		uint _id;
		queue<img_proc::ImageLoaded> _imagesToProcess;
		string _directory;
		queue<string> _imageNames;
	protected:
		void Fill_Images();
		void Process();
	public:
		NodeReadFile();
		void AddFileName(const string& filename);
		void Set_Directory(const string& directory);
		string Directory() const;
	};
}

#endif
