#include "node_generator.h"

namespace protocol
{
	NodeGenerator::NodeGenerator()
	{
		this->_current_pckid = 0;
	}
		
	void NodeGenerator::Add_To_Dictionary(const string& word, protocol::Pack* pack)
	{
		uint id = this->Generate_Package_Id();
		this->_dictionary.Add_Word(id, word);
		pack->_packId = id;
	}

	uint NodeGenerator::Generate_Package_Id()
	{
		int s = this->_current_pckid;
		++this->_current_pckid;
		return(s);
	}

	bool NodeGenerator::Mailbox_Empty() const
	{
		return(false);
	}

	void NodeGenerator::Pack_Push(Pack* pack)
	{
		delete pack; 
	}

	Dictionary& NodeGenerator::Generator_Dictionary()
	{
		return(this->_dictionary);
	}

	const Dictionary& NodeGenerator::Dictionary() const
	{
		return(this->_dictionary);
	}
}
