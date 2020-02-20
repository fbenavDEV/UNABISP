#include <regex>
#include "node_segmenter.h"
#include "defs.h"


namespace parser
{
	Node_Segmenter::Node_Segmenter(std::istream& stream)
	{
		this->_stream = &stream;
		this->_openBrackets = 0;
		this->_cumString = "";
		this->_inNode = false;
		this->_lineNumber = 0;
		this->_squareBrackets = 0;
	}

	bool Node_Segmenter::Check_Square_Brackets(const string& line)
	{
		string cline = line;
		uint npos = 0;
		bool r = false;
		while ((cline.length() > 0) && (npos != (uint)string::npos))
		{
			npos = (uint)cline.find("[");
			if (npos != (uint)string::npos)
			{
				cline = cline.substr((size_t)(npos+1), cline.length());
				++this->_squareBrackets;
			}
			npos = (uint)cline.find("]");
			if (npos != (uint)string::npos)
			{
				cline = cline.substr((size_t)(npos+1),cline.length());
				--this->_squareBrackets;
			}
			if (this->_squareBrackets > 1)
			{
				r = true;
			}
		}
		return(r);
	}

	Node_Segmenter::~Node_Segmenter()
	{

	}

	void Node_Segmenter::Accum_Line(const string& line)
	{
		bool error = this->Check_Square_Brackets(line);
		if (!error)
		{
			string mline = std::regex_replace(line, std::regex("\n"), "");
			mline = std::regex_replace(mline, std::regex(" "), "");
			mline = std::regex_replace(mline, std::regex("("), "");
			mline = std::regex_replace(mline, std::regex(")"), "");
			this->_cumString = this->_cumString + mline;
		}
		else
		{
			this->_logStream << "Error at line " << this->_lineNumber << ". Inconsistent square brackets.";
		}
	}

	void Node_Segmenter::Process_Line(const string& line)
	{
		if (!this->_inNode)
		{
			this->_cumString = "";
			uint np = (uint)line.find("NODE");
			if (np != std::string::npos)
			{
				this->_inNode = true;
			}	
		}
		else
		{
			uint np = (uint)line.find("NODE");
			if (np != (uint)std::string::npos)
			{
				this->_logStream << "Error line: " << this->_lineNumber << "\n";
				this->_logStream
					<< "Node brackets have not been properly closed";
			}
		}
		if (line.find("{") != std::string::npos)
		{
			this->_openBrackets++;
		}
		if (line.find("}") != std::string::npos)
		{
			this->_closeBrackets++;
			if (this->_closeBrackets > this->_openBrackets)
			{
				this->_logStream << "Error line: " << this->_lineNumber << "\n";
				this->_logStream 
					<< "Opening and closing brackets do not match. A closing bracket \"}\" does not match any opening bracket \n";
			}
			if ((this->_openBrackets > 0) && (this->_openBrackets - this->_closeBrackets == 0))
			{
				this->_inNode = false;
				this->Accum_Line(line);
				this->_nodeSegments.push_back(this->_cumString);
				this->_cumString = "";
			}
		}
		this->Accum_Line(line);
	}

	void Node_Segmenter::Segment()
	{
		std::istream& stream = *this->_stream;
		while (!stream.eof())
		{
			string line;
			std::getline(stream, line);
			size_t com_p = line.find("%");
			if (com_p != string::npos)
			{
				line = line.substr(0, com_p);
			}
			if (line.length() > 0)
			{
				std::transform(line.begin(), line.end(), line.begin(), ::toupper);
				this->Process_Line(line);
			}
			++this->_lineNumber;
		}
	}
}