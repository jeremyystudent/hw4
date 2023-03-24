#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.insert(std::make_pair('a',1));
    bt.insert(std::make_pair('b',2));
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');

    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }


    BinarySearchTree<int,int> ct;
    ct.insert(std::make_pair(1,-50));
    ct.insert(std::make_pair(2,8));
    ct.insert(std::make_pair(3,0));
    ct.insert(std::make_pair(10,0));
    ct.insert(std::make_pair(15,0));
    
    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<int,int>::iterator it = ct.begin(); it != ct.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(ct.find(-1) != ct.end()) {
        cout << "Found -1" << endl;
    }
    else {
        cout << "Did not find -1" << endl;
    }
    cout << "Erasing -1" << endl;
    ct.remove(-1);

    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<int,int>::iterator it = ct.begin(); it != ct.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }

    if(ct.find(2) != ct.end()) {
        cout << "Found 2" << endl;
    }
    else {
        cout << "Did not find 2" << endl;
    }
    cout << "Erasing 2" << endl;
    ct.remove(2);

    cout << "Binary Search Tree contents:" << endl;
    for(BinarySearchTree<int,int>::iterator it = ct.begin(); it != ct.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }


    // AVL Tree Tests
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.insert(std::make_pair('b',2));

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');

    return 0;
}
