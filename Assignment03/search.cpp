#include <iostream>
#include <dirent.h> // directory entry
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

bool checkWord(char chr) {
  /*
  check what is after the keyword, letter or symbol
  */
  if ((chr>='A' && chr<='Z') || (chr>='a' && chr<='z')) return false;
  return true;
}

int main(int argc, char const *argv[]) {
  string fileType = ".txt"; // file type
  int typeLen = fileType.length(); // e.g. ".txt" has 4 characters in length
  int numOfKeyword = argc-1; // number of arguments after ./a.out or ./search
  string keyword[numOfKeyword]; // arrays to hold the keywords
  int kwordLen[numOfKeyword];   // and the lengths of the keywords
  for (int i = 0; i < numOfKeyword; i++) {
    keyword[i] = argv[i+1]; // ith keywords
    kwordLen[i] = keyword[i].length(); //ith keyword lengths
  }
  DIR *dir = NULL; // for opendir()
  struct dirent *dirEntry = NULL; // for readdir()


  // loop over the files for each keyword
  for (int k = 0; k < numOfKeyword; k++) {
    bool neverFound=true; // if a keyword is ever found

    dir = opendir("."); // "." refers to the current directory
    if (dir == NULL) { // check if the path is initialized correctly
      cerr << "ERROR: The path is initialized incorrectly," << endl;
      exit(1);
    }

    if (k>0) cout << endl; // output format
    cout << "keyword-" << k+1 << " \"" << keyword[k] << "\":";
    // e.g. keyword-1 "are":

    while (dirEntry = readdir(dir)) { //loop over files in the current directory
      if (dirEntry == NULL) { // if the something goes wrong
        cerr << "ERROR: dirEntry could not be initialised correctly" << endl;
        exit(3);
      }

      string fileName=dirEntry->d_name, line;// line: lines of content in a file
      int count=0, lineNum=0, lineCount=0;
      // count: how many times a keyword appears in one line
      // lineNum: which line in a file
      // lineCount: how many lines contain the keyword
      bool firstFound=true, lineFound=false;

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

        ifstream fin(fileName.c_str());//for every file in the current directory
        while (!fin.eof()) {
          getline(fin, line);
          ++lineNum; // which line is on
          for (int i=0; i<line.length(); i++) {
            // to check if the keyword is in the line
            if ((line.substr(i,kwordLen[k])==keyword[k] &&
                 checkWord(line[i+kwordLen[k]]) && i==0) ||
                (line.substr(i,kwordLen[k])==keyword[k] &&
                 checkWord(line[i+kwordLen[k]]) &&
                 i>0 && checkWord(line[i-1]))) {
              /*
              The character before and after the keyword has to be checked.
                i.e. For keyword, "you", the "you" in "your book" and "iamyou"
                     would be not be counted, but the "you" in "you?" and "!you"
                     would be counted.

              ***P.S.*** Can delete checkWord(line[i+kwordLen[k]]) for as long
              ********** as the text matches the keyword. Change the if
              ********** statement to:
              ********** if (line.substr(i,kwordLen[k])==keyword[k]) {
              ********** Original:
              ********** if (line.substr(i,kwordLen[k])==keyword[k] &&
              **********     checkWord(line[i+kwordLen[k]])) {
              */

              lineFound = true; // the keyword is found
              if (firstFound) { // output format
                cout << "\n\tFound in \"" << fileName << "\" at ";
                firstFound = false;
                neverFound = false;
              }
              ++count; // number of times the keyword is found in a line
            }
          }
          if (lineFound) {
            ++lineCount; // keep track how many lines contain the keyword
            if (lineCount>1) cout << ", "; // output format
            cout << "line " << lineNum << " (" << count << " time";
            if (count>1) cout << "s"; // output format
            cout << ")";
            count=0; // keyword count is reset after each line
            lineFound = false;
          }
        }
        fin.close();
      }
    }
    if (neverFound) cout << "\n\tNot found"; // if the keyword is never found

  }
  cout << endl; // output format

  // End of program
  closedir (dir);
  return 0;
}
