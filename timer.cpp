#include <bits/stdc++.h>
#include <chrono>
#include <random>
#include <future>
#include <thread>

using namespace std;

template <typename T> void printvec(vector<T> *v) {
    for (std::vector<int>::iterator i=v->begin(); i!=v->end(); i++)
        std::cout << *i << " ";
    std::cout << std::endl;
}
 
void selectionSort(vector<int> *arr) {
    int min_idx;
    int n = arr->size();
 
    for (int i = 0; i < n-1; i++)
    {
        min_idx = i;
        for (int j = i+1; j < n; j++)
        if ((*arr)[j] < (*arr)[min_idx])
            min_idx = j;
 
        iter_swap(arr->begin() + min_idx, arr->begin() + i);
    }
}

void insertionSort(vector<int> *arr) {
    int n = arr->size();
    int key, j;
    for (int i = 1; i < n; i++)
    {
        key = (*arr)[i];
        j = i - 1;
 
        while (j >= 0 && (*arr)[j] > key)
        {
            (*arr)[j + 1] = (*arr)[j];
            j = j - 1;
        }
        (*arr)[j + 1] = key;
    }
}

void bubbleSort(vector<int> *arr) {
    int n = arr->size();
    for (int i = 0; i < n-1; i++)    
        for (int j = 0; j < n-i-1; j++)
            if ((*arr)[j] > (*arr)[j+1])
                iter_swap(arr->begin() + j, arr->begin() + j+1);
}

void defaultsort(vector<int> *arr) {
    sort(arr->begin(), arr->end());
}

void (*funcs[])(vector<int> *arr) = { selectionSort, insertionSort, bubbleSort, defaultsort };
std::string names[] = {"Selection Sort", "Insertion Sort", "Bubble Sort", "STL Sort"};
static random_device rd;
static mt19937 rng {rd()};

int randomNumBetweenVals(int v1, int v2) {
    uniform_int_distribution<int> num(v1, v2);
    return num(rng);
}

const size_t N = 10000;
vector<vector<int>> tests;

vector<vector<int>> setupArrays() {  // Random, nearly sorted, reversed, few unique
    vector<vector<int>> tests;
    vector<int> t1(N);
    for (int i = 0; i < N; i++) t1[i] = i+1;
    shuffle(t1.begin(), t1.end(), rng);
    tests.push_back(t1);

    vector<int> t2(N);
    for (int i = 0; i < N; i++) t2[i] = i+1;
    for (int i = 0; i < N/4; i++) {
        int pos = randomNumBetweenVals(1, N-1);
        iter_swap(t2.begin() + pos, t2.begin() + pos - 1);
    }
    tests.push_back(t2);

    vector<int> t3(N);
    for (int i = 0; i < N; i++) t3[i] = N - i;
    tests.push_back(t3);

    vector<int> t4(N);
    for (int i = 0; i < N; i++) t4[i] = (i / 10) + 1;
    tests.push_back(t4);
    shuffle(t4.begin(), t4.end(), rng);
    return tests;
}

vector<vector<int>> copyArrays = setupArrays();

void refreshArray(vector<int> *arr, int whicharr) {
    arr->resize(N);
    *arr = copyArrays[whicharr];
    // switch (whicharr) {
    // case 0:
    //     for (int i = 0; i < N; i++) (*arr)[i] = i+1;
    //     shuffle(arr->begin(), arr->end(), rng);
    //     break;
    
    // case 1:
    //     for (int i = 0; i < N; i++) (*arr)[i] = i+1;
    //     for (int i = 0; i < N/4; i++) {
    //         int pos = randomNumBetweenVals(1, N-1);
    //         iter_swap(arr->begin() + pos, arr->begin() + pos - 1);
    //     }
    //     break;
    
    // case 2:
    //     for (int i = 0; i < N; i++) (*arr)[i] = N - i;
    //     break;

    // case 3:
    //     for (int i = 0; i < N; i++) (*arr)[i] = (i / 10) + 1;
    //     shuffle(arr->begin(), arr->end(), rng);
    //     break;
    
    // default:
    //     break;
    // }
}

bool isarrSorted(vector<int> *arr) {
    int prev = -1;
    for (const auto &item : *arr) {
        if (item < prev) {
            return false;
        }
        prev = item;
    }
    return true;
}

void functionRunner(future<void> ender, int i, int j, int &times) {
    while (ender.wait_for(chrono::microseconds(1)) == future_status::timeout) {
        (*funcs[i])(&tests[j]);
        refreshArray(&tests[j], j);
        times++;
    }
}

int main() {
    int numFuncs = sizeof(funcs) / sizeof(funcs[0]);
    int repeats = 3;
    vector<vector<long long>> output(numFuncs);
    vector<long long> current(tests.size());
    for (int i = 0; i < numFuncs; i++) {  // For each sorting function
        tests = setupArrays();
        for (int j = 0; j < tests.size(); j++) {  // For each test
            current.clear();
            for (int k = 0; k < repeats; k++) {  // For each repeat
                cout << "Running function '" << names[i] << "', test " << j+1 << ", repeat " << k+1 << "\n";
                int times = 0;
                promise<void> exitSignal;
                future<void> futureObj = exitSignal.get_future();
                thread th(&functionRunner, move(futureObj), i, j, ref(times));
                this_thread::sleep_for(chrono::seconds(1));
                exitSignal.set_value();
                th.join();

                // if (!isarrSorted(&tests[j])) throw names[i] + " failed!";
                current.push_back(times);
            }
            output[i].push_back(accumulate(current.begin(), current.end(), 0) / current.size());
        }
    }

    ofstream outfile;
    outfile.open("merge.csv");
    for (int i = 0; i < numFuncs; i++) {  // For each sorting function
        outfile << names[i] << ",";
        for (int j = 0; j < tests.size(); j++) {  // For each test
            outfile << output[i][j];
            if (j != tests.size()-1) {
                outfile << ",";
            }
        }
        outfile << "\n";
    }
    outfile.close();
    return 0;
}
