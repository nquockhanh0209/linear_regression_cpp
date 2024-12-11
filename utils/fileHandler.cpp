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

    void handleReadCsv(std::string fileName)
    {
        // Specify the CSV file path
        std::string filename = fileName;

        // Open the file
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error: Could not open file " << filename << std::endl;
        }

        // Read the file line by line
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<std::string> row; // To store individual fields in a row

            // Parse the line using a stringstream
            std::stringstream ss(line);
            std::string field;
            while (std::getline(ss, field, ','))
            {                         // Assuming CSV uses ',' as a delimiter
                row.push_back(field); // Add each field to the row vector
            }

            // Process the row
            for (const auto &item : row)
            {
                std::cout << item << " ";
            }
            std::cout << std::endl; // Newline after each row
        }

        // Close the file
        file.close();

    }
};