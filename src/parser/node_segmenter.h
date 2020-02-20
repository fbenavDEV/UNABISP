#ifndef NODE_SEGMENTER_H
#define NODE_SEGMENTER_H

#include <istream>
#include <vector>
#include <string>
#include <sstream>
#include "defs.h"

using std::string;

namespace parser
{
	class Node_Segmenter
	{
	private:
		std::istream* _stream;
		std::vector<string> _nodeSegments;
		std::string _cumString;
		std::stringstream _logStream;
		uint _openBrackets;
		uint _closeBrackets;
		uint _squareBrackets;
		uint _lineNumber;
		bool _inNode;
	protected:
		void Process_Line(const string& line);
		void Accum_Line(const string& line);
		bool Check_Square_Brackets(const string& line);
	public:
		Node_Segmenter(std::istream& stream);
		void Segment();
		~Node_Segmenter();
	};
}


#endif
