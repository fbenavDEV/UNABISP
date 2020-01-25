#ifndef NODE_GAUSSIAN_H
#define NODE_GAUSSIAN_H

#include "protocol/siso.h"

namespace img_proc
{
	class NodeGaussian : public protocol::Siso
	{
	protected:
		protocol::Pack* Process(protocol::Pack* input) const;
	};
}

#endif
