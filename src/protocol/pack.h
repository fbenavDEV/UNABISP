#ifndef PACK_H
#define PACK_H

#include "defs.h"

namespace protocol
{
	class Node;
	class NodeGenerator;
	class Siso;

	class Pack
	{
	private:
		friend class Siso;
		friend class NodeGenerator;
		friend class Node;
		uint _packId;
		Node* _generatingNode;
	protected:
		virtual Pack* Create_Clone() const = 0;
	public:
		Pack();
		Pack(const Pack& pack);
		Pack* Clone() const;
		uint Pack_Id() const;
		Node* Emitting_Node() const;
		virtual ~Pack();
	};

	inline uint Pack::Pack_Id() const
	{
		return(this->_packId);
	}
}


#endif
