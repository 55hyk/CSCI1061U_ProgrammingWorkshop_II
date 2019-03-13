#include <iostream>
#include <dirent.h> // directory entry
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/*
For this database version of search.cpp, I decided to use the search function in
part and ouput the infomation I need as this format into the database:
    &file name.txt
    $keyword-1*line_number#how_many_times_the_keyword_has_occured_in_one_line
  e.g.
    &Romeo and Juliet.txt
    $love*5#3*16#3
    $poison*66#1
    i.e. This means that in "Romeo and Juliet.txt", love was found at line 5 (3
         times) and at line 16 (3 times), and poison was found at line 66 (1
         time).
So whenever I try to find a word in the database, I
  1. loop over every line，if the first character is "&", use a variable called
     currentFile to hold the file name.
  2. if the first character of the line is "$" and whatever after "&" matches
     the keyword, all I need to do is to get the information after the first
     "*", and output them properly.

RESULT:
  for seach.cpp to search a total of 8.30 KB of .txt files to find 4 keywords,
  it takes 0.125s.
  for the database version of seach.cpp to construct a database for a total of
  8.30 KB of .txt, it takes 4.989s. To search for 4 keywords, it takes 0.109s

CONCLUSION: THE DATABASE VERSION OF search.cpp IS A BIT FASTER.
*/

bool checkWord(char chr) {
  /*
  check what is after the keyword, letter or symbol
  */
  if ((chr>='A' && chr<='Z') || (chr>='a' && chr>='z')) return false;
  return true;
}

bool checkCommand(string argv, string command) {
  /*
  check if the argument matches a command
  i.e. ./search --make-index
       command: --make-
       check if the first few characters of argv[1] match --make-
  */
  for (int i=0; i<command.length(); i++) {
    if (command[i] != argv[i]) {
      return false;
    }
  }
  return true;
}

int main(int argc, char const *argv[]) {
  string command = "--make-"; // command to construct database


  if (checkCommand(argv[1], command)) { // if the argv[1] is --make-something
    //***************************CONSTRUCT DATABASE***************************//
    string arg = argv[1]; // to remove the last character in argv[1]
    string fileType = ".txt"; // file type
    int typeLen = fileType.length(); // e.g. ".txt" has 4 characters in length
    DIR *dir = NULL; // for opendir()
    struct dirent *dirEntry = NULL; // for readdir()
    dir = opendir("."); // "." refers to the current directory
    if (dir == NULL) { // check if the path is initialized correctly
      cerr << "ERROR: The path is initialized incorrectly," << endl;
      exit(2);
    }
    string outfile = arg.substr(command.length(),arg.length()-command.length());
    // e.g. if arg is "--make-index", outfile would be "index"
    ofstream fout(outfile.c_str());
    /*
    if there is a file called outfile (refer to the variable above) under the
    current directory, overwrite the file. If there isn't, create one.
    */

    //***FOR STORING INFOMATION ABOUT THE DATABASE***//
    // e.g. the name of the database constructed
    ofstream fDATAINFO("DATABASEINFO");
    fDATAINFO << "&" << outfile;
    fDATAINFO.close();
    //***FINISHED STORING INFOMATION***//

    cout << "CONSTRUCTING DATABASE \"" << outfile << "\"" << endl;
    while (dirEntry = readdir(dir)) { //loop over files in the current directory
      if (dirEntry == NULL) { // if the something goes wrong
        cerr << "ERROR: dirEntry could not be initialised correctly" << endl;
        exit(3);
      }

      string fileName = dirEntry->d_name; // the name of file or directory

      if (fileName.length() > typeLen &&
          fileName.substr(fileName.length()-typeLen, typeLen) == fileType) {
        /*
        The name of a file has to be greater than the file type in length.
          i.e. For example, ".txt" has 4 characters. For a valid .txt file,
               the file names have to have at least 5 characters in length.
               Such that "a.txt", "b.txt", ..., instead of just ".txt" or "a.o"
        The last few characters in the name of a file has to match the file type
        extension.
          i.e. The last four characters in the name of the .txt file, "Romeo and
               Juliet.txt" has to match ".txt".
        */
        cout << "Constructing for \"" << fileName << "\"..." << endl;
        fout << '&' << fileName << endl;

        ifstream fin(fileName.c_str()); // .txt files
        while (!fin.eof()) {
          string word, line, dataLine; // word: words in the file
                                       // line: lines in the file
                                       // dataLine: lines in the database
          ifstream fin2(fileName.c_str()); // for seaching word (refer to
                                           // the variable above)
          ifstream fincheck(outfile.c_str()); // for checking duplicates in the
                                              // database
          fin >> word;
          int wordLen = word.length();

          //***FOR CHECKING DUPLICATES IN THE DATABASE***//
          bool currentFile=false, duplicate=false;
          while (!fincheck.eof()) {
            getline(fincheck, dataLine);
            if (dataLine[0] =='&' &&
                dataLine.substr(1,dataLine.length()-1) == fileName) {
              // search for current file
              currentFile = true;
            }
            if (currentFile && dataLine[0] == '$' &&
                dataLine.substr(1,wordLen) == word &&
                dataLine[wordLen+1] == '*') {
              // search for same words
              duplicate = true;
              break;
            }
            // check if encounter next file
            if (currentFile && dataLine[0] == '&' &&
                dataLine.substr(1,dataLine.length()-1) != fileName) break;

          }
          if (duplicate) continue; // if duplicate, skip the rest and go to next
                                   // word
          //***END CHECKING DUPLICATES***//

          fout << "$" << word; // output for database

          int count=0, lineNum=0;
          bool firstFound=true, lineFound=false, neverFound=true;
          while (!fin2.eof()) {
            getline(fin2,line);
            ++lineNum;
            for (int i=0; i<line.length(); i++) {
              // to check is the keyword is in the line
              if ((line.substr(i,wordLen)==word && checkWord(line[i+wordLen]) &&
                   i==0) ||
                  (line.substr(i,wordLen)==word && checkWord(line[i+wordLen]) &&
                  (i>0 && checkWord(line[i-1])))) {
                // cout << "the word: " << word << endl;
                /*
                The character before and after the keyword has to be checked.
                i.e. For keyword, "you", the "you" in "your book" and "iamyou"
                     would be not be counted, but the "you" in "you?" and "!you"
                     would be counted.

                ***P.S.*** Can delete checkWord(line[i+kwordLen[k]]) for as long
                ********** as the text matches the keyword. Change the if
                ********** statement (line 81 to 82) to:
                ********** if (line.substr(i,kwordLen[k])==keyword[k]) {
                ********** Original:
                ********** if (line.substr(i,kwordLen[k])==keyword[k] &&
                **********     checkWord(line[i+kwordLen[k]])) {
                */

                lineFound = true; // the keyword is found
                // cout << "word in" << endl;
                ++count; // number of times the keyword is found in a line
              }
            }
            if (lineFound) {
              fout << "*" << lineNum << "#" << count; // output for database
              count=0; // keyword count is reset after each line
              lineFound = false;
            }
          }
          fout << endl; // output format for database
          fin2.close();
          fincheck.close();
        }
        fin.close();
      }
    }
    cout << "DATABASE \"" << outfile << "\" CONSTRUCTED" << endl;
  } else {
    //*****************************SEARCH KEYWORD*****************************//
    ifstream databaseINFO("DATABASEINFO");
    if (!databaseINFO.is_open()) {
      cerr << "ERROR: DATABASE NOT CONSTRUCTED" << endl
           << "       PLEASE CONSTRUCT A DATABASE USING "
           <<        "\"--make-database_name\" COMMAND" << endl;
      exit(1);
    }
    string databaseName, line;
    databaseINFO >> line;
    databaseName = line.substr(1, line.length()-1);
    cout << "SEARCHING FROM \"" << databaseName << "\":" << endl;

    int numOfKeyword = argc-1;
    string keyword[numOfKeyword]; // arrays to hold the keywords
    int kwordLen[numOfKeyword];   // and the lengths of the keywords
    for (int i = 0; i < numOfKeyword; i++) {
      keyword[i] = argv[i+1]; // ith keywords
      kwordLen[i] = keyword[i].length(); //ith keyword lengths
    }
    string currentFile, numStr;
    bool neverFound=true;

    for (int k=0; k<numOfKeyword; k++) {
      ifstream fin(databaseName.c_str());

      cout << "keyword-" << k+1 << " \"" << keyword[k] << "\":" << endl;
      while (!fin.eof()) {
        getline(fin, line);
        if (line[0] == '&') {
          currentFile = line.substr(1, line.length()-1);
          continue;
        }
        if (line[0] == '$' && line.substr(1, kwordLen[k]) == keyword[k] &&
            line[kwordLen[k]+1] == '*') {
          cout << "\tFound in \"" << currentFile << "\" at ";
          neverFound = false;
          int currentState = 1, lineCount=0;

          for (int i=kwordLen[k]+1; i<line.length(); i++) {
            if (line[i] == '*') {
              ++lineCount;
              if (lineCount>1) {
                cout << " time";
                stringstream numStream(numStr);
                int numOfOccurrence;
                numStream >> numOfOccurrence;
                if (numOfOccurrence>1) cout << "s";
                cout << "), ";
              }
              cout << "line ";
              numStr="";
              currentState = 1;
              continue;
            } else if (line[i] == '#') {
              cout << " (";
              currentState = 2;
              continue;
            }
            if (currentState == 1) {
              cout << line[i];
            } else if (currentState == 2) {
              cout << line[i];
              numStr += line[i];
            }

          }
          cout << " time";
          stringstream numStream(numStr);
          int numOfOccurrence;
          numStream >> numOfOccurrence;
          if (numOfOccurrence>1) cout << "s";
          cout << ")" << endl;
        }
      }
      if (neverFound) cout << "\tNot found" << endl;
    }
  }

  // End of program
  return 0;
}
