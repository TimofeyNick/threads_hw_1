#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <thread>
#include <mutex>

using namespace std;

std::recursive_mutex g_lock;

int size = 5;
//умножение будет на квадратную матрицу size*size

vector<int> inputVector()
{
    vector<int> vec;
    vec.reserve(size);
    int tmp;
    for(int i =0; i != size; i++){
        cin >> tmp;
        vec.push_back(tmp);
    }
    return vec;
}

void dumpVector(vector<int> vec)
{
    cout << "\n";
    cout << "This is your vector:\n\n";
    for(auto it: vec){
        cout << it << "\t\t";
    }
    cout << "\n";
}

vector<vector<int>> matrixInput()
{
    vector<vector<int>> matrix;

    matrix.resize(size);

    int tmp;
    for ( auto & row : matrix ){
        for ( int i =0; i != size ; i++){
            std::cin >> tmp;
            row.push_back(tmp);
        }
    }

    return matrix;
}

void dumpMatrix(vector<vector<int>> matrix)
{
    std::cout << "This is your matrix:\n\n";
    for ( const auto & row : matrix ){
        for ( const auto & element : row ){
            std::cout << element << "\t\t";
        }
            std::cout << "\n";
    }
}

void func1(vector<int> vec, vector<vector<int>> matrix, vector<int>& vec1, int i)
{
    int tmp = 0;
    for(int k = 0; k!= size; k++){
        tmp = tmp + matrix[k][i]*vec[k];
    }
    g_lock.lock();

    vec1[i] = tmp;

    g_lock.unlock();
}

vector<int> multiplication(vector<int> vec, vector<vector<int>> matrix)
{
    std::vector<int> vec1;
    vec1.resize(size);

    std::thread thr0(func1, vec, matrix, std::ref(vec1), 0);
    std::thread thr1(func1, vec, matrix, std::ref(vec1), 1);
    std::thread thr2(func1, vec, matrix, std::ref(vec1), 2);
    std::thread thr3(func1, vec, matrix, std::ref(vec1), 3);
    std::thread thr4(func1, vec, matrix, std::ref(vec1), 4);
    thr0.join();
    thr1.join();
    thr2.join();
    thr3.join();
    thr4.join();

//    int tmp = 0;
//    for (int i = 0; i != size; i++){
//        for(int k = 0; k!= size; k++){
//             tmp = tmp + matrix[k][i]*vec[k];
//        }
//        vec1[i] = tmp;
//        tmp = 0;
//    }

    return vec1;
}

int main()
{
    vector<int> vec = inputVector();
    vector<vector<int>> matrix = matrixInput();
    dumpVector(vec);
    dumpMatrix(matrix);
    vector<int> vec1 = multiplication(vec, matrix);
    dumpVector(vec1);
    return 0;
}
