#include <vector>
#include <algorithm>
#include <cmath>
#include <random>
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
            cout << "pivot " << pivot << endl;
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
    template <typename T>
    // Function to perform Cholesky decomposition
    bool cholesky_decomposition(const vector<vector<T>> &cov, vector<vector<T>> &L)
    {
        int d = cov.size();
        L = vector<vector<T>>(d, vector<T>(d, 0.0));

        for (int i = 0; i < d; ++i)
        {
            for (int j = 0; j <= i; ++j)
            {
                T sum = cov[i][j];
                for (int k = 0; k < j; ++k)
                {
                    sum -= L[i][k] * L[j][k];
                }
                if (i == j)
                {
                    if (sum <= 0)
                        return false; // Not positive definite
                    L[i][j] = sqrt(sum);
                }
                else
                {
                    L[i][j] = sum / L[j][j];
                }
            }
        }
        return true;
    }
    template <typename T>
    // Function to generate samples from a multivariate normal distribution
    vector<vector<T>> generate_multivariate_normal(const vector<T> &mean, const vector<vector<T>> &cov, int sample_size)
    {
        int d = mean.size(); // dimensionality of the distribution
        vector<vector<T>> samples;

        // Cholesky decomposition of the covariance matrix
        vector<vector<T>> L;
        if (!cholesky_decomposition(cov, L))
        {
            cerr << "Error: Covariance matrix is not positive definite!" << endl;
            return samples; // Return empty vector if decomposition fails
        }

        // Random number generator
        random_device rd;
        mt19937 gen(rd());
        normal_distribution<> dist(0.0, 1.0); // standard normal distribution

        // Generate samples
        for (int i = 0; i < sample_size; ++i)
        {
            // Generate standard normal random vector
            vector<T> z(d);
            for (int j = 0; j < d; ++j)
            {
                z[j] = dist(gen);
            }

            // Transform to the desired distribution
            vector<T> sample(d, 0.0);
            for (int j = 0; j < d; ++j)
            {
                sample[j] = mean[j];
                for (int k = 0; k < d; ++k)
                {
                    sample[j] += L[j][k] * z[k];
                }
            }
            samples.push_back(sample);
        }

        return samples;
    }

    
};