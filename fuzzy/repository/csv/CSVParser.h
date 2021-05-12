#ifndef CSV_PARSER_H
#define CSV_PARSER_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>

namespace repository {
	
	class CSVParser
	{
	public:
		using word = std::string;
		using line = std::vector<word>;
		const int DELIMITER_LENGTH = 1;

		CSVParser(const std::string _filePath, const char _delimiter);
		virtual ~CSVParser() = default;
		virtual std::vector<line> getLines();

	private:
		std::string filePath;
		char delimiter;
		std::fstream stream;
	};
}

#endif // !CSV_PARSER_H
