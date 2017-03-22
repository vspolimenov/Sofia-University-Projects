/**
 *
 * Solution to homework task
 * Data Structures Course
 * Faculty of Mathematics and Informatics of Sofia University
 * Winter semester 2016/2017
 *
 * @author Vasilen Polimenov
 * @idnumber 61888
 * @task 3
 * @compiler GCC
 *C:\Users\stan\Documents\HomeworkSDA2\main.cpp
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include<fstream>
#include "Trie.h"
using namespace std;
void CalculateResult(int argc, char * filename);
char mytolower(char in);
void ConstructDictionary(int argc, char * argv[]);
void ReadSentences(int argc, char * argv[]);
Trie* trie = new Trie();
//Special number to save prefix
const int ISPREFIX = -4419608;

int main(int argc, char * argv[])
{
   ConstructDictionary(argc, argv);
   ReadSentences(argc, argv);


    delete trie;
}

//Reading line by line and collecting words in a trie.
void ConstructDictionary(int argc, char * argv[])
{
     string word;
    int wordKey;
    string line;

ifstream myfile1(argv[1]);
 if (myfile1.is_open())
  {
    while ( getline (myfile1,line) )
    {
      for(int i = line.size(); i >-1 ;i--)
      {
          if(line[i] == ' ')
          {
              wordKey = atoi(const_cast<char*>((line.substr(i + 1)).c_str()));

              while(line[i] == ' ')
              {
                  i--;
              }
              word = line.substr(0,i + 1);
              break;
          }
      }

      trie->addWord(word,wordKey);
    }

    myfile1.close();
  }

 else
    {
      cout << "Unable to open file";
    }

}

//Read each file, one by one.
void ReadSentences(int argc, char * argv[])
{
for(int i = 2;i<argc;i++)
  {
   CalculateResult(argc, argv[i]);
  }
}

//Calculating result. Reading file char by char and constructing words.
void CalculateResult(int argc, char * filename)
{
string currentWord;
vector<string> potentialWords;
string temp;
int wordsCount = 0;
double result = 0;
char spaceSymbol;
int prefixCount = 0;
bool hasPrefix = false;
bool hasWord = false;
bool readyToCheck = false;
char currentSymbol;
string oldWord;
ifstream myfile1(filename);
if (myfile1.is_open())
{
myfile1.get(currentSymbol);
if((currentSymbol>'Z' || currentSymbol<'A') && (currentSymbol>'z' || currentSymbol<'a'))
        wordsCount--;

  while(myfile1.peek() != -1)
  {
      if(readyToCheck == false)
      {
          //If we have prefix or word we gets all potential word and add them one by one to currentWord.

          if(hasWord || hasPrefix)
          {
               string word;
              while((currentSymbol<='Z' && currentSymbol>='A') || (currentSymbol<='z' && currentSymbol>='a'))
             {
                 word.push_back(currentSymbol);

                if(myfile1.peek() == -1)
                {
                    break;
                }

                myfile1.get(currentSymbol);
             }

              potentialWords.push_back(word);
              currentWord.append(word);
          }

          //We haven't any word or prefix detected yet.

          else
          {
              while((currentSymbol<='Z' && currentSymbol>='A') || (currentSymbol<='z' && currentSymbol>='a'))
             {
                currentWord.push_back(currentSymbol);
                if(myfile1.peek() == -1)
                {
                    break;
                }

                myfile1.get(currentSymbol);
             }

          }
            //End of current word. We have reached space symbol(symbol different from literal.

          spaceSymbol = currentSymbol;//Gets first space symbol( asdasdsa(first spaceSymbol)  93242fsdfsdf.

           myfile1.get(currentSymbol);
           int intervals = 1;

           //Counting space symbols...

            while((currentSymbol>'Z' || currentSymbol<'A') && (currentSymbol>'z' || currentSymbol<'a'))
            {
                    intervals++;
                    if(myfile1.peek() == -1)
                    {
                        break;
                    }

                    myfile1.get(currentSymbol);
            }

        wordsCount++;//Now we have word and we can increase wordCount ( (dfasdasd)->first word is in currentWord 324324fdsfsdf r234324)

        transform(currentWord.begin(), currentWord.end(), currentWord.begin(), mytolower);

        //Check if we currentWord is prefix. If true we add ' ' to currentWord.

        if(trie->searchWord(currentWord) == ISPREFIX && (spaceSymbol ==' ' || spaceSymbol=='\t' || spaceSymbol == '\n') && intervals ==1 )
        {
            currentWord.push_back(' ');
           hasPrefix = true;
           prefixCount = 0;
        }

       /*
       Check if currentWord if recognized as word from out trie.
       If true we mark oldWord as current word and if spaceSymbol is interval we add ' ' to current word so that
       it can be read as prefix in case there is longer word starting with currentWord.
       */
       else  if( trie->searchWord(currentWord) != 0 && trie->searchWord(currentWord) != ISPREFIX )
        {
            oldWord = currentWord;
            if((spaceSymbol ==' ' || spaceSymbol=='\t' || spaceSymbol == '\n') && intervals == 1)
            {
                currentWord.push_back(' ');
                prefixCount = 0;
            }
             //Marks word. Next iteration the key of 'old word' will be added in result.
            else
            {
                currentWord.push_back('#');
                readyToCheck = true;
            }

            //Now we have prefix and word...

            hasPrefix = true;
            hasWord = true;
        }
           else if(trie->searchWord(currentWord) == ISPREFIX && hasPrefix)
           {
               hasPrefix = false;
           }
      }
           //Current word is not recognized as word or is prefix.
        if(trie->searchWord(currentWord) == 0 || (trie->searchWord(currentWord) == ISPREFIX && hasPrefix == false))

        {
            if(hasPrefix)
                {
                    //If we have word  and prefix we add old word to result.

                    if(hasWord)
                    {
                       result += trie->searchWord(oldWord);

                       //We try to add all potential word we have collected in searching currentWord...

                       for(int i =0;i<potentialWords.size();i++)
                       {
                       result += trie->searchWord(potentialWords.at(i));
                       }

                       potentialWords.empty();

                       //We don't have any word or prefix now.

                       hasWord = false;
                       readyToCheck = false;
                    }

            hasPrefix =false;
            }
            currentWord.clear();
        }
    }
}
    else
    {
        cout << "Unable to open file";

    }

cout<< filename<<" " << result / wordsCount <<endl;
}

char mytolower(char in)
{
  if(in<='Z' && in>='A')
    return in-('Z'-'z');
  return in;
}
