#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

struct Node {
    int value;
    vector<Node*> next;
    
    Node(int val, int levels) {
        value = val;
        next.resize(levels, nullptr);
    }
};

class SkipList {
private:
    int maxLevels;
    Node* head;

public:
    SkipList(int maxLevels) {
        this->maxLevels = maxLevels;
        head = new Node(-1, maxLevels);
    }

    int randomLevel() {
        int level = 1;
        while ((rand() % 2 == 0) && level < maxLevels) {
            level++;
        }
        return level;
    }

    void insert(int value) {
        vector<Node*> update(maxLevels, nullptr);
        Node* curr = head;

        for (int i = maxLevels - 1; i >= 0; i--) {
            while (curr->next[i] != nullptr && curr->next[i]->value < value) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }

        int levels = randomLevel();
        Node* newNode = new Node(value, levels);

        for (int i = 0; i < levels; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }

    bool search(int value) {
        Node* curr = head;
        for (int i = maxLevels - 1; i >= 0; i--) {
            while (curr->next[i] != nullptr && curr->next[i]->value < value) {
                curr = curr->next[i];
            }
        }
        curr = curr->next[0];
        return curr != nullptr && curr->value == value;
    }

    void deleteNode(int value) {
        vector<Node*> update(maxLevels, nullptr);
        Node* curr = head;

        for (int i = maxLevels - 1; i >= 0; i--) {
            while (curr->next[i] != nullptr && curr->next[i]->value < value) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }

        curr = curr->next[0];

        if (curr == nullptr || curr->value != value) {
            cout << "Value not found!" << endl;
            return;
        }

        for (int i = 0; i < maxLevels; i++) {
            if (update[i]->next[i] != curr) break;
            update[i]->next[i] = curr->next[i];
        }

        delete curr;
        cout << "Deleted " << value << endl;
    }

    void print() {
        for (int i = maxLevels - 1; i >= 0; i--) {
            Node* curr = head->next[i];
            cout << "Level " << i << ": ";
            while (curr != nullptr) {
                cout << curr->value << " -> ";
                curr = curr->next[i];
            }
            cout << "nullptr" << endl;
        }
    }
};

int main() {
    SkipList sl(4);
    sl.insert(10);
    sl.insert(20);
    sl.insert(15);
    sl.print();
    cout << "Search 15: " << sl.search(15) << endl;
    cout << "Search 99: " << sl.search(99) << endl;
    sl.deleteNode(15);
    sl.print();
    sl.deleteNode(99);
    return 0;
}