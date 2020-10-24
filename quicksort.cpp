#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

size_t random(size_t min, size_t max) {
    return rand() % (max - min) + min;
}

size_t partition(vector<int>& a, size_t l, size_t r) {
    const int pivot = a[random(l, r)];
    --r;
    do {
        while (a[l] < pivot) ++l;
        while (a[r] > pivot) --r;

        if (l < r) {
            swap(a[l], a[r]);
            ++l;
            --r;
        }
    } while (l < r);
    return l;
}


void quicksort(vector<int>& a, size_t l, size_t r) {
    if (l < r) {
        const size_t p = partition(a, l, r);
        quicksort(a, l, p);
        quicksort(a, p + 1, r);
    }
}


int main() {
    vector<int> a = {1, 58, 4, 12, 42, 0, -5};

    cout << "before sort:\n";
    for (int item : a) {
        cout << item << ' ';
    }
    cout << endl;

    quicksort(a, 0, a.size());

    cout << "after sort:\n";
    for (int item : a) {
        cout << item << ' ';
    }
    cout << endl;

    return 0;
}
