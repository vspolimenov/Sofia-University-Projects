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

#ifndef POSTFIXGENERATOR_H
#define POSTFIXGENERATOR_H
#include<iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

class PostfixGenerator
{
    public:
      static string inputToPostfix(string);
      static string addConcatenations(string);
      static int getPrivilege(char, char);

    private:
        PostfixGenerator();
        static string translateSpecialSymbols(string);
        static bool possibleConcatenation(string);
        static bool isLiteral(char);
        static bool isAlternation(char);
        static bool isConcatenation(char);
        static bool isKleene(char);
        static bool isOperator(char);
        static bool isCloseParenthesis(char);
        static bool isOpenParenthesis(char);
        static int countCloseParanthesis(string );
        static int countOpenParanthesis(string );
};

#endif // POSTFIXGENERATOR_H
