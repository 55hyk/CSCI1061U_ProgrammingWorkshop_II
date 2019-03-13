#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main(int argc, char const *argv[]) {
  string inFile = argv[1], outFile = argv[2];
  ifstream fin(inFile.c_str());
  ofstream fout(outFile.c_str());
  int A = (int)'A', a = (int)'a', Z = (int)'Z', z = (int)'z';

  if (fin.is_open()) {
    string line;

    while (getline(fin, line)) {
      for (int i = line.length()-1; i >= 0; i--) {
        if (line[i] >= a && line[i] <= z) {
          cout << (char)((int)line[i]-32);
          fout << (char)((int)line[i]-32);
        } else {
          cout << line[i];
          fout << line[i];
        }
      }
      cout << endl;
      fout << endl;
    }
  } else {
    cerr << "Unable to open file\n";
  }

  fin.close();
  fout.close();
  return 0;
}
