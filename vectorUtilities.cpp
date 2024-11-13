#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
class VectorUtilities
{
public:
    template <typename T>
    std::vector<std::vector<T>> transposeToColumnVector(const std::vector<T> &rowVector)
    {
        std::vector<std::vector<T>> columnVector;
        for (T element : rowVector)
        {
            columnVector.push_back({element});
        }
        return columnVector;
    }

    template <typename T>
    std::vector<std::vector<T>> multiplyMatrices(const std::vector<std::vector<T>> &mat1, const std::vector<std::vector<T>> &mat2)
    {
        size_t rows1 = mat1.size();
        size_t cols1 = mat1[0].size();
        size_t rows2 = mat2.size();
        size_t cols2 = mat2[0].size();

        if (cols1 != rows2)
        {
            throw std::invalid_argument("Number of columns in the first matrix must equal the number of rows in the second matrix.");
        }

        std::vector<std::vector<T>> result(rows1, std::vector<T>(cols2, 0));
        for (size_t i = 0; i < rows1; ++i)
        {
            for (size_t j = 0; j < cols2; ++j)
            {
                for (size_t k = 0; k < cols1; ++k)
                {
                    result[i][j] += mat1[i][k] * mat2[k][j];
                }
            }
        }
        return result;
    }

    // Function to convert column std::vector (std::vector<std::vector<int>>) to row std::vector (std::vector<int>)
    template <typename T>
    std::vector<T> convertToRowVector(const std::vector<std::vector<T>> &columnVec)
    {
        std::vector<T> rowVec;

        // Iterate through each element in the column std::vector (which is a std::vector of vectors)
        for (const auto &element : columnVec)
        {

            rowVec.push_back(element.at(0)); // Extract the element from the inner std::vector and add to rowVec
        }

        return rowVec;
    }
    template <typename T>
    // Helper function to transpose a matrix
    std::vector<std::vector<T>> transpose(const std::vector<std::vector<T>> &matrix)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();
        std::vector<std::vector<T>> transposed(cols, std::vector<T>(rows));
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                transposed[j][i] = matrix[i][j];
            }
        }
        return transposed;
    };

    template <typename T>
    vector<vector<T>> getIdentityMatrix(int n)
    {
        vector<vector<T>> identity(n, vector<T>(n, 0.0));
        for (int i = 0; i < n; i++)
        {
            identity[i][i] = 1.0;
        }
        return identity;
    }
    template <typename T>
    vector<vector<T>> invertMatrix(vector<vector<T>> matrix)
    {
        int n = matrix.size();
        vector<vector<T>> inverse = getIdentityMatrix<T>(n);

        for (int i = 0; i < n; i++)
        {
            T pivot = matrix[i][i];
            cout<<"pivot "<<pivot<<endl;
            if (pivot == 0)
            {
                cerr << "vector<vector<double>> is singular and cannot be inverted." << endl;
                exit(1);
            }

            for (int j = 0; j < n; j++)
            {
                matrix[i][j] /= pivot;
                inverse[i][j] /= pivot;
            }

            for (int k = 0; k < n; k++)
            {
                if (k != i)
                {
                    T factor = matrix[k][i];
                    for (int j = 0; j < n; j++)
                    {
                        matrix[k][j] -= factor * matrix[i][j];
                        inverse[k][j] -= factor * inverse[i][j];
                    }
                }
            }
        }
        return inverse;
    }
};