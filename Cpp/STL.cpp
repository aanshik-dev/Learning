#include <deque>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
using namespace std;

int main() {
  { // LIST
    list<int> ls;
    list<int> ls1 = {2, 5, 6, 8, 9};
    list<int> ls2(ls1);  // Copy of ls1
    list<int> ls3(5, 0); // {0, 0, 0, 0, 0}
    list<char> l4(10);   // size 10, all '\0'

    ls2.pop_back();
    ls2.pop_front();
    ls2.emplace_back(12);
    ls2.emplace_front(15);
    ls2.push_back(10);
    ls2.push_front(1);

    list<int>::iterator itr = ls2.begin();
    for (itr; itr != ls2.end(); itr++) {
      cout << *itr << " ";
    }
    cout << endl;

    auto it = ls2.begin();
    advance(it, 3);
    cout << *it << endl;
  }

  { // QUEUE
    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    cout << q.front() << endl;
  }

  return 0;
}
