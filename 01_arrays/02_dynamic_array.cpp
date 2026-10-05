// Dynamic array: our own mini std::vector.
// When full, allocate a new array of double the capacity and copy everything.
// Doubling makes push_back O(1) amortized.
#include <iostream>
using namespace std;

class DynamicArray {
private:
    int* data;
    int size;
    int capacity;

    void grow() {
        int newCapacity = capacity * 2;
        int* newData = new int[newCapacity];
        for (int i = 0; i < size; i++) newData[i] = data[i];
        delete[] data;
        data = newData;
        capacity = newCapacity;
        cout << "(resized to capacity " << capacity << ")" << endl;
    }

public:
    DynamicArray() : size(0), capacity(2) { data = new int[capacity]; }
    ~DynamicArray() { delete[] data; }

    void pushBack(int value) {
        if (size == capacity) grow();
        data[size++] = value;
    }

    void popBack() {
        if (size == 0) { cout << "Empty" << endl; return; }
        size--;
    }

    int get(int index) const {
        if (index < 0 || index >= size) { cout << "Bad index" << endl; return -1; }
        return data[index];
    }

    void insertAt(int index, int value) {
        if (index < 0 || index > size) { cout << "Bad index" << endl; return; }
        if (size == capacity) grow();
        for (int i = size; i > index; i--) data[i] = data[i - 1];
        data[index] = value;
        size++;
    }

    int getSize() const { return size; }

    void print() const {
        for (int i = 0; i < size; i++) cout << data[i] << " ";
        cout << endl;
    }
};

int main() {
    DynamicArray arr;
    for (int i = 1; i <= 5; i++) arr.pushBack(i * 10);  // triggers resizes
    arr.print();                                        // 10 20 30 40 50
    arr.insertAt(1, 15);
    arr.print();                                        // 10 15 20 30 40 50
    arr.popBack();
    arr.print();                                        // 10 15 20 30 40
    cout << "arr[2] = " << arr.get(2) << ", size = " << arr.getSize() << endl;
    return 0;
}
