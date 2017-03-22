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

#ifndef AUTOMATSIMULATOR_H
#define AUTOMATSIMULATOR_H
#include "State.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;


// AutomatSimulator simulates the process of "checking" if the input text is recognized by the NFA.


class AutomatSimulator
{
    public:

        static bool simulateNFA(State*, string);

    private:

        AutomatSimulator();
        static bool containsFinalState(vector<State>);
        static int step(vector<State>, char, vector<State>&, int);
        static void addState(vector<State>&, State*, int);
};

#endif // AUTOMATSIMULATOR_H
