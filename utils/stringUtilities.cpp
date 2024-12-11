#include<vector>
#include<string>
#include <iostream>
class StringUtilities{
    public:
        std::vector<std::string> tokenize(std::string s, std::string del)
            {
                std::vector<std::string> cleanString;
                int start, end = -1*del.size();
                do {
                    start = end + del.size();
                    end = s.find(del, start);
                    cleanString.push_back(s.substr(start, end - start));
                } while (end != -1);
                return cleanString;
            }
};