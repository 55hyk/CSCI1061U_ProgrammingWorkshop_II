#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
  srand(time(NULL));
  int count=0, headCount=0, head, twice;
  while (1) {
    head = rand()%2;
    cout << "Result: ";
    count++;
    if (head) {
      headCount++;
      twice++;
      cout << "Head";
    } else {
      twice = 0;
      cout << "Tail";
    }
    cout << endl;
    if (twice == 2) {
      break;
    }
  }

  cout << "Total number of flips: " << count << endl
       << "Number of heads: " << headCount << endl;

  return 0;
}
