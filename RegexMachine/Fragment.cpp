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

#include "Fragment.h"
using namespace std;

Fragment::Fragment()
{
  startState = nullptr;
  allStates = nullptr;
}

Fragment::Fragment(State* startState, State* currentState)
{
    this->allStates = new vector<State*>();
    allStates->push_back(currentState);
    this->startState = startState;
}

Fragment::Fragment(State* startState, vector<State*>* states)
{
    this->allStates = states;
    this->startState = startState;
}

State* Fragment::getStart()
{
    return this->startState;
}

vector<State*>* Fragment::getAllStates()
{
    return this->allStates;
}

