/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Vasilen Polimenov
 * @idnumber 61888
 * @task 5
 * @compiler GCC
 *
 */

#include <iostream>
#include<unordered_map>
#include<unordered_set>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <math.h>
using namespace std;

unordered_map<long,int > readFileWithNumbers(string filename);
void findIntersections(unordered_map<long,int >* s, string filename);

int main()
{

    int n;
    cin >> n;
    string* filenames = new string[n];
    for(int i = 0; i < n; i++)
    {
        cin >> filenames[i];
    }

    unordered_map<long,int > firstFileNumbers = readFileWithNumbers(filenames[0]);
    for(int i = 1 ; i < n; i++ )
    {
       findIntersections(&firstFileNumbers, filenames[i]);
    }

    ofstream myFile ("result.bin", ios::out | ios::binary);
    for (auto itr = firstFileNumbers.begin(); itr != firstFileNumbers.end(); ++itr)
      {
          if( itr->second == n - 1)
          {
                  std::ostringstream oss;
                  oss << itr->first;
                  myFile.write (oss.str().c_str(), 64);
          }

      }
}

unordered_map<long, int > readFileWithNumbers(string filename)
{
    unordered_map<long, int > m;

    ifstream is;
    is.open (filename, ios::binary );
    is.seekg(0, ios::end);
    int size=(int) is.tellg();
    is.seekg (0, ios::beg);
    char* buffer;
    while(is.tellg() < size)
    {
        int length = 64;
        buffer = new char [length];
        is.read (buffer,length);
        auto  got = m.find(atol(buffer));
      if(got == m.end())
      {
        m.insert(make_pair(atol(buffer), 0));
      }

    }

    is.close();
    return m;
}

void findIntersections(unordered_map<long,int >* s, string filename)
{
unordered_set<long> numbersAllreadyInfile;
 ifstream is;
    is.open (filename, ios::binary );
    is.seekg(0, ios::end);
    int size=(int) is.tellg();
    is.seekg (0, ios::beg);
    char* buffer;
    while(is.tellg() < size)
    {
        int length = 64;
        buffer = new char [length];
        is.read (buffer,length);
        auto  got = s->find(atol(buffer));
        if(got != s->end() && numbersAllreadyInfile.find(atol(buffer)) == numbersAllreadyInfile.end())
        {
          got->second++;
          numbersAllreadyInfile.insert(atol(buffer));
        }
    }

    is.close();
}
