/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Vasilen Polimenov
 * @idnumber 61888
 * @task 0
 * @compiler GCC
 *
 */

#ifndef SEARCHMANAGER_H
#define SEARCHMANAGER_H
#include<string>
#include<vector>
#include <dirent.h>
#include <fstream>
#include <stdio.h>
#include "./NFAImplementation.h"
#include "./AutomatSimulator.h"
#include "./PostfixGenerator.h"

/*
Simple class that helps us to open text files, read the information from them and search by regular expression.
*/

using namespace std;
class SearchManager
{
    public:

      static void searchInFiles(char*, char*);

    private:

        static vector<string> allSubstrings;
        SearchManager();
        static bool isTxt(string);
        static void directoryRecursion(string, vector<string> &);
        static vector<string> readFromFile(string);
        static vector<string> getFilenames(char* );
        static void findAllSubstrings(string );
        static void fixString(string*);
        static bool isToLower(char);
        static char toLower(char);
};

#endif // SEARCHMANAGER_H
