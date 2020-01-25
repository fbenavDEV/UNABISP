#include <opencv2/imgcodecs/imgcodecs.hpp>
#include "node_copyfile.h"

namespace img_proc
{
	NodeCopyFile::NodeCopyFile()
	{

	}

	protocol::Pack* NodeCopyFile::Process(protocol::Pack* input) const
	{
		PackImg* ii = static_cast<PackImg*>(input);
		return(ii);
	}
}