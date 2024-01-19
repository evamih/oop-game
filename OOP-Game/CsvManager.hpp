#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class CsvManager
{
public:
	static std::vector<std::string> readData(const char* path)
	{
        std::vector<std::string> rows;

        std::ifstream fin(path, std::ios::in);

        std::string line;

        while (std::getline(fin, line)) {
            rows.push_back(line);
        }

        return rows;
	}
};