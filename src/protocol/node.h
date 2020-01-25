#ifndef NODE_H
#define NODE_H

#include <vector>
#include "pack.h"

namespace protocol
{
	using std::vector;

	/**
	* This is a generic processing unit. After processing its input package, a node is able to send packages to connected nodes
	* A node may have two states: processing or stopped. When the node is stopped, it does not execute any work and its working thread
	* does not exist. Once the node chnages its state, it creates a working thread in which all processing is executed. 
	* When a Package enters the node, it is placed in a local Mailbox so it can be processed afterwards. A node can contain many
	* Mailboxes. 
	*/

	class Node
	{
	private:

		typedef void (Node::*OnInputEvent)(const Node* input_node);

		/**
		* All output nodes to which the present node is connected
		*/
		vector<Node*> _outputNodes;

		/**
		* This is TRUE when the node is processing and its corresponding processing thread has been
		* created
		*/
		mutable bool _processing;

		/**
		It is TRUE when the node stopped and is not processing packages
		*/
		mutable bool _stopped;

		OnInputEvent _inputEvent;
	protected:
		/**
		* All processing is executed in this method, which calls the method Process() in a separate thread.
		* The invoked separated thread is destroyed once there are no more packages to process
		*/
		void Back_Process();

		/**
		* The overladed method that processes the package. 
		*/
		virtual void Process() = 0;

		/**
		* @return TRUE if the Mailbox is empty. 
		*/
		virtual bool Mailbox_Empty() const = 0;
	public:
		Node();
		/**
		* A Pack is pushed inside the local Mailbox. 
		* @param pack The package to be pushed inside the Mailbox
		*/
		virtual void Pack_Push(Pack* pack) = 0;

		/**
		* A package is cloned and broadcasted to all nodes connected to the present node. 
		* @param pack Package to be broadcasted
		*/
		void Broadcast(Pack* pack);

		/**
		* Connects current node to the node given in the parameter
		* @param node Node to which current node is connected
		*/
		void Connect_To_Output(Node* node);

		/**
		* This method allows access to one of the output nodes to which current node is connected.
		* @param id Node output pin to which current node is connected as an input
		* @return A pointer to the output node
		*/
		Node* Output_Node(int id);

		/**
		* Starts processing input packages with the number of threads specified
		* @param no_of_threads Number of executing threads
		*/
		void Start(uint no_of_threads = 1);

		/**
		* Stops processing
		*/
		void Stop();

		/**
		* @return TRUE if the node is stopped
		*/
		bool Stopped() const;

		/**
		* Sets the event that is triggered when a node is connected. 
		* @param event A pointer to the function that is called when an input node is connected
		*/
		void Set_Input_Event(OnInputEvent event);
	};

	inline bool Node::Stopped() const
	{
		return(this->_stopped);
	}

	inline Node* Node::Output_Node(int id)
	{
		return(this->_outputNodes[id]);
	}
}

#endif
