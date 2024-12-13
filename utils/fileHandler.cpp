#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include "stringUtilities.cpp"
using namespace std;
class FileHandler
{
private:
    StringUtilities stringUtilities;
    std::vector<std::string> handleReadFile(std::string fileName)
    {
        std::ifstream f(fileName);

        // Check if the file is successfully opened
        if (!f.is_open())
        {
            assert("Error opening the file!");
        }

        // String variable to store the read data
        std::string s;
        std::vector<std::string> lines;
        // Read each line of the file and print it to the
        // standard output stream till the whole file is
        // completely read

        while (getline(f, s))
            lines.push_back(s);

        // Close the file
        f.close();
        return lines;
    }

public:
    template <typename T>
    std::vector<std::vector<T>> convertDataToNumber(std::string fileName)
    {
        std::vector<std::string> data = handleReadFile(fileName);
        if (data.size() != 0)
        {
            std::vector<std::vector<T>> result;
            for (int i = 0; i < data.size(); i++)
            {
                std::vector<std::string> dataIndex = stringUtilities.tokenize(data.at(i), " ");
                std::vector<T> resultLine;

                for (int i = 0; i < dataIndex.size(); i++)
                {
                    resultLine.push_back(std::stod(dataIndex.at(i)));
                }
                result.push_back(resultLine);
            }
            return result;
        }
        assert("Data empty!");
    }

    map<std::string, std::vector<std::string>> handleCSV(FileHandler fileHandler, StringUtilities stringUtilities, std::string fileName)
    {
        map<std::string, std::vector<std::string>> csvData;

        std::vector<std::string> data = handleReadFile(fileName);
        std::string keysString = data[0];
        std::vector<std::string> keys = stringUtilities.tokenize(keysString, ",");
        for (int i = 1; i < data.size(); i++)
        {
            std::vector<std::string> line = stringUtilities.tokenize(data[i], ",");
            for (int j = 0; j < keys.size(); j++)
            {
                if (csvData[keys[j]].empty())
                {
                    csvData[keys[j]] = std::vector<std::string>();
                }
                csvData[keys[j]].push_back(line[j]);
            }
        }
        return csvData;
    }
};