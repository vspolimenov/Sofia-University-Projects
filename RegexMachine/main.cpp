#include <iostream>
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

#include "SearchManager.h"
#include "NFAImplementation.h"
#include "AutomatSimulator.h"
#include "PostfixGenerator.h"

using namespace std;

int main(int argc, char * argv[])
{
    try
    {
         SearchManager::searchInFiles(argv[1],argv[2]);
    }

    catch(const char* msg)
    {
        cout << msg <<endl;
    }

    return 0;
}
