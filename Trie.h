#ifndef TRIE_H
#define TRIE_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include "Node.h"

using namespace std;


class Trie {
public:
    Trie();
    ~Trie();
    void addWord(string s);
    bool searchWord(string s);
    void deleteWord(string s);
    void findRadOccurances(string rad);
private:
    void printAllPossibleChildren(Node* node, string s);
    Node* root;
};


#endif