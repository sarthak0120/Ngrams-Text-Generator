// This program produces random text in the writing style of the input file!
// It uses N-grams to map sets of words to their probable successors and repeats
// the process as many times as the user wants.

#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "vector.h"
#include "map.h"
#include "filelib.h"
#include <sstream>
#include "simpio.h"
#include "strlib.h"
using namespace std;
int isInteger(string);
int main() {

    cout<<"Welcome to CS 106B Random Writer ('N-Grams').\n";
    cout<<"This program makes random text based on a document.\n";
    cout<<"Give me an input file and an 'N' value for groups\n";
    cout<<"of words, and I'll create random text for you.\n\n";

    //Taking a file.
    string filename = getLine("Input file name? ");
    do{

        if(!fileExists(filename)){

            filename = getLine("Unable to open that file. Try again.");
        }
    } while(!fileExists(filename));

    //Taking N.
    string N;
    N = getLine("Value of N? ");
    do{

        if (!isInteger(N) || (isInteger(N) && stringToInteger(N)<2)){

            if (!isInteger(N)){
                N = getLine("Illegal integer format. Try again.\nValue of N? ");
            }
            else{

                N = getLine("N must be 2 or greater.\nValue of N? ");
            }
        }

    } while (!isInteger(N) || (isInteger(N) && stringToInteger(N)<2));
    int n = stringToInteger(N);

    //Taking X.
    string X;
    X = getLine("# of random words to generate (0 to quit)? ");
    do{

        if (!isInteger(X) || (isInteger(X) && stringToInteger(X)<n)){

            if (!isInteger(X)){
                X = getLine("Illegal integer format. Try again.\n# of random words to generate (0 to quit)? ");
            }
            else{
                if(stringToInteger(X)==0){
                    cout<<"Exiting.";
                    break;
                }
                X= getLine("Must be at least n words.\n\n# of random words to generate (0 to quit)? ");
            }

        }

    } while (!isInteger(X) || (isInteger(X) && stringToInteger(X)<n));

    int x = stringToInteger(X);

    //If user does not want to quit.
    if(x!=0){

        ifstream fil;
        fil.open(filename);

        //Counting number of words in file.
        string w, line;
        long int wordCount=0;

        while(!fil.eof()){
            wordCount++;
            fil>>w;
        }
        fil.seekg(0, ios::beg);

        map<vector<string>, vector<string>> m;
        string word;

        vector<string> s, fileWords, fileWordsCopy;
        int total=0;

        //Storing N-1 beginning file words to wrap around.
        for (int i=0; i<n-1; i++){
            fil>>word;
            fileWords.insert(fileWords.end(), word);
        }
        fileWordsCopy = fileWords;
        fil.seekg(0, ios::beg);

        //Creating Map m.
        while(!fil.eof()){

            fil>>word;
            total+=word.length();
            fil.seekg(-(word.length()), ios::cur);

            for(int i=0; i<n-1; i++){
                if(!fil.eof()){
                    fil>>word;
                    s.insert(s.end(), word);
                } else{
                    s.insert(s.end(), fileWords[0]);
                    fileWords.erase(fileWords.begin());
                }
            }
            fileWords = fileWordsCopy;
            if(!fil.eof()){
                fil>>word;
                m[s].insert(m[s].end(), word);
            } else{
                m[s].insert(m[s].end(), fileWords[0]);
            }
            s.clear();
            fil.seekg(total); // -------I debugged my program and it doesn't run this statement (leading to an infinite loop).-------------------

        }
        fil.seekg(0, ios::beg);

        //Taking random integer.
        long int randomInt = (rand() % (wordCount+1));
        //Seeking to the above random position.
        for(long int i=1; i<=randomInt; i++){
            fil>>word;
        }
        //Taking in N-1 words from the file into s.
        for(int i=0; i<n-1; i++){
            if(!fil.eof()){
                fil>>word;
                s.insert(s.end(), word);
            } else{
                s.insert(s.end(), fileWords[0]);
                fileWords.erase(fileWords.begin());
            }
        }
        fil.close();

        //Printing the result.
        cout<<"...";
        for(int i=0; i<s.size(); i++){
            cout<<s[i]<<" ";
        }
        for(int i=0; i<x-2; i++){
            int r = rand()%(m[s].size());
            cout<<m[s])[r];
            s.erase(s.begin());
            s.insert(s.end(), m[s][r]);
        }
        cout<<"...";
    }
    return 0;
}

int isInteger(string s){
    int flag=1;
    for (int i=0; i<s.length(); i++){
        if(s[i]<48 || s[i]>57){
            flag=0;
            break;
        }
    }
    if(flag==0){
        return 0;
    }
    return 1;
}
