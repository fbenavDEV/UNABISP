#include <thread>
#include "node.h"

namespace protocol
{
	Node::Node()
	{
		this->_processing = false;
		this->_stopped = false;
		this->_inputEvent = nullptr;
		this->_emptyEvent = nullptr;
	}

	void Node::Start(uint no_of_threads)
	{
		if ((!this->_processing)&&(!this->Mailbox_Empty()))
		{
			this->_processing = true;
			this->_stopped = false;
			for (uint k = 0; k < no_of_threads; ++k)
			{
				std::thread t(&Node::Back_Process, this);
				t.detach();
			}
		}
	}

	void Node::Back_Process()
	{
		while ((!this->Mailbox_Empty())&&(!this->_stopped))
		{
			this->Process();
		}	
		this->_processing = false;
		if (this->_emptyEvent)
		{
			(*this->_emptyEvent)();
		}
	}

	void Node::Stop()
	{
		this->_stopped = true;
	}


	void Node::Broadcast(Pack* pack)
	{
		int n = (int)this->_outputNodes.size();
		if (n > 0)
		{
			vector<Pack*> outputs(n);
			pack->_generatingNode = this;
			outputs[0] = pack;
			for (int k = 1; k < n; ++k)
			{
				Pack* n_pack = pack->Clone();
				outputs[k] = n_pack;
			}
			for (int k = 0; k < n; ++k)
			{
				this->_outputNodes[k]->Pack_Push(outputs[k]);
				this->_outputNodes[k]->Start();
			}
		}
		else
		{
			delete pack;
		}
	}
		
	void Node::Connect_To_Output(Node* node)
	{
		this->_outputNodes.push_back(node);
		if (node->_inputEvent)
		{
			(*node->_inputEvent)(this);
		}
	}

	void Node::Set_Input_Event(OnInputEvent* event)
	{
		this->_inputEvent = event;
	}

	void Node::Set_Maibox_Empty_Event(OnMailboxEmptyEvent* event)
	{
		this->_emptyEvent = event;
	}
}