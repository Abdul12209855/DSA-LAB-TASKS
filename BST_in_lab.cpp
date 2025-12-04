#include <iostream>
using namespace std;


class TimeCapsule {
public:
    int year;
    string eventName;
    TimeCapsule* left;
    TimeCapsule* right;

    TimeCapsule(int y, string name) {
        year = y;
        eventName = name;
        left = right = nullptr;
    }        
};


class TimeStreamBST {
public:
    TimeCapsule* root;

    TimeStreamBST() {
        root = nullptr;
    }

    
    void inject(int year, string name) {
        root = insert(root, year, name);
        cout << "System: Injecting " << year << "... Timeline stable." << endl;
    }

    TimeCapsule* insert(TimeCapsule* node, int year, string name) {
        if (node == nullptr) {
            return new TimeCapsule(year, name);
        }
        if (year < node->year) {
            node->left = insert(node->left, year, name);
        } else if (year > node->year) {
            node->right = insert(node->right, year, name);
        }
        
        return node;
    }

    
    void paradox(int year) {
        cout << "Alert: Paradox detected at " << year << "!" << endl;
        root = deleteNode(root, year);
        cout << "System: Year " << year << " removed. Timeline stabilized." << endl;
    }

    TimeCapsule* deleteNode(TimeCapsule* node, int year) {
        if (node == nullptr) return nullptr;

        if (year < node->year) node->left = deleteNode(node->left, year);
        else if (year > node->year) node->right = deleteNode(node->right, year);
        else {
            // Node found
            if (!node->left) {
                TimeCapsule* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                TimeCapsule* temp = node->left;
                delete node;
                return temp;
            } else {
                // Two children: replace with inorder successor
                TimeCapsule* succ = node->right;
                while (succ->left) succ = succ->left;
                node->year = succ->year;
                node->eventName = succ->eventName;
                node->right = deleteNode(node->right, succ->year);
            }
        }
        return node;
    }

    
    void search(int year) {
        cout << "Query: Searching for " << year << "..." << endl;
        TimeCapsule* result = searchNode(root, year);
        if (result) {
            cout << "Result: Event Found! [" << result->year << ": " << result->eventName << "]" << endl;
        } else {
            cout << "Result: Year " << year << " not found in current timeline." << endl;
        }
    }

    TimeCapsule* searchNode(TimeCapsule* node, int year) {
        if (!node) return nullptr;
        if (year == node->year) return node;
        else if (year < node->year) return searchNode(node->left, year);
        else return searchNode(node->right, year);
    }
    void report() {
        cout << "COMMAND: CHRONOLOGICAL REPORT" << endl;
        cout << "-------------------------------" << endl;
        inorder(root);
        cout << "-------------------------------" << endl;
    }

    void inorder(TimeCapsule* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->year << ": " << node->eventName << endl;
        inorder(node->right);
    }

    int calculateTimeSpan() {
        if (!root) return 0;
        int minYear = root->year;
        int maxYear = root->year;
        TimeCapsule* temp = root;

        
        while (temp->left) temp = temp->left;
        minYear = temp->year;

        temp = root;
        
        while (temp->right) temp = temp->right;
        maxYear = temp->year;

        return maxYear - minYear;
    }
};


int main() {
    TimeStreamBST timeline;

    
    timeline.inject(2050, "Mars Colony Established");
    timeline.inject(1969, "Moon Landing");
    timeline.inject(2100, "Warp Drive Invented");
    timeline.inject(2000, "Y2K Bug");

    timeline.search(1969);

    timeline.inject(1990, "World Wide Web");
    timeline.paradox(2000);

    timeline.report();
    timeline.search(2000);

    cout << "Time Span of Timeline: " << timeline.calculateTimeSpan() << " years" << endl;

    return 0;
}
