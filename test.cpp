#include <iostream>
#include <vector>
#include <random>
#include <cmath>
#include <limits.h> // For INT_MAX
#include <fileHandler.cpp>
using namespace std;

int main() {
    FileHandler fileHandler;
    fileHandler.handleReadCsv("dataset/weather.csv");
}
