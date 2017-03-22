/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Vasilen Polimenov
 * @idnumber 61888
 * @task 3
 * @compiler GCC
 */

#include "Trie.h"
//Special number to save prefix
const int ISPREFIX = -4419608;
Node* Node::findChild(char c)
{
    for ( int i = 0; i < children.size(); i++ )
    {
        Node* tmp = children.at(i);
        if ( tmp->get_content() == c )
        {
            return tmp;
        }
    }

    return NULL;
}

Trie::Trie()
{
    root = new Node();
}

Trie::~Trie()
{
    // Free memory
}

void Trie::addWord(string s, int wordValue)
{
    Node* current = root;

    if ( s.length() == 0 )
    {
        current->set_wordMarker(0); // an empty word
        return;
    }

    for ( int i = 0; i < s.length(); i++ )
    {
        Node* child = current->findChild(s[i]);
        if ( child != NULL )
        {
            current = child;
        }
        else
        {
            Node* tmp = new Node();
            tmp->set_content(s[i]);
            current->appendChild(tmp);
            current = tmp;
        }
        if ( i == s.length() - 1 )
            current->set_wordMarker(wordValue);
    }
}


int Trie::searchWord(string s)
{
    Node* current = root;

    while ( current != NULL )
    {
        for ( int i = 0; i < s.length(); i++ )
        {
            Node* tmp = current->findChild(s[i]);
            if ( tmp == NULL )
                return 0;
            current = tmp;
        }
        if ( current->get_wordMarker() )
            return current->get_wordMarker();
        else
            return ISPREFIX;


    }

    return 0;
}
