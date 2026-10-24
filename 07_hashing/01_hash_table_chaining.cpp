// Hash table with separate chaining: an array of buckets, each bucket is a linked list.
// bucketIndex = key % capacity picks the bucket. Keys that collide just join that bucket's list.
//
// put / get / remove: O(1) on average, O(n) worst case (every key lands in one bucket).
// Load factor = count / capacity. When it goes above 0.75 we double the capacity and
// move every node to its new bucket (rehash), which keeps the lists short.
#include <iostream>
#include <vector>
using namespace std;

struct HashNode {
    int key;
    int value;
    HashNode* next;
    HashNode(int keyToStore, int valueToStore)
        : key(keyToStore), value(valueToStore), next(nullptr) {}
};

class HashTableChaining {
private:
    vector<HashNode*> buckets;
    int capacity;
    int count;

    // The extra "+ capacity" keeps the result non-negative for negative keys.
    static int bucketIndexFor(int key, int bucketCount) {
        return ((key % bucketCount) + bucketCount) % bucketCount;
    }

    void resize() {
        int newCapacity = capacity * 2;
        vector<HashNode*> newBuckets(newCapacity, nullptr);

        for (int oldIndex = 0; oldIndex < capacity; oldIndex++) {
            HashNode* current = buckets[oldIndex];
            while (current != nullptr) {
                HashNode* nextNode = current->next;               // save before relinking
                int newIndex = bucketIndexFor(current->key, newCapacity);
                current->next = newBuckets[newIndex];             // insert at head of new bucket
                newBuckets[newIndex] = current;
                current = nextNode;
            }
        }
        buckets = newBuckets;
        capacity = newCapacity;
    }

public:
    HashTableChaining(int initialCapacity = 5)
        : buckets(initialCapacity, nullptr), capacity(initialCapacity), count(0) {}

    // Raw pointers inside, so copying is disabled (a copy would share and double-delete nodes).
    HashTableChaining(const HashTableChaining&) = delete;
    HashTableChaining& operator=(const HashTableChaining&) = delete;

    ~HashTableChaining() {
        for (int index = 0; index < capacity; index++) {
            HashNode* current = buckets[index];
            while (current != nullptr) {
                HashNode* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
    }

    int size() const { return count; }

    void put(int key, int value) {
        int index = bucketIndexFor(key, capacity);

        // if the key already exists, just update its value
        for (HashNode* current = buckets[index]; current != nullptr; current = current->next) {
            if (current->key == key) {
                current->value = value;
                return;
            }
        }

        // new key: insert at the head of the bucket list, O(1)
        HashNode* newNode = new HashNode(key, value);
        newNode->next = buckets[index];
        buckets[index] = newNode;
        count++;

        if (count * 4 > capacity * 3) resize();                   // load factor > 0.75
    }

    bool get(int key, int& foundValue) const {
        int index = bucketIndexFor(key, capacity);
        for (HashNode* current = buckets[index]; current != nullptr; current = current->next) {
            if (current->key == key) {
                foundValue = current->value;
                return true;
            }
        }
        return false;
    }

    bool remove(int key) {
        int index = bucketIndexFor(key, capacity);
        HashNode* previous = nullptr;
        HashNode* current = buckets[index];
        while (current != nullptr) {
            if (current->key == key) {
                if (previous == nullptr) buckets[index] = current->next;   // removing the head
                else previous->next = current->next;
                delete current;
                count--;
                return true;
            }
            previous = current;
            current = current->next;
        }
        return false;
    }

    void print() const {
        for (int index = 0; index < capacity; index++) {
            cout << "[" << index << "]";
            for (HashNode* current = buckets[index]; current != nullptr; current = current->next) {
                cout << " " << current->key << ":" << current->value;
            }
            cout << endl;
        }
    }
};

int main() {
    HashTableChaining table(5);

    // 10, 15, 20 all have key % 5 == 0, so they collide in bucket 0
    table.put(10, 100);
    table.put(15, 150);
    table.put(20, 200);
    table.print();
    // [0] 20:200 15:150 10:100   (three keys chained in bucket 0, newest first)
    // [1] .. [4] are empty

    table.put(7, 70);                  // 4th key: load factor 4/5 > 0.75, so the table doubles to 10
    cout << "After resize:" << endl;
    table.print();
    // [0] 10:100 20:200   [5] 15:150   [7] 7:70   (others empty)
    // 10 and 20 still share bucket 0 (both % 10 == 0), but 15 moved to bucket 5.

    int foundValue = 0;
    if (table.get(15, foundValue)) cout << "get(15) = " << foundValue << endl;   // 150
    cout << "get(99) found? " << (table.get(99, foundValue) ? "yes" : "no") << endl;   // no

    table.put(15, 999);                                           // update existing key
    table.get(15, foundValue);
    cout << "after update get(15) = " << foundValue << endl;      // 999

    cout << "remove(10): " << (table.remove(10) ? "removed" : "not found") << endl;    // removed
    cout << "remove(10) again: " << (table.remove(10) ? "removed" : "not found") << endl;   // not found
    cout << "size = " << table.size() << endl;                    // 3
    return 0;
}
