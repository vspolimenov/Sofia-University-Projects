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

#include "SearchManager.h"

SearchManager::SearchManager()
{
}

vector<string> SearchManager::allSubstrings;

void SearchManager::searchInFiles(char* input, char* _reg)
{
    allSubstrings.clear();
    string reg(_reg);
    fixString(&reg);

    vector<string> filenames = getFilenames(input);
    for(int i = 0; i < filenames.size();i++)
    {
    vector<string> fileLines = readFromFile(filenames[i]);
    for(int j = 0;j < fileLines.size();j++)
    {
        findAllSubstrings(fileLines[j]);
        allSubstrings.push_back("");
         for(int l = 0; l < allSubstrings.size();l++)
        {
            fixString(&allSubstrings[l]);

            State* startState = NFAImplementation::postfixToNFA(PostfixGenerator::inputToPostfix(reg));
            bool matches = AutomatSimulator::simulateNFA(startState,allSubstrings[l]);

            if(reg == "" || matches)
            {
                int counter = filenames[i].size() - 1;
                char symbol = filenames[i][counter];

                while(symbol != '\\' && counter != 0)
                {
                    symbol = filenames[i][--counter];
                }

                string shortName = filenames[i].substr(counter + 1);

                if(reg == "")
                {
                    cout << filenames[i] << ":" << j + 1 << ":" <<endl;
                    break;
                }

                else if(matches)
                {
                    cout << shortName << ":" << j + 1 << ":" << allSubstrings[l] <<endl;
                    break;
                }

            }
         }
        allSubstrings.clear();
    }
   }
}

vector<string> SearchManager::readFromFile(string filename)
{
    vector<string> fileLines;
    string line;
    ifstream myfile (filename);
    if(myfile.is_open())
    {
        while (getline(myfile,line))
        {
            fileLines.push_back(line);
        }
      myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
    return fileLines;
}
vector<string> SearchManager::getFilenames(char* input)
{
    vector<string> filenames;
    string filenameFromInput(input);
    if(filenameFromInput.length() > 3 && filenameFromInput.substr(filenameFromInput.size() - 3) == "txt")
    {
        int counter = filenameFromInput.size() - 1;
        char symbol = filenameFromInput[counter];
        while(symbol != '\\' && counter != 0)
        {
            symbol = filenameFromInput[--counter];
        }
        if(counter == 0)
        {
            filenames.push_back(filenameFromInput);
            return filenames;
        }

        filenames.push_back(filenameFromInput);
        return filenames;
    }

    directoryRecursion(input,filenames);
    return filenames;
}


void SearchManager::directoryRecursion(string dir, vector<string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL)
    {
        cout << "Wrong directory or file name!" << dir << endl;

    }

    while ((dirp = readdir(dp)) != NULL)
        {
            string p1 = ".";
            string p2 = "..";
            if(dirp->d_name != p1 && dirp->d_name!=p2)
            {
                DIR * dp2;
                string new_dir = dir + "\\" + dirp->d_name ;

                if(isTxt(dirp->d_name)) files.push_back(new_dir);
                else if((dp2 = opendir(new_dir.c_str())) != NULL)
                {
                    directoryRecursion(new_dir, files);
                }
            }
        }
    closedir(dp);
}

bool SearchManager::isTxt(string filename)
{
     if(filename.length() > 3)
        {
           if(filename.substr(filename.size() - 3) == "txt")
           return true;
        }
        return false;
}

void SearchManager::findAllSubstrings(string input)
{
	for(int i = 0; i < input.size(); i++)
    {
        for(int j = 1; j < input.size() - i + 1;j++)
        {
            allSubstrings.push_back(input.substr(i,j));
        }
    }
}

char SearchManager::toLower(char symbol)
{
  if(symbol<='Z' && symbol>='A')
    return symbol-('Z'-'z');
  return symbol;
}
bool SearchManager::isToLower(char symbol)
{
  if(symbol<='Z' && symbol>='A')
    return true;
  return false;
}

void SearchManager::fixString(string* input)
{
    for(int i = 0; i< input->size();i++)
    {   if(isToLower(input->at(i)))
        input->replace(i,1,1,toLower(input->at(i)));
    }
}
