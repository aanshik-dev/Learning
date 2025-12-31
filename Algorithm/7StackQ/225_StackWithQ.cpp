#include <bits/stdc++.h>
using namespace std;

class MyStack {
  private:
  queue<int> q1, q2;

  public:
  void push(int x) {
    q2.push(x);
    while (!q1.empty()) {
      q2.push(q1.front());
      q1.pop();
    }
    swap(q1, q2);
  }
  int pop() {
    int val = q1.front();
    q1.pop();
    return val;
  }
  int top() {
    return q1.front();
  }
  bool empty() {
    return q1.empty();
  }
};

int main() {
  MyStack *obj = new MyStack();
  obj->push(5);
  int param_3 = obj->top();
  int param_2 = obj->pop();
  bool param_4 = obj->empty();
  cout << param_2 << " " << param_3 << " " << param_4 << endl;
  return 0;
}