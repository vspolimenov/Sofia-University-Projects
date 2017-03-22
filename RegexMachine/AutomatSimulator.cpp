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

#include "AutomatSimulator.h"
using namespace std;

AutomatSimulator::AutomatSimulator()
{
}

bool AutomatSimulator::simulateNFA(State* startState, string input)
{
     //Vector that contains possible states.
    vector<State> currentStatesVector;

    // Temp vector used t help collecting current possible states.
    vector<State> newStatesVector;

    int currentStep = 0;
    addState(currentStatesVector, startState, currentStep);

    for (int i = 0; i < input.size(); i++) {
        char symbol = input[i];
        currentStep = step(currentStatesVector, symbol, newStatesVector, currentStep);
        currentStatesVector = newStatesVector;
        newStatesVector = vector<State>();
    }

    return containsFinalState(currentStatesVector);
}

/*
 This method check if there is any final state in last step.(Is the input recognized.
*/
bool AutomatSimulator::containsFinalState(vector<State> finalStatesVector)
{
    for (int i = 0; i < finalStatesVector.size(); i++) {
        State state = finalStatesVector[i];

        if (state.isFinal())
        {
            return true;
        }
    }
    return false;
}

/*
 This method simulate the step of the NFA.
 It checks if the current symbol form input text is from all possible states (search literal type state) in currentStatesVector .
 If it is recognized from NFA. The state is saved in currentStatesVector.
 Number of step is increased.
*/
int AutomatSimulator::step(vector<State> currentStatesVector, char symbol, vector<State>& newStatesVector, int currentStep)
{
    currentStep++;

    for (int i = 0; i < currentStatesVector.size(); i++){
        State s = currentStatesVector[i];
        if(symbol == s.getCharLabel())
        {
            addState(newStatesVector, s.getFirstTransitionState(), currentStep);
        }
    }
    return currentStep;
}
/*
 This method adds all possible states in current step. In this way we can check all possible states in one step.
 See step method.
*/
void AutomatSimulator::addState(vector<State>& currentStatesVector, State* state, int currentStep)
{
    if (state == nullptr || state->getLastlist() == currentStep)
    {
        return;
    }

    state->setLastlist(currentStep);
    if (state->isSplit())
    {
        addState(currentStatesVector, state->getFirstTransitionState(), currentStep);
        addState(currentStatesVector, state->getSecondTransitionState(), currentStep);
        return;
    }

    currentStatesVector.push_back(*state);
}
