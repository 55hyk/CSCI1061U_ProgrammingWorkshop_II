#include "Queue.h"
using namespace Huang;


int main() {
  TQueue<int> q;
  q.push(1);
  q.push(10);

  cout << q.pop() << endl;

  return 0;
}
