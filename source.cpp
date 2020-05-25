#include "header.h"

int main(){
    Menu menu;
    menu.selectMainMenuOption();
    system("pause");
    return 0;
}

#pragma region WORD_CLASS_IMPLEMENTATION
/*
*
*   WORD CLASS DEFINITIONS
*
*/

// Word Class Contructor
Word::Word(string _word, string _definition, string _type){
    word = _word;
    definition = _definition;
    type = _type;
}

// Word Default Class Contructor
Word::Word(){};

// This function is huge and it probably wasnt necessary but it looks a lot nicer having the definitions in a list
// I'll try to explain whats happening, however I'm hoping most of the variable names are self explanatory
// I'm going to go a little overkill with the comments on this function since it wasnt a requirement
// The rest of the assignment is a little bit more reasonable, most of my comments are remnents of my psuedocode

// This function splits the definitions of the inputted word by the semicolons and puts each definition into a vector
vector<string> Word::splitDefinitions(){
    // I use this alot so I put it in a seperate variable that i can manage from here. it gets the full list of definitions
    string wordDefinition = getDefinition();
    // My vector variable that I will fill with definitions and return
    vector<string> wordDefinitionContainer;
    // More on these later
    size_t currentDefinitionEndPostition;
    size_t previousDefinitionEndPosition = 0;
    const int DEFINITION_POSITION_OFFSET = 2;
    // interior decorating :)
    cout << "Definitons: " << endl;
    // Here I am looping the full definition list by each character and storing the characters position as the index
    // I used this style of for loop later on in the assignment
    for(string::size_type i = 0; i < wordDefinition.length(); i++)
    {
        // Find every instance of a semi-colon in the definition
        // This definitions for all words except for the last one when ends in a "." now a ";"
        if(i < wordDefinition.length() - 1)
        {
            // Here i am storing the position of the character ";" in the wordDefiniton string
            // i am finding the first instance of a ";" from the character at position 'i'
            currentDefinitionEndPostition = wordDefinition.find(";", i);
        }
        else // So I fixed the "." issue here
        {
            // Same as with the ";"
            currentDefinitionEndPostition = wordDefinition.find(".", i);
        }
        // If there was a ";" at the current position in the loop
        if(currentDefinitionEndPostition != string::npos)
        {   
            // Here's some wizardry
            // since string.substr selects a string from a start position for a select amount of characters
            // I have a few variables to handle this, the names explain it
            size_t currentDefinitionLength = currentDefinitionEndPostition - previousDefinitionEndPosition;
            // Here I am splitting the definition into a seperate variable
            string currentDefinition = wordDefinition.substr(previousDefinitionEndPosition, currentDefinitionLength);
            // This is to stop the console from printing the definitions as many times as there are characters in the wordDefinition string
            if(previousDefinitionEndPosition != (currentDefinitionEndPostition + DEFINITION_POSITION_OFFSET))
            {
                // Add the current definition variable to the list
                wordDefinitionContainer.push_back(currentDefinition);
                // I'll explain the offset constant here. Since every definition ends with "; " which is 2 characters
                // I have added those characters onto the previous definition so each definition doesnt start with "; "
                previousDefinitionEndPosition = currentDefinitionEndPostition + DEFINITION_POSITION_OFFSET;
            }
        }
    }
    // return the vector so that I can add it to another variable when i call the function
    return wordDefinitionContainer;
}

void Word::printDefinition(){

    // Get the split up definitions and store it in another variable so i dont have to keep calling the function
    vector<string> splitDefinitionsContainer = splitDefinitions();
    // Print the words definition prefixed by its type
    cout << establishType() << endl;
    // Loop through the definitions so i can print them in a list
    for(int i = 0; i < splitDefinitionsContainer.size(); i++)
    {
        cout << i + 1 << ". " << splitDefinitionsContainer[i] << endl;
    }
}

#pragma region ESTABLISH_TYPE

// get the type code of each word and convert it to its full length name
string Word::establishType(){
    string output = ""; 
    isNoun(output);
    isVerb(output);
    isAdverb(output);
    isAdjective(output);
    isMisc(output);
    isPrep(output);
    isProperNoun(output);
    isNounAndVerb(output);
    typeError(output);
    return output;
}

// Check to see if the word is a Noun
void Word::isNoun(string& output){
    if(getType() == "n")
        output = "Noun (n.) ";
}

// Check to see if the word is a Verb
void Word::isVerb(string& output){
    if (getType() == "v"){
        output = "Verb (v.) ";
    }
}
// Check to see if the word is a Adverb
void Word::isAdverb(string& output){
    if (getType() == "adv")
        output = "Adverb (adv.) ";
}
// Check to see if the word is a Adjective
void Word::isAdjective(string& output){
    if (getType() ==  "adj")
        output = "Adjective (adj.) ";
}
// Check to see if the word is a Preposition
void Word::isPrep(string& output){
    if (getType() == "prep")
        output = "Preposition (prep.) ";
}
// Check to see if the word is a Misc word
void Word::isMisc(string& output){
    if (getType() == "misc")
        output = "MiscWords (misc.) ";
}
// Check to see if the word is a ProperNoun
void Word::isProperNoun(string& output){
    if (getType() == "pn")
        output = "ProperNouns (pn.) ";
}
// Check to see if the word is a Noun and Verb
void Word::isNounAndVerb(string& output){
    if (getType() == "n v")
        output = "NounAndVerb (n. v.) ";
}
// Check to see if the word failed to find a type
void Word::typeError(string& output){
    if(output == "")
        output = "(Unknown) ";
}
// Check to see if the word is a noun
#pragma endregion ESTABLISH_TYPE

#pragma endregion WORD_CLASS_IMPLEMENTATION

#pragma region DICTIONARY_CLASS_IMPLEMENTATION
/*
*
*   DICTIONARY CLASS DEFINITIONS
*
*/

// Dictionary Default Class Contructor
Dictionary::Dictionary(){};

bool Dictionary::canReadFile(ifstream& file)
{
    // Create an error if the file cannot be read
    if(!file)
    {
        cerr << "Cannot open the File : " << dictionaryFile << endl;
        return false;
    }
    return true;    
}

void Dictionary::readFromFile(){
    ifstream file (dictionaryFile.c_str());
    string input;
    bool isFileFound = canReadFile(file);
    // read the file
    if(isFileFound)
    {
        while(getline(file, input))
        {
            if(input.size() > 0)
            {
                // add the content from the file to a variable
                dictionaryContent.push_back(input);
            }
        }
        file.close();
    }
}

void Dictionary::loadDictionary(){
    //  Retrieve the content from readFromFile()
    readFromFile();
    //  loop through the vector extract all the content, assigning it to the word class instance
    int contentSize = dictionaryContent.size();
    // Constant variables to handle getting the values from the dictionary based on the line it is on
    // Every second line in the dictionary is a definition so add this to the index to get the definition
    const int DICTIONARY_DEFINITION_OFFSET = 1;
    // Every third line in the dictionary is a type so add this to the index to get the type
    const int DICTIONARY_TYPE_OFFSET = 2;
    // Each word has three lines of content: word, definition, and type. using this in the loop will allow us to loop each word
    const int DICTIONARY_CONTENT_OFFSET = 3;
    for(int i = 0; i < contentSize; i+=DICTIONARY_CONTENT_OFFSET){
        //  Create an instance of the word class
        Word word(dictionaryContent[i], dictionaryContent[i+DICTIONARY_DEFINITION_OFFSET], dictionaryContent[i+DICTIONARY_TYPE_OFFSET]);
        //  Fill a new Vector to all each word class instance.
        wordContainer.push_back(word);
    }
}

// TASK 1: Search the dictionary for a word inputted by the user and print the definiton to the console
void Dictionary::searchDefinition(){
    string input;
    // Ask the user to enter a word
    cout << "Enter a word you want a definition for..." << endl;
    // Recieve Input
    cin >> input;
    int wordContainerSize = wordContainer.size();
    // The last word in the dictionary
    const int LAST_WORD = wordContainerSize - 1;
    for(int i = 0; i < wordContainerSize; i++){
        if(input == wordContainer[i].getWord())
        {
            wordContainer[i].printDefinition();
            scrabbleWords(wordContainer[i].getWord());
            break;
        }
        else if(i == LAST_WORD && input != wordContainer[i].getWord())
        {
            cout << "word not found." << endl;
        }
    }
}

// Find the largest word in the dictionary and print it to the screen
void Dictionary::findLargestWord(){
    // Create a string to store the largest word
    Word largestWord;
    // Create a int to store the current largest words length
    int largestWordsLength  = 0;
    // loop through the word list checking the length of each word
    int wordContainerSize = wordContainer.size();
    for(string::size_type i = 0; i < wordContainerSize; i++)
    {
        // store the length of the largest word in the int if it is greater then the previous length
        if(wordContainer[i].getWord().size() > largestWordsLength)
        {
            largestWordsLength = i;
            // store the largest word in the string
            largestWord = wordContainer[i];
        }
    }
    // print the largest word to the console
    cout << largestWord.getWord() << endl;
    largestWord.printDefinition();
}

void Dictionary::logyWords(){
    // I have created a seperate variable for this so that the loop isnt contantly running the .size() function
    int wordContainerSize = wordContainer.size();
    const int MIN_LOGY_WORD_SIZE = 4;
    const int MAX_LOGY_WORD_SIZE = 7;
    const int LAST_WORD = wordContainerSize - 1;
    // loop through the Dictionary
    for(int i = 0; 0 < wordContainerSize; i++)
    {
        // create an instance variable of the current word for clarity
        string wordInstance = wordContainer[i].getWord();
        // check to see if the current word is less then 7 characters and greater then 4 (because 'logy' is 4 characters)
        if(wordInstance.length() >= MIN_LOGY_WORD_SIZE  && wordInstance.length() <= MAX_LOGY_WORD_SIZE)
        {
            // find cases of which a word contains the 'logy' substring
            size_t logyInstance = wordInstance.find("logy", 0);
            // if the word contained the substring print it to the console
            if(logyInstance != string::npos){
                cout << wordInstance << endl;
            }
            else if (wordInstance == wordContainer[LAST_WORD].getWord())
            {
                break;
            }
        }
    }
}

///
/// ASSIGNMENT 2 DICTIONARY DEFINITIONS
///

void Dictionary::rhymingWords(){

    string input;
    cout << "Enter a word to find rhyming words" << endl;
    cin >> input;
    int wordContainerSize = wordContainer.size();
    const int LAST_THREE_CHARACTERS = 3;
    const int MIN_WORD_SIZE = 2;
    //get the substring of the last three letters of the current word
    string lastThreeCharactersFromInput = (input.length() > MIN_WORD_SIZE) ? input.substr(input.length() - LAST_THREE_CHARACTERS, LAST_THREE_CHARACTERS) : "";
    //Loop through the Dictionary to find other words that also end in that substring
    for(int i = 0; i < wordContainerSize; i++){
    string currentWord = wordContainer[i].getWord();
    string lastThreeCharactersFromCurrentWord  =  (currentWord.length() > MIN_WORD_SIZE) ? currentWord.substr(currentWord.length() - LAST_THREE_CHARACTERS, LAST_THREE_CHARACTERS)  : "";
    string wordThatRhymes = (lastThreeCharactersFromInput == lastThreeCharactersFromCurrentWord) ? currentWord : "";
    // Print each word to the console
    if(wordThatRhymes.length() > MIN_WORD_SIZE)
        cout << wordThatRhymes << endl;
    }
}

// Scrabble Words

void Dictionary::scrabbleWords(string word)
{   
    int score = 0;
    score += determineLetterScore(word);
    cout << score << endl;
}

int Dictionary::determineLetterScore(string word)
{
    int score = 0;

    for(int i = 0; i < word.length(); i++)
    {
        string character ("");
        character.push_back(word[i]);

        score += checkLetters(character, "aeilnorstu", 1);
        score += checkLetters(character, "dg", 2);
        score += checkLetters(character, "bcmp", 3);
        score += checkLetters(character, "fhwvy", 4);
        score += checkLetters(character, "k", 5);
        score += checkLetters(character, "jx", 8);
        score += checkLetters(character, "qz", 10);
    }

    return score;
}

int Dictionary::checkLetters(string currentLetter, string characters, int scoreMultiplier){

    std::size_t found = currentLetter.find_first_of(characters);
    if(found != string::npos)
    {
        return scoreMultiplier;
    }
    return 0;
}

void Dictionary::highestScrabbleScoreFromLetters(){
    // Ask user for input
    string letters;
    cout << "Enter a string of letters to find the highest scoring word" << endl;
    cin >> letters;
    // Create a vector for the different permutations of the users input
    vector<string> scrambledLettersContainer;
    scrambledLettersContainer = scrambleWords(letters, scrambledLettersContainer);
    int scrambledLettersSize = scrambledLettersContainer.size();
    // Create variables to keep track of the highest scoring word
    int highestScore = 0;
    int currentScore = 0;
    string highScoreWord = "";
    //Loop through the dictionary
    int wordContainerSize = wordContainer.size();
    for(int j = 0; j < wordContainerSize; j++){
        //loop through the permutations
        scrambledLettersSize = scrambledLettersContainer.size();
        for(int i = 0; i < scrambledLettersSize; i++){
            //Check to see if a the permutation matches a word in the dictionary
            if(scrambledLettersContainer[i] == wordContainer[j].getWord()){
                currentScore = determineLetterScore(wordContainer[j].getWord());
                if(currentScore >= highestScore){
                    highestScore = currentScore;
                    highScoreWord = wordContainer[j].getWord();
                }
                scrambledLettersContainer.erase(scrambledLettersContainer.begin(), scrambledLettersContainer.begin() + i);
                break;
            }

        }
    }
    if(highScoreWord.length() > 0)
    {
        cout << "Word: " << highScoreWord << endl;
        cout << "Scrabble Score: " << highestScore << endl;
    }
    else{
        cout << "Could not find any words with those letters" << endl;
    }
}

vector<string> Dictionary::scrambleWords(string word, vector<string> scrambleWordsContainer){
    
    //Give the container the word and shuffle the different permutations into the vector
    scrambleWordsContainer = permute(word, 0, word.length());
    
    //Remove the whitespaces from the each word in the vector
    scrambleWordsContainer = fixVector(scrambleWordsContainer);
    
    //Remove any duplicates that may reside within the vector after stripping the whitespace
    // Because "  d " and "d   " were two seperate values prior to stripping the whitespace
    scrambleWordsContainer = filterUsedWords(scrambleWordsContainer);

    return scrambleWordsContainer;
}

void Dictionary::getAnagrams(){
    string word;
    cout << "Enter a word to find anagrams" << endl;
    cin >> word;
    vector<string> scrambleWordsContainer;
    scrambleWordsContainer = scrambleWords(word, scrambleWordsContainer);
    int wordContainerSize = wordContainer.size();
    int scrambledWordSize = scrambleWordsContainer.size();

    int lastFoundWord;

    int dictionarySize = 0;


    while(dictionarySize < wordContainerSize)
    {
        //Loop through the Dictionary to find other words that also end in that substring
        for(int j = dictionarySize; j < wordContainerSize; j++){
            
            if(wordContainer[j].getWord().find_first_of(word) != string::npos)
            {
                
                scrambledWordSize = scrambleWordsContainer.size();
                for(int i = 0; i < scrambledWordSize; i++){
                    if(scrambleWordsContainer[i] == wordContainer[j].getWord()){
                        cout << wordContainer[j].getWord() << endl;
                        dictionarySize = j;
                        //Make the container shorter so it doesn't take so long to search through it over and over again
                        scrambleWordsContainer.erase(scrambleWordsContainer.begin(), scrambleWordsContainer.begin() + i);
                        //cout << scrambledWordSize << endl;
                        break;
                    }
                }
            }
            break;
        }
        dictionarySize += 1;
    }
}

vector<string> Dictionary::filterUsedWords(vector<string> scrambledWords){
    vector<string> usedWords;
    
    unordered_set<string> s;
    int scrambledWordSize = scrambledWords.size();
    
    for(int i = 0; i < scrambledWordSize; ++i) 
    {
        s.insert(scrambledWords[i]);
    }
    scrambledWords.assign(s.begin() , s.end());
    sort(scrambledWords.begin(), scrambledWords.end());

    // for(int i = 0; i < scrambledWordSize; ++i) 
    // {
    //     cout << scrambledWords[i] << endl;
    // }

    // for(int i = 0; i < scrambledWordSize; i++){
    //     bool found = false;
    //     unsigned usedWordSize = usedWords.size();
    //     for(int j = 0; j < usedWordSize; j++){
    //         if(scrambledWords[i] == usedWords[j])
    //         {
    //             found = true;
    //         }
    //     }
    //     if(found == false || usedWords.size() == 0){
            
    //         usedWords.push_back(scrambledWords[i]);
    //     }
    // }
    return scrambledWords;
}


////////// REFACTOR THIS METHOD //////////////
vector<string> Dictionary::fixVector(vector<string> scrambledWords)
{
    vector<string> noSpacesBruh;
    string const ALPHABET = "abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < scrambledWords.size(); i++){
        string letters = "";
        for (int j = 0; j < scrambledWords[i].length(); j++){
            string currentLetter = "";
            currentLetter.push_back(scrambledWords[i][j]);
            if(currentLetter.find_first_of(ALPHABET) != string::npos)
            {
                letters.push_back(scrambledWords[i][j]);
            }
        }
        noSpacesBruh.push_back(letters);
    }
    return noSpacesBruh;
}

vector<string> Dictionary::permute(string word, int left, int right){

    string a = word;

    vector<string> wordPermuations;
    
    if(left == right){
        wordPermuations.push_back(a);
        return wordPermuations;
    }
    else{
        for(int i = left; i <= right; i++)
        {

            //swap a character in the word with another
            swap(a[left], a[i]);


            //Recursively call function
            vector<string> b = permute(a, left+1, right);

            //Append the new vector to the old one
            wordPermuations.insert(end(wordPermuations), begin(b), end(b)); 

            //Swap the word back to not mutate it
            swap(a[left], a[i]);
        }
    }
    return wordPermuations;
}



#pragma endregion DICTIONARY_CLASS_IMPLEMENTATION

#pragma region MENU_CLASS_IMPLEMENTATION
/*
*
*   MENU CLASS DEFINITIONS
*
*/

void Menu::displayMainMenu(){
    cout << "Select an operation:" 
    << endl 
    << "[1] Search Definition" 
    << endl 
    << "[2] Find the largest Word" 
    << endl 
    << "[3] Find words containing the 'logy' substring that are less than 7 characters in length" 
    << endl
    << "[4] Find words that rhyme" 
    << endl
    << "[5] Find words that are anagrams" 
    << endl
    << "[6] Find the highest Scrabble score from a string of letters" 
    << endl
    << "[0] Exit" 
    << endl;
}

// Having this function be public allows me to have all the other functions private
// While also allowing me to keep int Main() simple
void Menu::selectMainMenuOption()
{
    dictionary.loadDictionary();
    determineMainMenuSelection();
}

// its really difficult to make a switch statement look small
void Menu::determineMainMenuSelection()
{
    string input;
    bool readDictionary = true;
    
    while(readDictionary)
    {
        cout << endl;
        displayMainMenu();
        // check which value the user inputted and return the correct function
        cin >> input;
        cout << endl;
        searchDefinitionSelected(input);
        findLargestWordSelected(input);
        logyWordsSelected(input);
        rhymingWordsSelected(input);
        getAnamgramsSelected(input);
        highestScoreFromLettersSelected(input);
        readDictionary = exitMainMenu(input);
        invalidSelection();
    }
}

// Check to see if the user selected Search Definitions
void Menu::searchDefinitionSelected(string& input){
    if(input == "1")
    {
        dictionary.searchDefinition();
        isValidSelection = true;
    }
}
// Check to see if the user selected Find The Largest Word
void Menu::findLargestWordSelected(string& input){
    if(input == "2")
    {
        dictionary.findLargestWord();
        isValidSelection = true;
    }
}
// Check to see if the user selected logy Words
void Menu::logyWordsSelected(string& input){
    if(input == "3")
    {
        dictionary.logyWords();
        isValidSelection = true;
    }
}
// Check to see if the user selected Rhyming Words
void Menu::rhymingWordsSelected(string& input){
    if(input == "4")
    {
        dictionary.rhymingWords();
        isValidSelection = true;
    }
}
// Check to see if the user selected Anagrams
void Menu::getAnamgramsSelected(string& input){
    if(input == "5")
    {
        dictionary.getAnagrams();
        isValidSelection = true;
    }
}

// Check to see if the user selected Highest Score from Letters
void Menu::highestScoreFromLettersSelected(string& input){
    if(input == "6")
    {
        dictionary.highestScrabbleScoreFromLetters();
        isValidSelection = true;
    }
}
// Check to see if the user selected Exit
bool Menu::exitMainMenu(string& input){
    if(input == "0")
    {
        return false;
        isValidSelection = true;
    }
    return true;
}

void Menu::invalidSelection(){
    // Check to see if the input was a valid selection 
    if(!isValidSelection)
        cout << "Please select a valid menu option." << endl;
}

#pragma endregion MENU_CLASS_IMPLEMENTATION
