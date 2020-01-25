#include "siso.h"
#include "node.h"
#include "pack.h"


namespace protocol
{
	Siso::Siso() : Node()
	{}

	void Siso::Pack_Push(Pack* pack)
	{
		this->_mailbox.Pack_Push(pack);
	}

	void Siso::Process()
	{
		Pack* pack = this->_mailbox.Pack_Pop();
		Pack* new_pack = this->Process(pack);
		new_pack->_packId = pack->Pack_Id();
		this->Broadcast(new_pack);
		delete pack;
	}
}

