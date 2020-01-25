#include "mailbox.h"

namespace protocol
{
	Mailbox::Mailbox()
	{

	};

	void Mailbox::Pack_Push(Pack* pack)
	{
		this->_mailbox_locker.lock();
		int id = pack->Pack_Id();
		map<uint, Pack*>::iterator itr = this->_received.find(id);
		if (this->_received.find(id) == this->_received.end())
		{
			this->_received.insert(std::pair<int, Pack*>(id, pack));
		}
		else
		{
			delete itr->second;
			itr->second = pack;			
		}
		this->_mailbox_locker.unlock();
	}


	Pack* Mailbox::Pack_Pop()
	{
		this->_mailbox_locker.lock();
		Pack* r = 0;
		map<uint, Pack*>::iterator itr = this->_received.begin( );
		if (itr != this->_received.end())
		{
			r = itr->second;
			this->_received.erase(itr->first);
		}
		this->_mailbox_locker.unlock();
		return(r);
	}

	Pack* Mailbox::Pack_Pop(uint id)
	{
		this->_mailbox_locker.lock();
		Pack* r = 0;
		map<uint, Pack*>::iterator itr = this->_received.find(id);
		if (itr != this->_received.end())
		{
			r = itr->second;
		}
		this->_mailbox_locker.unlock();
		return(r);

	}

	bool Mailbox::Pack_Exists(uint id) const
	{
		bool r = false;
		map<uint, Pack*>::const_iterator itr = this->_received.find(id);
		if (itr != this->_received.end())
		{
			r = true;
		}
		return(r);
	}


	Mailbox::~Mailbox()
	{
		map<uint, Pack*>::iterator itr;
		for (itr = this->_received.begin(); itr != this->_received.end(); ++itr)
		{
			Pack* pack = itr->second;
			delete pack;
		}
		this->_received.clear();
	};
}