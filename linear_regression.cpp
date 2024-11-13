#include <iostream>
#include <vector>
#include <numeric>
#include "fileHandler.cpp"
#include "vectorUtilities.cpp"

using namespace std;
float dot_product(const std::vector<std::vector<int>> &e, const std::vector<int> &p)
{
    float result = 0;
    for (auto &v : e) // range based loop
        result += std::inner_product(v.begin(), v.end(), p.begin(), 0.0);
    return result;
}
int main()
{
    FileHandler fileHandler;
    VectorUtilities vectorUtilities;
    //each row of inout file converted as a vector
    
    std::vector<std::vector<float>> xInput = fileHandler.convertDataToNumber<float>("x_input.txt");
    std::vector<std::vector<float>> yInput = fileHandler.convertDataToNumber<float>("y_input.txt");
    std::vector<float> x = xInput.at(0);
    std::vector<float> y = yInput.at(0);

    std::vector<std::vector<float>> xInputTranspose = vectorUtilities.transposeToColumnVector(x);
    std::vector<std::vector<float>> A = vectorUtilities.multiplyMatrices(xInputTranspose, xInput);
    cout<<A[0][0]<<endl;
    // std::vector<std::vector<float>> AInverse = vectorUtilities.invertMatrix(A);
// std::vector<std::vector<float>> b = vectorUtilities.multiplyMatrices(xInputTranspose, yInput);
// std::vector<std::vector<float>> w = vectorUtilities.multiplyMatrices(AInverse, b);

    for(std::vector<float> i : A){
        for (float j : i){
            cout<<j<<endl;
        }
    }

    
    return 0;
}