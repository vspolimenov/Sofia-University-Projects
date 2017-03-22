/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Vasilen Polimenov
 * @idnumber 61888
 * @task 2
 * @compiler GCC
 *C:\Users\stan\Documents\HomeworkSDA2\main.cpp
 */
#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <vector>
using namespace std;
class Node
{

public:

    Node()
    {
      content = ' '; wordMarker = false;
    }

    ~Node(){}

    char get_content()
    {
      return content;
    }

    void set_content(char c)
     {
        content = c;
     }

    int get_wordMarker()
    {
        return wordMarker;
    }

    void set_wordMarker(int wordValue)
    {
        wordMarker = wordValue;
    }

    Node* findChild(char c);
    void appendChild(Node* child)
    {
        children.push_back(child);
    }

    vector<Node*> get_children()
     {
         return children;
     }
private:
    char content;
    int wordMarker = 0;
    vector<Node*> children;
};

class Trie
{

public:
    Trie();
    ~Trie();
    void addWord(string s,int wordValue);
    int searchWord(string s);
    void deleteWord(string s);
private:
    Node* root;
};

#endif // TRIE_H
