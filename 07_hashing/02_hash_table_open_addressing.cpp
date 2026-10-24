// Hash table with open addressing (linear probing): everything lives inside ONE array.
// If the home slot (key % capacity) is taken, try the next slot, then the next, wrapping around.
//
// Each slot is EMPTY, OCCUPIED or DELETED.
// Why DELETED (a "tombstone") and not EMPTY after remove?
//   A search stops at the first EMPTY slot. If remove made a slot EMPTY, keys that were
//   placed after it (because of a collision) would become unreachable.
//
// put / get / remove: O(1) average while the table is not nearly full, O(n) worst case.
// This simple version has a fixed capacity; put() returns false when there is no room.
#include <iostream>
#include <vector>
using namespace std;

enum SlotState { EMPTY, OCCUPIED, DELETED };

struct Slot {
    int key;
    int value;
    SlotState state;
    Slot() : key(0), value(0), state(EMPTY) {}
};

class HashTableLinearProbing {
private:
    vector<Slot> slots;
    int capacity;
    int count;                    // number of OCCUPIED slots

    int homeIndexFor(int key) const {
        return ((key % capacity) + capacity) % capacity;
    }

public:
    HashTableLinearProbing(int tableCapacity) : slots(tableCapacity), capacity(tableCapacity), count(0) {}

    int size() const { return count; }

    bool put(int key, int value) {
        int homeIndex = homeIndexFor(key);
        int firstDeletedIndex = -1;           // reuse the first tombstone we pass, if any

        for (int probe = 0; probe < capacity; probe++) {
            int index = (homeIndex + probe) % capacity;

            if (slots[index].state == EMPTY) {
                // key is definitely not in the table, insert (prefer an earlier tombstone)
                int target = (firstDeletedIndex != -1) ? firstDeletedIndex : index;
                slots[target].key = key;
                slots[target].value = value;
                slots[target].state = OCCUPIED;
                count++;
                return true;
            }
            if (slots[index].state == DELETED) {
                if (firstDeletedIndex == -1) firstDeletedIndex = index;
                continue;                      // keep looking, the key may be further along
            }
            if (slots[index].key == key) {     // OCCUPIED with the same key: update
                slots[index].value = value;
                return true;
            }
        }

        // went around the whole table without finding an EMPTY slot
        if (firstDeletedIndex != -1) {
            slots[firstDeletedIndex].key = key;
            slots[firstDeletedIndex].value = value;
            slots[firstDeletedIndex].state = OCCUPIED;
            count++;
            return true;
        }
        return false;                          // table is full
    }

    bool get(int key, int& foundValue) const {
        int homeIndex = homeIndexFor(key);
        for (int probe = 0; probe < capacity; probe++) {
            int index = (homeIndex + probe) % capacity;
            if (slots[index].state == EMPTY) return false;       // chain ends here
            if (slots[index].state == OCCUPIED && slots[index].key == key) {
                foundValue = slots[index].value;
                return true;
            }
            // DELETED or another key: keep probing
        }
        return false;
    }

    bool remove(int key) {
        int homeIndex = homeIndexFor(key);
        for (int probe = 0; probe < capacity; probe++) {
            int index = (homeIndex + probe) % capacity;
            if (slots[index].state == EMPTY) return false;
            if (slots[index].state == OCCUPIED && slots[index].key == key) {
                slots[index].state = DELETED;                    // tombstone, NOT empty
                count--;
                return true;
            }
        }
        return false;
    }

    void print() const {
        for (int index = 0; index < capacity; index++) {
            cout << "[" << index << "] ";
            if (slots[index].state == EMPTY) cout << "empty";
            else if (slots[index].state == DELETED) cout << "deleted";
            else cout << slots[index].key << ":" << slots[index].value;
            cout << endl;
        }
    }
};

int main() {
    HashTableLinearProbing table(7);

    table.put(10, 100);       // 10 % 7 = 3  -> slot 3
    table.put(17, 170);       // 17 % 7 = 3  -> collision, probes to slot 4
    table.put(24, 240);       // 24 % 7 = 3  -> collision, probes to slot 5
    table.put(5, 50);         //  5 % 7 = 5  -> slot 5 taken, probes to slot 6
    table.print();
    // [3] 10:100  [4] 17:170  [5] 24:240  [6] 5:50  (slots 0, 1, 2 empty)

    table.remove(17);         // slot 4 becomes a tombstone
    cout << "After remove(17):" << endl;
    table.print();
    // [3] 10:100  [4] deleted  [5] 24:240  [6] 5:50

    int foundValue = 0;
    // 24 was placed AFTER the tombstone. This still works because we skip DELETED slots.
    cout << "get(24) found? " << (table.get(24, foundValue) ? "yes" : "no")
         << ", value = " << foundValue << endl;               // yes, 240

    table.put(31, 310);       // 31 % 7 = 3 -> reuses the tombstone at slot 4
    cout << "After put(31):" << endl;
    table.print();
    // [3] 10:100  [4] 31:310  [5] 24:240  [6] 5:50
    cout << "size = " << table.size() << endl;
    return 0;
}
