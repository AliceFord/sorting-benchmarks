#include <bits/stdc++.h>

using namespace std;

template <typename T> void printvec(vector<T> *v) {
    for (std::vector<int>::iterator i=v->begin(); i!=v->end(); i++)
        std::cout << *i << " ";
    std::cout << std::endl;
}

int main() {
    const size_t t2Size = 20;
    vector<int> t2(t2Size);
    for (int i = 0; i < t2Size; i++) t2[i] = i+1;
    iter_swap(t2.begin() + 15, t2.begin() + 16);
    printvec(&t2);
}

// int main() {
//   int arr[] = {1,2,3,4,5,6,7,8,9};
//   std::vector<int> * v = new std::vector<int>(arr, arr + sizeof(arr) / sizeof(arr[0]));
//   iter_swap(v->begin(),v->begin()+1);
//   for (std::vector<int>::iterator i=v->begin(); i!=v->end(); i++)
//     std::cout << *i << " ";
//   std::cout << std::endl;
// }