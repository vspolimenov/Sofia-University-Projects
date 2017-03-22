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

#include "NFAImplementation.h"

using namespace std;

NFAImplementation::NFAImplementation()
{
}

State* NFAImplementation::postfixToNFA(string postfix)
{
    stack<Fragment*> fragmentStack;
    Fragment* completeNFA = new Fragment();
    State* finalState = new State();

    for (int i = 0; i < postfix.size(); i++)
    {
        char symbol = postfix[i];

        if(isLiteral(symbol))
        {
            State* literalState = new State(symbol);
            Fragment* literalStateFragment = new Fragment(literalState, literalState);
            fragmentStack.push(literalStateFragment);
        }

        else if (isConcatenation(symbol))
        {

                if(fragmentStack.empty())
                    throw "Wrong regular expression!";
                Fragment* secondFragment = fragmentStack.top();
                fragmentStack.pop();

                 if(fragmentStack.empty())
                    throw "Wrong regular expression!";
                Fragment* firstFragment = fragmentStack.top();
                fragmentStack.pop();

                patchFragmentToAState(firstFragment, secondFragment->getStart());
                fragmentStack.push(new Fragment(firstFragment->getStart(), secondFragment->getAllStates()));

        }

        else if (isAlternation(symbol))
        {
              if(fragmentStack.empty())
                    throw "Wrong regular expression!";
                Fragment* secondFragment = fragmentStack.top();
                fragmentStack.pop();

                if(fragmentStack.empty())
                    throw "Wrong regular expression!";
                Fragment* firstFragment = fragmentStack.top();
                fragmentStack.pop();

                State* newState = new State(firstFragment->getStart(), secondFragment->getStart());

                fragmentStack.push(new Fragment(newState, appendStates(firstFragment->getAllStates(), secondFragment->getAllStates())));
        }

        else if (isKleene(symbol))
        {

                 if(fragmentStack.empty())
                        throw "Wrong regular expression!";
                Fragment* fragment = fragmentStack.top();
                fragmentStack.pop();

                State* newState = new State(fragment->getStart(), nullptr);
                patchFragmentToAState(fragment, newState);
                fragmentStack.push(new Fragment(newState, newState));
        }
    }

    completeNFA = fragmentStack.top();

    fragmentStack.pop();

    patchFragmentToAState(completeNFA, finalState);

    return completeNFA->getStart();
}

vector<State*>* NFAImplementation::appendStates(vector<State*>* firstState, vector<State*>* secondState)
{
    vector<State*>* appended = new vector<State*>();
    for (int i = 0; i < firstState->size(); i++)
    {
        appended->push_back(firstState->at(i));
    }

    for (int i = 0; i < secondState->size(); i++)
    {
        appended->push_back(secondState->at(i));
    }

    return appended;
}

bool NFAImplementation::isLiteral(char symbol)
{
    bool isLiteral = isConcatenation(symbol) == false && isAlternation(symbol) == false && isKleene(symbol) == false;
    //cout << "here  i goo" << endl;
    return isLiteral;
}

bool NFAImplementation::isConcatenation(char symbol)
{
    bool isConcatenation = symbol == '.';
    return isConcatenation;
}

bool NFAImplementation::isAlternation(char symbol)
{
    bool isAlternation = symbol == '|';
    return isAlternation;
}



bool NFAImplementation::isKleene(char symbol)
{
    bool isKleene = symbol == '*';
    return isKleene;
}


void NFAImplementation::patchFragmentToAState(Fragment* currentFragment, State* currentState)
{
    vector<State*>* toBePatched = currentFragment->getAllStates();
    for (int i = 0; i < toBePatched->size(); i++)
    {
        State* openStates = toBePatched->at(i);
        openStates->patch(currentState);
    }
}
