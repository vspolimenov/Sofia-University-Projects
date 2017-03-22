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

#include "PostfixGenerator.h"
using namespace std;

PostfixGenerator::PostfixGenerator()
{
    //ctor
}

string PostfixGenerator::inputToPostfix(string _input)
{

        if(countOpenParanthesis(_input) != countCloseParanthesis(_input))
            throw "Wrong input!";

    string input = translateSpecialSymbols(_input);
    input = addConcatenations(input);
    stack<char> operatorStack;
    string outputString;
    for(int i = 0; i < input.size(); i++){
        char symbol = input[i];

        if(isOperator(symbol)){
            if(operatorStack.empty())
            {
                operatorStack.push(symbol);
            }

            else
            {
                char stackTop = operatorStack.top();

                if(isOperator(stackTop))
                {
                    int privilegeValue = getPrivilege(symbol, stackTop);
                    if (privilegeValue <= 0)
                    {
                            if(operatorStack.empty())
                                throw "Wrong regular expression!";
                            stackTop = operatorStack.top();
                            operatorStack.pop();
                            outputString += stackTop;

                    }
                }

                operatorStack.push(symbol);
            }
        }
        else if(isOpenParenthesis(symbol))
        {
            operatorStack.push(symbol);
        }

        else if(isCloseParenthesis(symbol))
        {
            char stackTop = operatorStack.top();
            operatorStack.pop();

            while(!isOpenParenthesis(stackTop))
            {
                outputString += stackTop;
                stackTop = operatorStack.top();
                operatorStack.pop();
            }
        }
        else
        {
            outputString += symbol;
        }
    }
    while(!operatorStack.empty())
    {
        outputString += operatorStack.top();
        operatorStack.pop();
    }

    return outputString;
}

string PostfixGenerator::translateSpecialSymbols(string input)
{
    for(int i = 0; i < input.size(); i++)
    {
        char symbol = input[i];
        if(symbol != '\\')
        continue;
        else
        {
            char next = input[i + 1];
            bool isSpecialCombination = next == 'a' || next == 'd' || next == 'e' || next == 's';
            if(isSpecialCombination)
            {
                string beforeSpecialCombination = input.substr(0,i);
                string afterSpecialCombination = input.substr(i+2,input.length());

                if(next == 's')
                {
                    input = beforeSpecialCombination + "(( )|(\t)|(\n))" + afterSpecialCombination;
                }

                else if(next == 'e')
                {
                   input = beforeSpecialCombination + '\0' +"*" +afterSpecialCombination ;

                }

                else if(next == 'a')
                {
                    input = beforeSpecialCombination +"(a|b|c|d|e|f|g|h|i|j|k|l|m|n|o|p|q|r|s|t|u|v|w|x|y|z)"  + afterSpecialCombination;
                }
                else if(next == 'd')
                {
                    input = beforeSpecialCombination +"(1|2|3|4|5|6|7|8|9|0)"  + afterSpecialCombination;
                }
                else{}
            }
        }
    }
    return input;
}

string PostfixGenerator::addConcatenations(string original)
{
    string withConcatenations;
    withConcatenations+= original[0];

    for(int i = 1; i < original.size(); i++)
    {
        char symbol = original[i];
        if(possibleConcatenation(withConcatenations))
        {
            if(isLiteral(symbol) || isOpenParenthesis(symbol))
            {
                withConcatenations+= '.';
            }
        }

        withConcatenations+= symbol;

    }

    return withConcatenations;
}


int PostfixGenerator::getPrivilege(char firstSymbol, char secondSymbol)
{
    if(isKleene(firstSymbol))
    {
        if(isKleene(secondSymbol))
            return 0;
        else
            return 1;
    }

    else if(isConcatenation(firstSymbol))
    {
        if(isKleene(secondSymbol))
            return -1;
        else if (secondSymbol == firstSymbol)
            return 0;
        else
            return 1;
    }

    else if(isAlternation(firstSymbol))
    {
        if(firstSymbol == secondSymbol)
            return 0;
        else return -1;
    }

    return -2;
}


bool PostfixGenerator::isLiteral(char symbol)
{
    bool isLiteral = isOperator(symbol) == false && isCloseParenthesis(symbol) == false &&
    isOpenParenthesis(symbol) == false;
    return isLiteral;
}

bool PostfixGenerator::isAlternation(char symbol)
{
    bool isAlternation = symbol == '|';
    return isAlternation;
}

bool PostfixGenerator::isConcatenation(char symbol)
{
    bool isConcatenation = symbol == '.';
    return isConcatenation;
}

bool PostfixGenerator::isKleene(char symbol)
{
    bool isKleene = symbol == '*';
    return isKleene;
}

bool PostfixGenerator::isOperator(char symbol)
{
    bool isOperator = symbol == '*' || symbol == '|' || symbol == '.';
    return isOperator;
}

bool PostfixGenerator::isCloseParenthesis(char symbol)
{
    bool isCloseParenthesis = symbol == ')';
    return isCloseParenthesis;
}

bool PostfixGenerator::isOpenParenthesis(char symbol)
{
    bool isOpenParenthesis = symbol == '(';
    return isOpenParenthesis;
}

bool PostfixGenerator::possibleConcatenation(string withConcatenations)
{
    bool isPossible = isLiteral(withConcatenations[withConcatenations.size() - 1])
            || isCloseParenthesis(withConcatenations[withConcatenations.size() - 1])
            || isKleene(withConcatenations[withConcatenations.size() - 1]);
    return isPossible;
}

int PostfixGenerator::countOpenParanthesis(string input)
{
    int counter = 0;
    for(int i = 0; i < input.size();i++)
    {
        if(isOpenParenthesis(input[i]))
            counter++;
    }
        return counter;
}

int PostfixGenerator::countCloseParanthesis(string input)
{
    int counter = 0;
    for(int i = 0; i < input.size();i++)
    {
        if(isCloseParenthesis(input[i]))
            counter++;
    }
        return counter;
}
