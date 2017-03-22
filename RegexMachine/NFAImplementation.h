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

#ifndef NFAIMPLEMENTATION_H
#define NFAIMPLEMENTATION_H
#include "State.h"
#include "Fragment.h"
#include<stack>
#include<iostream>
#include<vector>
#include<string>

// NFAImplementation is the class where we construct our NFA from regular postfix expression by patching fragments together.

using namespace std;
class NFAImplementation
{
    public:
         static State* postfixToNFA(string);
    private:
        NFAImplementation();
        static bool isLiteral(char);
        static bool isKleene(char);
        static bool isAlternation(char);
        static bool isConcatenation(char);
        static vector<State*>* appendStates(vector<State*>*, vector<State*>*);
        static void patchFragmentToAState(Fragment*, State*);
};

#endif // NFAIMPLEMENTATION_H
