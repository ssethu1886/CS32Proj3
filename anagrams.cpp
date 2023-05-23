#include <iostream>
#include <fstream>
#include <istream>
#include <cstring>
#include <string>
using namespace std;

const int MAXRESULTS   = 20;    // Max matches that can be found
const int MAXDICTWORDS = 30000; // Max words that can be read in

//Puts each string in dictfile into the array dict. Returns the number of words
//read into dict.
int lexiconBuilder(istream &dictfile, string dict[]);

// helper function for lexiconBuilder
// takes in same parameters, beginning position of array, and max lines of file
// returns number of lines in file
int LoopReadFile(int i, int max, istream &dictfile, string dict[]);

//Puts all the possibilities of word which are found in dict into results. Returns
//the number of matched words found.
int theJumbler(string word, const string dict[], int size, string results[]);

// helper function for theJumbler
// takes in a word, find permutations,
// if any combinations are found in dict but not in results, adds word to results,
// updates idx to number of words in results
void printPermutations (string prefix, string rest, int nwords, const string dict[], string results[], int &idx);

// helper function for printPermutations and theJumbler
// finds the permutations of a string using recursion instead of for loop
void printPermutationsLoop (int i, int max, string prefix, string rest, int nwords, const string dict[], string results[], int &idx);

// helper function for Jumbler
// returns whether word is in the array passed in
bool searchString(int i, int max, const string dict[], string word);


//Displays size number of strings from results.
void divulgeSolutions(const string results[], int size);

// helper function for divulgeSolutions
void lpPrintResults(int i, int max, const string results[]);


int main()
{
    string results[MAXRESULTS];
    string dict[MAXDICTWORDS];
    ifstream dictfile;         // file containing the list of words
    int nwords;                // number of words read from dictionary
    string word;

    dictfile.open("words.txt");
    if (!dictfile) {
        cout << "File not found!" << endl;
        return (1);
    }

    nwords = lexiconBuilder(dictfile, dict);
    cout << nwords << endl;
    

    cout << "Please enter a string for an anagram: ";
    cin >> word;

    int numMatches = theJumbler(word, dict, nwords, results);
    if (!numMatches) {
        cout << "No matches found" << endl;
    }
    else {
        divulgeSolutions(results, numMatches);
    }

    return 0;
}

int lexiconBuilder(istream &dictfile, string dict[]) {
    return LoopReadFile(0, MAXDICTWORDS, dictfile, dict);
}


int LoopReadFile(int i, int max, istream &dictfile, string dict[]){
    string line;
    if (i >= max || !getline(dictfile, line)){
        return i;
    }
    dict[i] = line;
    return LoopReadFile(i+1, max, dictfile, dict);
}

int theJumbler(string word, const string dict[], int size, string results[]){
    int idx = 0;
    printPermutations("", word, size, dict, results, idx);
    return idx;
}

void printPermutations (string prefix, string rest, int nwords, const string dict[], string results[], int &idx) {
    if (rest == ""){
        if ((searchString(0, nwords, dict, prefix)) && !(searchString(0, idx, results,prefix)) && idx < MAXRESULTS) {
            results[idx] = prefix;
            idx++;
        }
    }
    else {
        printPermutationsLoop(0, rest.length(), prefix, rest, nwords, dict, results, idx);
    }
}


void printPermutationsLoop (int i, int max, string prefix, string rest, int nwords, const string dict[], string results[], int &idx){
    if (i>= max){
        return;
    }
    string first = prefix + rest[i];
    string last = rest.substr(0, i) + rest.substr(i+1);
    printPermutations(first, last, nwords, dict, results, idx);
    printPermutationsLoop(i+1, max, prefix, rest, nwords, dict, results, idx);
}

bool searchString(int i, int max, const string dict[], string word){
    if (i>= max){
        return false;
    }
    if (dict[i] == word) {
        return true;
    }
    return searchString(i+1, max, dict, word);
}

void lpPrintResults(int i, int max, const string results[]){
            if (i>= max){
                return;
            }
            cout << "Matching word " << results[i] << endl;
            lpPrintResults(i+1, max, results);
}

void divulgeSolutions(const string results[], int size){
    lpPrintResults(0, size, results);
}
