#ifndef NODE_COPY_FILE_H
#define NODE_COPY_FILE_H

#include <string>
#include <queue>
#include "pack_img.h"
#include "protocol/pack.h"
#include "protocol/siso.h"
#include "protocol/dictionary.h"

namespace img_proc
{
	using std::queue;
	using std::string;

	struct ImageToSave
	{
		cv::Mat _image;
		string _filename;
	};

	class NodeCopyFile : public protocol::Siso
	{
	private:
		const protocol::Dictionary* _dictionary;
		uint _sizeImgsToProcess;
		uint _id;
		queue<ImageToSave> _imagesToSave;
		string _path;
	protected:
		protocol::Pack* Process(protocol::Pack* input) const;
	public:
		NodeCopyFile();
	};
}

#endif
