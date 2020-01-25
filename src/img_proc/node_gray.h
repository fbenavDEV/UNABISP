#ifndef NODE_GRAY_H
#define NODE_GRAY_H

#include "protocol/siso.h"

namespace img_proc
{
	class NodeGray : public protocol::Siso
	{
	protected:
		protocol::Pack* Process(protocol::Pack* input) const;
	};
}

#endif
