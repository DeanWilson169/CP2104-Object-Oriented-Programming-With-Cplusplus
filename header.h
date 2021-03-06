#ifndef HEADER_H
#define HEADER_H
#endif

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstddef>
#include <algorithm>
#include <unordered_set>
using namespace std;

class Word {

//  •	Fields: 
//      o	word (string) The word in the dictionary
//      o	type
//      o	definition (string) 
//  •	Methods: 
//      o	Getters for word, definition and type
//      o	printDefinition – print the word’s definition to the console in accordance with the requirement for basic task 1.

    private:
    // Private Variable Declarations
    string word;
    string definition;
    string type;
    // Private Method Declarations
    //string establishWordType();
    vector<string> splitDefinitions();
    string establishType();
    void isNoun(string& output);
    void isVerb(string& output);
    void isAdjective(string& output);
    void isAdverb(string& output);
    void isMisc(string& output);
    void isPrep(string& output);
    void isProperNoun(string& output);
    void isNounAndVerb(string& output);
    void typeError(string& output);
    void scrabbleWords();
    
    int checkLetters(string currentLetter, string characters, int scoreMultiplier);

    public:
    // Public Method Declarations
    string getWord(){ return word; }
    string getDefinition(){ return definition; }
    string getType(){ return type; }
    Word(string, string, string);
    Word();
    void printDefinition();
    string getDefinitionsAsListedString();
    int determineLetterScore();
};

class Dictionary {

//    •	maintains an appropriate STL container of Word objects 
//    •	loads the dictionary file into its array of Word objects 
//    •	Performs the tasks needed for this assignment.
//    •	provides the methods: 
//        o	loadDictionary() - (loads the dictionary file into its array of Word objects) 
//        o	Other appropriate methods so as to implement the tasks.
    private:
    // Private Variable Declarations
    Word word;
    vector<string> dictionaryContent;
    
    string dictionaryFile = "dictionary2020.txt";
    // Private Variable Declarations for Assignment 2
    //vector<string> scrambledWords;


    // Private Method Declarations
    bool canReadFile(ifstream& file);
    
    //Assignment 2

    vector<string> permute(string word, int left, int right);
    vector<string> fixVector(vector<string> scrambledWords);
    vector<string> filterUsedWords(vector<string> scrambledWords);
    vector<string> scrambleWords(string word, vector<string> scrambleWordsContainer);

    public:
     // Public Variable Declarations
    vector<Word> wordContainer;
    // Public Method Declarations
    Dictionary();
    void readFromFile();
    void loadDictionary();
    void searchDefinition();
    void findLargestWord();
    void logyWords();
    //Assignment 2
    void rhymingWords();    
    vector<string> convertWordToVector(string word);
    void getAnagrams();
    void highestScrabbleScoreFromLetters();
    vector<string> jumbleWord(string word);
};


class WriteToHTML{

private:
ofstream index;
Dictionary dictionary;
string const FOLDER_PREFIX = "html-files/";
string const ALPHABET = "abcdefghijklmnopqrstuvwxyz";
public:

WriteToHTML();
void writeAlphabetToFile();
string writeWord(Word word);
string createHTMLPages(char letter);
void setupIndexPage();
string writeIndexPage(string letter);
string addHTMLHeaderAndFooterToPage(string page);
string setupHTMLHeader();
string setupHTMLFooter();
};

class Menu{

    //
    //  This class handles all user interactions and prompts to the screen
    //

    private:
    // Private Method Declarations
    Dictionary dictionary;
    WriteToHTML writeToHTML;
    bool isValidSelection;
    void searchDefinitionSelected(string& input);
    void findLargestWordSelected(string& input);
    void logyWordsSelected(string& input);
    bool exitMainMenu(string& input);
    void invalidSelection();
    void determineMainMenuSelection();
    void displayMainMenu();
    //Assignment 2
    void rhymingWordsSelected(string& input);
    void getAnamgramsSelected(string& input);
    void highestScoreFromLettersSelected(string& input);
    void writeToHTMLSelected(string& input);
    public:
    // Public Method Declarations
    void selectMainMenuOption();
};

