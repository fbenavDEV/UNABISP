#include "dictionary.h"

namespace protocol
{

	Dictionary::Dictionary()
	{

	}

	Dictionary::~Dictionary()
	{

	}

	void Dictionary::Add_Word(uint id, const string& index)
	{
		this->_index[id] = index;
	}

	string Dictionary::Pick_Word(uint id) const
	{
		string r = "";
		map<uint, string>::const_iterator itr = this->_index.find(id);
		if (itr != this->_index.end())
		{
			r = itr->second;
		}
		return(r);
	}

	string Dictionary::Remove_Word(uint id)
	{
		string r = "";
		map<uint, string>::const_iterator itr = this->_index.find(id);
		if (itr != this->_index.end())
		{
			this->_locker.lock();
			this->_index.erase(itr);
			this->_locker.unlock();
		}
		return(r);

	}


}