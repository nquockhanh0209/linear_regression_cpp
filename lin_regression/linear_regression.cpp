#include <iostream>
#include <vector>
#include <numeric>
#include "utils/fileHandler.cpp"
#include "utils/vectorUtilities.cpp"
using namespace std;
int main()
{
    FileHandler fileHandler;
    VectorUtilities vectorUtilities;
    //each row of inout file converted as a vector
    
    std::vector<std::vector<double>> xInput = fileHandler.convertDataToNumber<double>("x_input.txt");
    std::vector<std::vector<double>> yInput = fileHandler.convertDataToNumber<double>("y_input.txt");
    std::vector<double> x = xInput.at(0);
    std::vector<double> y = yInput.at(0);
    // need to add vector 1 to X as bias 
    vector<double> vectorOne = vector<double>(xInput[0].size(), 1.0);
    xInput.push_back(vectorOne);

    //input vector of x and y should be at coulumn vector format
    std::vector<std::vector<double>> yInputTranspose = vectorUtilities.transpose(yInput);
    std::vector<std::vector<double>> xInputTranspose = vectorUtilities.transpose(xInput);

    //handle create A and b
    std::vector<std::vector<double>> A = vectorUtilities.multiplyMatrices(xInput, xInputTranspose);
    std::vector<std::vector<double>> AInverse = vectorUtilities.invertMatrix(A);
std::vector<std::vector<double>> b = vectorUtilities.multiplyMatrices(xInput, yInputTranspose);
std::vector<std::vector<double>> w = vectorUtilities.multiplyMatrices(AInverse, b);

    for(std::vector<double> i : w){
        for (double j : i){
            cout<<j<<",";
        }
        cout<<endl;
    }

    
    return 0;
}