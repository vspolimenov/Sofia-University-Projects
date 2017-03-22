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

#ifndef STATE_H
#define STATE_H

/*
States are the main blocks of the NFA. We have three types of states:
-LiteralState - holds a symbol
-SplitState - links to other states
-FinalState - has information if the text is recognized by the NFA
*/

class State
{
    public:
        State();
        State(char);
        State(State*, State*);

        bool isLiteralState();
        char getCharLabel();
        bool isFinal();
        bool isSplit();
        State* getFirstTransitionState();
        State* getSecondTransitionState();
        void patch(State*);
        int getLastlist();
        void setLastlist(int);


    private:
        char charLabel;
        State* firstTransitionState;
        State* secondTransitionState;
        bool split;
        bool _isFinal;
        bool hasChar;
        int lastList;
};

#endif // STATE_H
