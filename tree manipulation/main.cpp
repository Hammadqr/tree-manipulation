#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "binarytree.h"

using namespace std;

BinaryTree obj[3];
void readfile(string& filename) {

    ifstream file(filename);
    if (file.is_open()) {
        cout << "File loaded successfully" << endl;
        string line;
        int i = -1, value = 0; // value is the value read from the file
        while (getline(file, line)) {
            if (line.empty() || line[0] == ' ' || line[0] == '#')
                continue;
            if (line == ">>>>") {
                i++;
            }
            else {
                value = stoi(line);
                obj[i].insert(value);
            }
        }
    }
    else {
        cout << "Error reading file" << endl;
    }
    file.close();
}

int main() {
    string filename = "q2.txt";
    readfile(filename);

    const int maxDepth = 100; // Set an arbitrary maximum depth for the tree

    // Initialize an array to store linked lists at each depth
    LinkedList* linkedLists = new LinkedList[maxDepth];

    int count = 0;
    while (count < 3)
    {
        int depth = obj[count].createDepthLinkedLists(linkedLists);
        cout << "Depth of the tree " << count << " is " << depth << endl;
        for (int i = 0; i < depth; i++)
        {
            cout << "Linked List at depth " << i << ": ";
            LLNode* currNode = linkedLists[i].head;

            while (currNode != nullptr)
            {
                cout << currNode->val << " ";
                currNode = currNode->next;
            }
            cout << endl;
        }
        cout << endl;
        count++;
    }
    if (obj[0].isSubtree(obj[1])) {
        cout << "T2 is a subtree of T1." << endl;
    }
    else {
        cout << "T2 is not a subtree of T1." << endl;
    }

    int targetSum = 9;
    bool pathExists = obj[2].findPath(targetSum);

    if (!pathExists) {
        cout << "No path found with sum " << targetSum << endl;
    }

    // Clean up memory
    delete[] linkedLists;

    return 0;
}