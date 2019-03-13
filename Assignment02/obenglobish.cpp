#include <iostream>
#include <string>
// #include <cstdlib>

using namespace std;

string obenglobish(const string& english) {
  char vowel[10] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
  string trans="", ob = "ob";
  int wordLen=english.length(), count=0;
  bool consec=false;

  for (int i = 0; i < wordLen; i++) {
    for (int j = 0; j < 5; j++) {
      if (english[i] == vowel[j] || english[i] == vowel[j+5]) {
        for (int k = 0; k < 5; k++) {
          if (i > 0 && (english[i-1]==vowel[k] || english[i-1]==vowel[k+5])) {
            trans += english[i];
            consec = true;
            break;
          }
        }
        if (consec) {
          consec = false;
          break;
        }

        if (i == wordLen-1 && (vowel[j] == 'e' || vowel[j+5] == 'E')) {
          trans += english[i];
          break;
        }

        trans += (ob + english[i]);

        break;
      } else {
        count++;
        if (count==5) {
          trans += english[i];
          count = 0;
        }
      }
    }
    count = 0;
  }

  return trans;
}

int main() {
  while (true) {
    string word;

    cout << "Enter a word: ";
    cin >> word;
    if (word == "QUIT") break;
    string trans = obenglobish(word);
    cout << word << " -> " << trans << endl;
  }

  return 0;
}
