#ifndef NODE_GENERATOR_H
#define NODE_GENERATOR_H

#include "pack.h"
#include "node.h"
#include "dictionary.h"

namespace protocol
{

	class NodeGenerator : public Node
	{
	private:
		uint _current_pckid;
		Dictionary _dictionary;
	protected:
		bool Mailbox_Empty() const;
		Dictionary& Generator_Dictionary();
		uint Generate_Package_Id();
		void Add_To_Dictionary(const string& word, protocol::Pack* pack);
	public:
		NodeGenerator();
		void Pack_Push(Pack* pack);
		const Dictionary& Dictionary() const;
	};
}
#endif
