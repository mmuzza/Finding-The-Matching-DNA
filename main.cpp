/*
Program 1: DNA Profiling
Course: CS 251
System: Mac using Replit
Author: Muhammad Muzzammil
---------------------------------------------
*/

#include <algorithm> // For find(), which searches within a vector
#include <cassert>   // For the assert statement
#include <cctype>    // Allows using the tolower() function
#include <cstring>   // For C string function strcpy
#include <fstream>   // For file input and output
#include <iostream>  // For Input and Output
#include <map>
#include <sstream> // For reading in CSV file and splitting by commas
#include <vector>  // For vectors
using namespace std;
#include "ourvector.h"


// struct to save the names and strand counts from the database file accordingly
struct subject {
  ourvector<int> strCount;
  string name;
};


// Reads the DNA files 1.txt-20.txt
ourvector<char> loadDna(string dnaFile) {

  ourvector<char> str;
  str.clear();

  ifstream inStream;
  inStream.open(dnaFile); 

  if (inStream.is_open()) {

    string line, word;
    int rowIndex = -1;

    while (getline(inStream, line)) {

      rowIndex++;

      stringstream s(line);

      while (getline(s, word,
                     ',')) {
        for (int j = 0; j < word.size();
             j++) { 
          str.push_back(word[j]);
        }
      }
    }
  } else {
    cout << "Error: unable to open '" << dnaFile << "'" << endl;
  }

  return (str);
}

// displays the command for DNA files
void displayDna(ourvector<char> str) {
  cout << "\nDNA loaded:\n";
  for (int i = 0; i < str.size(); i++) {
    cout << str[i];
  }
  cout << endl;
}

// Displays the command database
void displayData(ourvector<subject> subjects) {
  cout << "Database loaded:" << endl;
  for (int i = 0; i < subjects.size(); i++) {
    cout << subjects[i].name << " ";
    for (int j = 0; j < subjects[i].strCount.size(); j++) {
      cout << subjects[i].strCount[j] << " ";
    }
    cout << endl;
  }
}

// Reads small.txt and large.txt files and stores the names and their str counts into struct
void loadDb(string fileName, ourvector<ourvector<char>> *str,
            ourvector<subject> *subjects) {
  ifstream inStream;
  inStream.open(fileName);

  if (inStream.is_open()) {
    string line, temporary, word;
    int rowIndex = -1;

    while (getline(inStream, line)) {

      rowIndex++;

      stringstream s(line);

      if (rowIndex == 0) {
        while (getline(s, word, ',')) {
          ourvector<char> temp;
          if (word != "name") {

            for (int j = 0; j < word.size(); j++) {
              temp.push_back(word[j]);
            }
            str->push_back(temp);
          }
        }
      } else {
        subject sp = {};
        int index = 0;
        while (
            getline(s, word,
                    ',')) { // read in columns of each line separated by comma
          if (index == 0) {
            sp.name = word;

          } else {
            sp.strCount.push_back(stoi(word));
          }
          index++;
        }
        subjects->push_back(sp);
      }
    }
  } else {
    cout << "Error: unable to open '" << fileName << "'" << endl;
  }
}

// Checks if the number of str counts matched anyone from the chosen Database file
string getMatchingDNA(ourvector<subject> subjects, ourvector<int> DNACount) {

  for (int i = 0; i < subjects.size(); i++) {
    bool isFound = true;
    for (int j = 0; j < DNACount.size(); j++) {
      if (DNACount[j] != subjects[i].strCount[j]) {
        isFound = false;
        break;
      }
    }
    if (isFound) {
      return (subjects[i].name);
    }
  }
  return ("");
}

// counts the number of consecutive strands for process command
ourvector<int> getDNACount(ourvector<ourvector<char>> str,
                           ourvector<char> dna) {

  ourvector<int> strcount;

  for (int i = 0; i < str.size(); i++) {
    int count = 0;
    int index = 0;
    int largestCount = 0;
    int lastMatchingIndex = -1;

    int strSize = str[i].size();

    while (index <= dna.size() - strSize) {
      int p = 0;
      int j = index;

      while (p < strSize) {
        if (dna[j] != str[i][p]) {
          break;
        }
        p++;
        j++;
      }
      if (p == strSize) {
        if (lastMatchingIndex == -1 || (lastMatchingIndex + strSize) != j) {
          count = 1;
        } else {
          count++;
        }
        lastMatchingIndex = j;
        if (count > largestCount) {
          largestCount = count;
        }
      }
      index++;
    }
    strcount.push_back(largestCount);
  }

  return strcount;
}

// display the process command
void displayProcessing(ourvector<ourvector<char>> str,
                       ourvector<int> strcount) {

  cout << "\nDNA processed, STR counts:" << endl;

  for (int i = 0; i < str.size(); i++) {
    for (int j = 0; j < str[i].size(); j++) {
      cout << str[i][j];
    }
    cout << ": " << strcount[i] << endl;
  }
  cout << endl;
}

// Displaying my creative component
void displayTotal(ourvector<ourvector<char>> str,
                       ourvector<int> strcount){
  cout << "\nTotal Number of STR found in the file:" << endl;

  for (int i = 0; i < str.size(); i++) {
    for (int j = 0; j < str[i].size(); j++) {
      cout << str[i][j];
    }
    cout << ": " << strcount[i] << endl;
  }
  cout << endl;
}

// Creative component 
// How to run it?
// The user will enter "total" to command this function. if they are interested 
// in finding out the total number of strands detected in the file and not just
// consecutive long strands like our process function.
ourvector<int> totalStrands(ourvector<ourvector<char>> str, ourvector<char> dna)
{
  ourvector<int> strcount;

  for (int i = 0; i < str.size(); i++) {
    int count = 0;
    int index = 0;
    int strSize = str[i].size();

    while (index <= dna.size() - strSize) {
      int p = 0;
      int j = index;

      while (p < strSize) {
        if (dna[j] != str[i][p]) {
          break;
        }
        p++;
        j++;
      }
      if (p == strSize) {
        count++;
      }
      index++;
    }
    strcount.push_back(count);
  }
  return(strcount);
}

// This function controls the whole menu for all commands.
void menu() {

  ourvector<char> dnaFile;
  ourvector<ourvector<char>> str;
  ourvector<subject> subjects;
  ourvector<int> dnaCounts;
  ourvector<string> userInput;
  
  string inputOfUser;
  string word;
  string quit;
  string dnaFileName = "";
  string command = "";

  cout << "Welcome to the DNA Profiling Application.\n";

  while (quit != "#") {

    cout << "Enter command or # to exit: ";

    getline(cin, inputOfUser);
    stringstream s(inputOfUser);
    while (getline(s, word, ' ')) {
      userInput.push_back(word);
    }

    command = userInput[0];

    // option 1 to load database ---> small.txt or large.txt
    if (command == "load_db") {
      subjects.clear();
      dnaCounts.clear();
      string file = userInput[1];
      cout << "Loading Database...\n";
      loadDb(file, &str, &subjects);
    }

    // option 2 of loading DNA file ----> 1.txt-20.txt
    if (command == "load_dna") {
      string file = userInput[1];
      cout << "Loading DNA...\n";
      dnaFile = loadDna(file);
    }

    // option 3 to find number of times str found
    if (command == "process") {
      if (str.size() == 0) {
        cout << "\nNo Database loaded.\n";
      } else if (dnaFile.size() == 0) {
        cout << "\nNo DNA loaded.\n";
      } else {
        cout << "Processing DNA...\n";
        dnaCounts = getDNACount(str, dnaFile);
      }
    }
    
    //option 4 will display anything that is loaded (database, dna, process) 
    if (command == "display") {
      if (str.size() == 0) {
        cout << "\nNo Database loaded.\n";
      } else {
        displayData(subjects);
      }
      if (dnaFile.size() == 0) {
        cout << "\nNo DNA loaded.\n";
      } else {
        displayDna(dnaFile);
      }
      if (dnaCounts.size() == 0) {
        cout << "\nNo DNA has been processed.\n";
      } else {
        displayProcessing(str, dnaCounts);
      }
    }

    // option 5 will check if someone matched the DNA in a given file
    if (command == "search") {
      string personMatched;
      if (str.size() == 0) {
        cout << "\nNo Database loaded.\n";
      } else if (dnaFile.size() == 0) {
        cout << "\nNo DNA loaded.\n";
      } else if (dnaCounts.size() == 0) {
        cout << "\nNo DNA processed.\n";
      } else {
        cout << "Searching database...\n";
        personMatched = getMatchingDNA(subjects, dnaCounts);
        if (personMatched != "") {
          cout << "Found in database!  DNA matches: " << personMatched << endl;
        } else {
          cout << "Not found in database." << endl;
        }
      }
    }

    // This calls my creative component function
    if(command == "total"){
      if (str.size() == 0) {
        cout << "\nNo Database loaded.\n";
      } 
      else if (dnaFile.size() == 0) {
        cout << "\nNo DNA loaded.\n";
      }
      else{
        displayTotal(str, totalStrands(str, dnaFile));
      }
    }

    // Last option to quit
    if (command == "#") {
      quit = "#";
    }

    userInput.clear();
  }
}

int main() {
  
    menu(); 
  
}