#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

struct LLNode {
    int val;
    LLNode* next;

    LLNode() {
        val = 0;
        next = nullptr;
    }
    LLNode(int value) {
        val = value;
        next = nullptr;
    }
};

class LinkedList {
public:

    int depth;
    LLNode* head;
    LLNode* tail;

    LinkedList() {
        depth = 0;
        head = nullptr;
        tail = nullptr;
    }

    void append(int value) {
        LLNode* newNode = new LLNode(value);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            tail = newNode;
        }
    }
};

struct Node {
    int data;
    Node* left;
    Node* right;

    Node() {
        data = 0;
        left = nullptr;
        right = nullptr;
    }

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class BinaryTree {
private:
    Node* root;
    LinkedList obj[20];

public:
    BinaryTree() : root(NULL)/*, depth(0), head(NULL), tail(NULL)*/ {}

    Node* insert(Node* subroot, int value) {
        if (subroot == nullptr) {
            Node* newNode = new Node(value);
            subroot = newNode;
            obj[0].append(value);
            /* head = tail = new LLNode(value);*/
            obj->depth++;
        }
        else {
            queue<Node*> q;
            q.push(subroot);

            while (!q.empty())
            {

                Node* frontNode = q.front();
                q.pop();

                if (frontNode->left == nullptr) {
                    frontNode->left = new Node(value);
                    break;
                }
                else {
                    q.push(frontNode->left);
                }

                if (frontNode->right == nullptr) {
                    frontNode->right = new Node(value);
                    break;
                }
                else {
                    q.push(frontNode->right);
                }
                obj->depth++;
            }
        }
        return subroot;
    }

    void insert(int val) {
        root = insert(root, val);
    }

    int createDepthLinkedLists(LinkedList*& linkedLists) {
        if (root == nullptr)
            return 0;

        queue<Node*> q;
        q.push(root);

        int level = 0;
        int maxDepth = -1;

        while (!q.empty()) {
            int levelSize = q.size();
            linkedLists[level] = LinkedList();

            for (int i = 0; i < levelSize; i++) {
                Node* currentNode = q.front();
                q.pop();

                linkedLists[level].append(currentNode->data);

                if (currentNode->left)
                    q.push(currentNode->left);
                if (currentNode->right)
                    q.push(currentNode->right);
            }

            level++;
            maxDepth++;
        }

        return maxDepth;
    }

    void display(Node*);
    void display();
    bool areTreesIdentical(Node*, Node*);
    bool isSubtree(Node*, Node*);
    bool isSubtree(BinaryTree&);

    bool findPathUtil(Node*, int, int, string&);
    bool findPath(int);
};

bool BinaryTree::areTreesIdentical(Node* root1, Node* root2) {
    if (root1 == nullptr && root2 == nullptr)
        return true;
    if (root1 == nullptr || root2 == nullptr)
        return false;

    return (root1->data == root2->data) &&
        areTreesIdentical(root1->left, root2->left) &&
        areTreesIdentical(root1->right, root2->right);
}

bool BinaryTree::isSubtree(Node* root1, Node* root2) {
    if (root1 == nullptr)
        return false;
    if (areTreesIdentical(root1, root2))
        return true;

    return isSubtree(root1->left, root2) || isSubtree(root1->right, root2);
}

bool BinaryTree::isSubtree(BinaryTree& other) {
    return isSubtree(root, other.root);
}

bool BinaryTree::findPath(int targetSum) {
    string path;
    return findPathUtil(root, targetSum, 0, path);
}

bool BinaryTree::findPathUtil(Node* root, int targetSum, int currentSum, string& path) {
    if (root == nullptr)
        return false;

    currentSum += root->data;
    path += to_string(root->data) + " ";

    if (currentSum == targetSum) {
        cout << "Path with sum " << targetSum << ": " << path << endl;
        return true;
    }

    bool foundInLeft = findPathUtil(root->left, targetSum, currentSum, path);
    bool foundInRight = findPathUtil(root->right, targetSum, currentSum, path);

    // Remove the current node from the path to backtrack
    path.erase(path.length() - to_string(root->data).length() - 1);

    return foundInLeft || foundInRight;
}


void BinaryTree::display(Node* root) {
    if (root == nullptr)
        return;
    display(root->left);
    cout << root->data << " ";
    display(root->right);
}

void BinaryTree::display() {
    cout << "Contents in the binary tree: " << endl;
    display(root);
    cout << endl;
}