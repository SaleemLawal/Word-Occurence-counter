/*****************************************
** File:    Bar.cpp
** This file contains the functions that help with perfoming actions 
** from input received form a text file, acctions
**  such as (loading the file, removing common and single words words, sorting the data and exporting it)
**
***********************************************/

#include "Bar.h"
// Name: Bar (Default Constructor) (not used)
// Desc: Dynamically allocates m_data for strings (always). m_fileName defaults to test.txt
// Preconditions: Input file has correctly formatted input
// Postconditions: Returns list of items and their frequency (stored in LL)
Bar::Bar(){
    m_data = new LL<string>();
    m_fileName = "test.txt";
}

// Name: Bar (Overloaded Constructor)
// Desc: Used to pass an input file
//       Dynamically allocates m_data for strings (always)
//       Sets m_fileName and nothing done with m_dataSorted until SortData
// Preconditions: Input file
// Postconditions: m_data is allocated, m_fileName populated
Bar::Bar(string filename){
    m_fileName = filename;
    m_data = new LL<string>();
}

// Name: ~Bar (Destructor)
// Desc: Deallocates m_data
// Preconditions: m_data has been dynamically allocated
// Postconditions: m_data is empty
Bar::~Bar (){
    delete m_data;
}

// Name: Start
// Desc: Calls LoadFile, RemoveCommon, RemoveSingles, Sort, DisplayBars, and Export
//       During testing, may want to call Display
// Preconditions: None (filename is available)
// Postconditions: None
void Bar::Start(){
    LoadFile();
    RemoveCommon();
    RemoveSingles();
    SortData();
    DisplayBars();
    Export();
}

// Name: LoadFile()
// Desc: Loads a file (everything as a string although could be anything stringlike)
//       Calls RemovePunct as each item is loaded
//       Each input file is an unknown length
// Preconditions: m_fileName is populated with good data
// Postconditions: m_data is populated
void Bar::LoadFile(){
    int count = 0;
    ifstream file(m_fileName);
    //checks if file is open
    if (!file.is_open()){
        cout << "File is not opened" << endl;
    } else{
        string word;
        // keeps looping while there are words to read
        while (file >> word){
            RemovePunct(word);
            m_data->Insert(word);
            count++;
        }
    }
    file.close();
    cout << count << " loaded" << endl;
}

// Name: RemovePunct (passed a string)
// Desc: Converts all input into lowercase using tolower
//       When passed a string, removes all non letter punctation on the beginning
//       or end of the string.
//       These are all ok: "don't" "inner-circle" but "candy," is bad
//       Is called during LoadFile
//       You can use ispunct - https://www.geeksforgeeks.org/ispunct-function-c/
// Preconditions: Strings to be evaluated
// Postconditions: Punctuation is removed from string
void Bar::RemovePunct(string& word){
    int stringSize = word.size() - 1;
    int i  = 0;
    string newWord;
    // checks each character
    while(word[i]){
        // remove punctuation if it exist at either the first index or the last index
        if(!(ispunct(word[i]) and (i == 0 or i == stringSize))){
            newWord += word[i];
        }
        i++;
    }
    // converts word passed in to lowercase
    string lowerCaseWord;
    for(string::const_iterator it = newWord.begin(); it != newWord.end(); ++it){
      lowerCaseWord += tolower(*it);
    }
    word = lowerCaseWord;
}
// Name: RemoveCommon
// Desc: Asks user if they want to remove common words
//       If yes, iterates through m_data and removes all common words after they are read
// Preconditions: m_data is populated and EXCLUDE_LIST is populated
// Postconditions: m_data will have no words from EXCLUDE_LIST
void Bar::RemoveCommon(){
    string userInput;
    bool check = true;
    while (check){
        string upperCaseWord;
        cout << "Would you like to remove all common words (Only use with essays)?" << endl;
        cin >> userInput;
        // convert to upper case for comparison
        for (string::iterator it = userInput.begin(); it != userInput.end(); it++){
            upperCaseWord += toupper(*it);
        }
        userInput = upperCaseWord;
        if (userInput == "YES" or userInput == "Y") {
            check = false;
        } else if (userInput == "NO" or userInput == "N") {
            check = false;
        }
    }
    // if (userInput == "YES" or userInput == "Y" or userInput == "yes" or userInput == "y"){
    //     for(vector<string>:: const_iterator it = EXCLUDE_LIST.begin(); it != EXCLUDE_LIST.end(); ++it){
    //         m_data -> RemoveAt(*it);
    //     }
    //     cout << "All common words removed." << endl;
    // }
}
// Name: RemoveSingles
// Desc: Asks the user if they would like to remove words with a frequency of 1
//       Should use the overloaded [] NOTE: Don't forget m_data is a pointer!
// Preconditions: m_data is populated
// Postconditions: m_data will have no words with a frequency of 1
void Bar::RemoveSingles(){
    string userInput;
    int count = 0;
    bool check = true;
    while (check){
        string upperCaseWord;
        cout << "Would you like to remove all words with a frequency of 1?" << endl;
        cin >> userInput;
        // convert to upper case for comparison
        for (string::iterator it = userInput.begin(); it != userInput.end(); it++){
            upperCaseWord += toupper(*it);
        }
        // sets userInput to be the upperCase word
        userInput = upperCaseWord;
        if (userInput == "YES" or userInput == "Y") {
            check = false;
        } else if (userInput == "NO" or userInput == "N") {
            check = false;
        }
    }
    if (userInput == "YES" or userInput == "Y" or userInput == "yes" or userInput == "y"){
        int i = 0;
        // keep running while i is less than the LL size
        while(i < m_data -> GetSize()){
            int frequency = (*m_data)[i].second;
            if (frequency == 1){
                count++;
                m_data -> RemoveAt((*m_data)[i].first);
            } else {
                i++;
            }
        }
        cout << count << " words removed." << endl;
    }
}
// Name: SortData
// Desc: Iterates through each items in m_data and inserts into
//       m_dataSorted using the frequency as the key (can use make_pair)
// Preconditions: m_data is populated
// Postconditions: m_dataSorted is populated and sorted based on frequency
void Bar::SortData(){
    int i = 0;
    // insert item into the multi map vased on their frequency
    while(i < m_data -> GetSize()){
        m_dataSorted.insert(make_pair((*m_data)[i].second, (*m_data)[i].first));
        i++;
    }
}
// Name: DisplayBars
// Desc: Displays a bar chart for each item in m_dataSorted from highest
//       frequency (at the top) to lowest frequency (at the bottom) (iterate backwards)
// Preconditions:  m_dataSorted is populated
// Postconditions: Bar charts are displayed
void Bar::DisplayBars(){
    const int BARWIDTH = 15;
    // loops through the multi map and prints out the data
    for (multimap<int, string>::reverse_iterator rit = m_dataSorted.rbegin(); rit != m_dataSorted.rend(); ++rit){
        cout << setw(BARWIDTH) <<rit -> second << ": ";
        for (int i = 0; i < rit -> first; i++){
            cout << barChar;
        }
        cout << endl;
    }
}
// Name: Export
// Desc: Asks the user what name the export file should be called
//       Iterates through m_dataSorted and exports to file
// Preconditions: m_dataSorted is populated
// Postconditions: New export file is created and populated with a formatted bar chart
void Bar::Export(){
    const int BARWIDTH = 15;
    const int MIN = 3;
    bool fileValidation = true;
    string fileName;
    string requiredExtension = ".txt";
    string extensionCheck;

    while (fileValidation){
        cout << "What would you like to call the export file? " << endl;
        cin >> fileName;
        // checks if the file inputted has a size < 3, if it does, then it means an extension wasnt specified
        if (!(fileName.size() <= MIN)){
            // gets the last 3 letters if a file extension was provide
            extensionCheck = fileName.substr(fileName.length() - requiredExtension.length());
            if(extensionCheck == requiredExtension){
                fileValidation = false;
            }
            cout << "File needs a .txt extension" << endl;
        }else{
            cout << "File name must be greater than 3" << endl;
        }
    }

    // creates a file that will be populated with data that was outputed
    ofstream myfile(fileName);
    for (multimap<int, string>::reverse_iterator rit = m_dataSorted.rbegin(); rit != m_dataSorted.rend(); ++rit){
        myfile << setw(BARWIDTH) <<rit -> second << ":";
        for (int i = 0; i < rit -> first; i++){
            myfile << barChar;
        }
        myfile << endl;
    }

    myfile.close();
    cout << "Output to exportFile " << fileName << endl;
}