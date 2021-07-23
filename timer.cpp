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

void oddEvenSort(vector<int> *arr) {
    bool sorted = false;
    int n = arr->size();
    while (!sorted) {
        sorted = true;
        for (int i = 1; i < n - 1; i += 2) {
            if ((*arr)[i] > (*arr)[i + 1]) {
                iter_swap(arr->begin() + i, arr->begin() + i + 1);
                sorted = false;
            }
        }
        for (int i = 0; i < n - 1; i += 2) {
            if ((*arr)[i] > (*arr)[i + 1]) {
                iter_swap(arr->begin() + i, arr->begin() + i + 1);
                sorted = false;
            }
        }
    }
}

void gnomeSort(vector<int> *arr) {
    int n = arr->size();
    int pos = 0;
    while (pos < n) {
        if (pos == 0 || (*arr)[pos] >= (*arr)[pos - 1])
            pos++;
        else {
            iter_swap(arr->begin() + pos, arr->begin() + pos - 1);
            pos--;
        }
    }
}

void combSort(vector<int> *arr) {
    int n = arr->size(), gap = arr->size();
    float shrink = 1.3;
    bool sorted = false;

    while (sorted == false) {
        gap = floor(gap / shrink);
        if (gap <= 1) {
            gap = 1;
            sorted = true;
        }

        for (int i = 0; i + gap < n; i++) {
            if ((*arr)[i] > (*arr)[i + gap]) {
                iter_swap(arr->begin() + i, arr->begin() + i + gap);
                sorted = false;
            }
        }
    }
}

void cocktailShakerSort(vector<int> *arr) {
    bool swapped;
    int n = arr->size();
    do {
        swapped = false;
        for (int i = 0; i < n - 1; i++) {
            if ((*arr)[i] > (*arr)[i + 1]) {
                iter_swap(arr->begin() + i, arr->begin() + i + 1);
                swapped = true;
            }
        }
        if (!swapped) break;

        for (int i = 0; i < n - 1; i++) {
            if ((*arr)[i] > (*arr)[i + 1]) {
                iter_swap(arr->begin() + i, arr->begin() + i + 1);
                swapped = true;
            }
        }
    } while (swapped);
}

void defaultsort(vector<int> *arr) {
    sort(arr->begin(), arr->end());
}

void strandSortIter(vector<int> *finalarr, bool *first, vector<int> *arr) {
    if (arr->size() == 0) return;
    vector<int> sublist;

    sublist.push_back((*arr)[0]);
    arr->erase(arr->begin());

    int i = 0;
    for (int j = 0; j < arr->size(); j++) {
        if ((*arr)[j] > sublist[i]) {
            sublist.push_back((*arr)[j]);
            arr->erase(arr->begin() + j);
            j--;
            i++;
        }
    }

    if (!(*first)) {
        for (i = 0; i < sublist.size(); i++) {
            finalarr->push_back(sublist[i]);
        }
        (*first) = true;
    } else {
        int subend = sublist.size() - 1;
        int finalarrstart = 0;
        while (sublist.size() > 0) {
            if (sublist[subend] > (*finalarr)[finalarrstart]) {
                finalarrstart++;
            } else {
                finalarr->insert(finalarr->begin() + finalarrstart, sublist[subend]);
                sublist.erase(sublist.begin() + subend);
                subend--;
                finalarrstart = 0;
            }
        }
    }
    strandSortIter(finalarr, first, arr);
}

void strandSort(vector<int> *arr) {
    bool first = false;
    vector<int> *response = new vector<int>();
    strandSortIter(response, &first, arr);
    arr->swap(*response);
}

void cycleSort(vector<int> *arr) {
    size_t n = arr->size();
    for (int i = 0; i < n - 1; i++) {
        int item = (*arr)[i];
        int pos = i;
        for (int j = i + 1; j < n; j++) {
            if ((*arr)[j] < item)
                pos++;
        }
        if (pos == i) continue;

        while (item == (*arr)[pos]) pos++;

        int _temp = item;
        item = (*arr)[pos];
        (*arr)[pos] = _temp;

        while (pos != i) {
            pos = i;
            for (int j = i + 1; j < n; j++) {
                if ((*arr)[j] < item)
                    pos++;
            }

            while (item == (*arr)[pos]) pos++;
            int _temp = item;
            item = (*arr)[pos];
            (*arr)[pos] = _temp;
        }
    }
}

// Implement best case (presorted) and also number of writes. Divide sorts / sec by writes?

void (*funcs[])(vector<int> *arr) = { cycleSort };  // cocktailShakerSort, selectionSort, insertionSort, bubbleSort, oddEvenSort, gnomeSort, defaultsort, combSort, strandSort
std::string names[] = { "Cycle Sort" };  // "Cocktail Shaker Sort", "Selection Sort", "Insertion Sort", "Bubble Sort", "Odd-Even Sort", "Gnome Sort", "STL Sort (Introsort + Insertion sort)", "Comb Sort", "Strand Sort"
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
                atomic<bool> threadFinished(false);
                thread t([&threadFinished] {
                    this_thread::sleep_for(chrono::seconds(1));
                    threadFinished = true;
                });
                while (!threadFinished) {
                    (*funcs[i])(&tests[j]);
                    if (!is_sorted(tests[j].begin(), tests[j].end())) throw names[i] + " failed!";
                    refreshArray(&tests[j], j);
                    times++;
                }
                t.join();

                current.push_back(times);
            }
            output[i].push_back(accumulate(current.begin(), current.end(), 0) / current.size());
        }
    }

    ofstream outfile;
    outfile.open("merge.csv", ios_base::app);
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
