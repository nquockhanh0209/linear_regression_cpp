#include<iostream>
#include<vector>
#include "vectorUtilities.cpp"
#include <limits.h> // For INT_MAX
using namespace std;

double getDist(double x1, double y1, double x2, double y2){
    return sqrt(((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2)));
}

// Function to find the minimum value in an array
int findMinOfArray(const std::vector<double>& arr) {
    int min_value = INT_MAX;  // Initialize to maximum integer value
    int indexMin = 0;

    for (int i = 0; i<arr.size(); i++) {
        

        if (arr[i] < min_value) {

            min_value = arr[i];  // Update min_value if a smaller element is found
            indexMin = i;
        }
    }

    return indexMin;
}

vector<vector<double>> defineCenters(vector<vector<double>> X, int K){
    vector<vector<double>> centers ={};
    for(int i = 0; i<K; i++){
        int index = rand()%X.size();
        centers.push_back(X[index]);
    }
    return centers;
}
vector<vector<int>> defineCluster(vector<vector<double>> X, vector<vector<double>> centers, int K){
    vector<vector<int>> clusters; 
    
    for(int j = 0; j<K; j++){
        clusters.push_back({});
    }
    for (int i = 0; i<X.size(); i++){
        vector<double> dis = {};
        for(int j = 0; j<K; j++){
            dis.push_back(getDist(X[i][0], X[i][1], centers[j][0], centers[j][1]));
        }
        int index = findMinOfArray(dis);
        clusters[index].push_back(i);
    }
    return clusters;
}
vector<double> centerOfCluster(vector<vector<double>> X, vector<int> indexOfCluster){
    double sumX = 0;
    double sumY = 0;
    for (double index : indexOfCluster){
        sumX += X[index][0];
        sumY += X[index][1];
    }
    return {sumX/indexOfCluster.size(), sumY/indexOfCluster.size()};
}
vector<vector<double>> findCenters(vector<vector<double>> X, vector<vector<double>> centers, int K){
    vector<vector<int>> indexOfClusters = defineCluster(X, centers, K);
    vector<vector<double>> finalCenters = {};
    for (vector<int> index : indexOfClusters){
        cout<<index.size()<<endl;
        finalCenters.push_back(centerOfCluster(X, index));
    }
    return finalCenters;
}
int main(){
    VectorUtilities vectorUtilities;
    int N = 500;
    int K = 3;
    vector<vector<double>> realCenter = {{2, 2},{8, 3},{3, 6}};
    vector<vector<double>> coverage = {{1, 0},{0, 1}};
    vector<vector<double>> X;
    vector<vector<double>> X0 = vectorUtilities.generate_multivariate_normal(realCenter[0], coverage, N);
    vector<vector<double>> X1 = vectorUtilities.generate_multivariate_normal(realCenter[1], coverage, N);
    vector<vector<double>> X2 = vectorUtilities.generate_multivariate_normal(realCenter[2], coverage, N);

    for(int i = 0; i<N; i++){
        X.push_back(X0[i]);
        X.push_back(X1[i]);
        X.push_back(X2[i]);
    }

    vector<vector<double>> initCenters = defineCenters(X, K);
    // vector<vector<double>> finalCenters;
    for(int i = 0; i<K;i++){
        initCenters = findCenters(X, initCenters, K);
    }
;

    
    for(vector<double> points: initCenters){
        for(double coordinates: points){
            cout<< coordinates<< " ";
        }
        cout<<endl;
    }
    return 0;
}