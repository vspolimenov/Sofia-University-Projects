/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Vasilen Polimenov
 * @idnumber 61888
 * @task 4
 * @compiler GCC
 *
 */

#include <iostream>
#include<queue>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include "Tree.cpp"
using namespace std;

priority_queue<Node<int,string>, vector<Node<int,string> >, greater<Node<int,string> > > readFileWithNodes(char* filename);
void operationsMenu(char* argv);

int main(int argc, char * argv[])
{
    cout << 3/2;
    //operationsMenu(argv[1]);
    return 0;
}

void operationsMenu(char* filename)
{
    //We put data read from file in priority queue represented as Node and sorted by key.
    priority_queue<Node<int,string>, vector<Node<int,string> >, greater<Node<int,string> > > nodes =
    readFileWithNodes(filename);

    //Construct perfect balanced tree from data in queue.
    Tree<int, string> tree(nodes.size(), nodes);

    /* Choosing operation:
       add <key> <data>
       remove <key> <data>
       removeall <key>
       search <key> <data>
    */
    while(true)
    {
        string operation;
        cin >> operation;

        if(operation == "add")
            {
                int key = 0;
                cin >> key;

                string data;
                getline(cin, data);
                data = data.substr(1);

                tree.add(key, data);
            }

        else if (operation == "remove")
            {
                int key = 0;
                cin >> key;

                string data;
                getline(cin, data);
                data = data.substr(1);

                  if(tree.remove(key, data))
                  {
                    cout << "true" <<endl;
                  }

                 else
                    cout << "false" << endl;
            }

        else if (operation == "removeall")
            {
                int key = 0;
                cin >> key;
                cout << tree.removeall(key) <<endl;
            }

         else if (operation == "search")
            {
                int key = 0;
                cin >> key;

                string data;
                getline(cin, data);
                data = data.substr(1);

                if(tree.search(key, data))
                  {
                    cout << "true" << endl;
                  }

                 else
                    cout << "false" << endl;
            }

        else
            {
                cout << "Wrong command!";
                break;
            }
        }
    }

priority_queue<Node<int,string>, vector<Node<int,string> >, greater<Node<int,string> > > readFileWithNodes(char* filename)
{
    priority_queue<Node<int,string>, vector<Node<int,string> >, greater<Node<int,string> > > nodes;
    int length;
    char * buffer;

    ifstream is;
    is.open (filename, ios::binary );
    is.seekg(0, ios::end);
    int size=(int) is.tellg();
    is.seekg (0, ios::beg);

    while(is.tellg() < size)
    {
        length = 32;
        buffer = new char [length];
        is.read (buffer,length);
        Node<int,string> p1;
        p1.key = atoi(buffer);

        buffer = new char [length];
        is.read(buffer, length);

        length = atoi(buffer);
        buffer = new char [length];
        is.read(buffer, length);
        string data(buffer);
        p1.data = data;

        nodes.push(p1);
    }

    is.close();
    return nodes;
}
