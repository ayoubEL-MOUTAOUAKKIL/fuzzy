#include "CSVParser.h"
#include <fstream>

repository::CSVParser::CSVParser(const std::string _filePath, const char _delimiter = ',') : 
	filePath(_filePath),
	delimiter(_delimiter)
{
}

std::vector<std::vector<std::string>> repository::CSVParser::getLines()
{
    std::vector<std::vector<std::string>> lines;
    std::vector<std::string> line;
    std::string csv_line;
    std::string field = "";
    stream.open(filePath);
    while (std::getline(stream, csv_line)) {
        line.clear();
        std::istringstream iss(csv_line);
        while (!iss.eof()) {
            std::getline(iss, field, delimiter);
            line.push_back(field);
        }
        lines.push_back(line);
    }
    stream.close();
    return lines;
}
