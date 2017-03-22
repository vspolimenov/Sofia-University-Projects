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

#include "State.h"

State::State()
{
    this->hasChar = false;
    this->split = false;
    this->_isFinal = true;
    this->firstTransitionState = nullptr;
    this->secondTransitionState = nullptr;
    this->lastList = -1;
}

State::State(char charLabel)
{
    this->charLabel = charLabel;
    this->hasChar = true;
    this->split = false;
    this->_isFinal = false;
    this->firstTransitionState = nullptr;
    this->secondTransitionState = nullptr;
    this->lastList = -1;
}

State::State(State* firstTransitionState, State* secondTransitionState)
{
    this->hasChar = false;
    this->split = true;
    this->_isFinal = false;
    this->firstTransitionState = firstTransitionState;
    this->secondTransitionState = secondTransitionState;
    this->lastList = -1;
}

int State::getLastlist()
{
    return this->lastList;
}

void State::setLastlist(int index)
{
    this->lastList = index;
}

bool State::isLiteralState()
{
    return this->hasChar;
}

char State::getCharLabel()
{
    return this->charLabel;
}

bool State::isSplit()
{
    return this->split;
}

bool State::isFinal()
{
    return this->_isFinal;
}

State* State::getFirstTransitionState()
{
    return this->firstTransitionState;
}

State* State::getSecondTransitionState()
{
    return this->secondTransitionState;
}

void State::patch(State* state)
{
    if (firstTransitionState == nullptr)
    {
        firstTransitionState = state;
    }

    if (secondTransitionState == nullptr && split)
    {
         secondTransitionState = state;
    }
}



