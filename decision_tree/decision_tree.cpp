#include <iostream>
#include <vector>
#include "vectorUtilities.cpp"
#include <limits.h> // For INT_MAX
#include "fileHandler.cpp"
#include <map>
using namespace std;

int main()
{
    FileHandler fileHandler;
    StringUtilities stringUtilities;
    std::string fileName = "dataset/weather.csv";
    map<std::string, std::vector<std::string>> csvData = fileHandler.handleCSV(fileHandler, stringUtilities, fileName);
    for (std::map<std::string, std::vector<std::string>>::iterator it = csvData.begin(); it != csvData.end(); ++it)
    {
        std::cout << "Key: " << it->first << "\nValues:";
        for (const auto &value : it->second)
        {
            std::cout << " " << value;
        }
        if (it->second.empty())
        {
            std::cout << " (empty)";
        }
        std::cout << "\n";
    }
}