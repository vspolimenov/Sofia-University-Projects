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

#ifndef FRAGMENT_H
#define FRAGMENT_H
#include <vector>
#include "State.h"
using namespace std;

/*
 Fragment object  is used in the creation of an NFA.
 Fragments are partial NFA. We create NFA using algorithm who patch them together.
 The Fragment has startState of the partial NFA and vector of states who collects all states linked in the fragment.
*/

class Fragment
{
    public:
        Fragment();
        Fragment(State*, State*);
        Fragment(State*, vector<State*>*);
        State* getStart();
        vector<State*>* getAllStates();


    private:
        State* startState;
        vector<State*>* allStates;

};

#endif // FRAGMENT_H
