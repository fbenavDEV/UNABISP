#include "pack.h"

namespace protocol
{
	Pack::Pack()
	{
		this->_packId = 0;
		this->_generatingNode = nullptr;
	};

	Pack::Pack(const Pack& pack)
	{
		this->_packId = pack._packId;
		this->_generatingNode = pack._generatingNode;
	}

	Pack* Pack::Clone() const
	{
		Pack* cloned = this->Create_Clone();
		cloned->_packId = this->_packId;
		cloned->_generatingNode = this->_generatingNode;
		return(cloned);
	}

	Node* Pack::Emitting_Node() const
	{
		return(this->_generatingNode);
	}

	Pack::~Pack()
	{
		this->_generatingNode = 0;
	}
}