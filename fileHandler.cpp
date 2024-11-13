#include <bits/stdc++.h>
#include <fstream>
#include <vector>
#include "stringUtilities.cpp"
class FileHandler {
    private:
        StringUtilities stringUtilities;
        std::vector<std::string> handleReadFile(std::string fileName){
            std::ifstream f(fileName);

            // Check if the file is successfully opened
            if (!f.is_open()) {
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
        std::vector<std::vector<T>> convertDataToNumber(std::string fileName) {
            std::vector<std::string> data = handleReadFile(fileName);
            if(data.size() != 0) {
                std::vector<std::vector<T>> result;
                for(int i =0; i<data.size(); i++){
                    std::vector<std::string> dataIndex = stringUtilities.tokenize(data.at(i), " ");
                    std::vector<T> resultLine;

                    for(int i = 0; i<dataIndex.size(); i++){
                        resultLine.push_back(std::stoi(dataIndex.at(i)));
                    }
                    result.push_back(resultLine);
                }
                return result;
                
            }
            assert("Data empty!");
        }

};