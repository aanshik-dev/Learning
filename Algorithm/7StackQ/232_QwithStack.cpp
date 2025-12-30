#include <bits/stdc++.h>
using namespace std;

class MyQueue {
  public:
  void push(int x) {
    in_stk.push(x);
  }

  int pop() {
    peek();
    const int val = out_stk.top();
    out_stk.pop();
    return val;
  }

  int peek() {
    if (out_stk.empty())
      while (!in_stk.empty()) {
        out_stk.push(in_stk.top());
        in_stk.pop();
      }
    return out_stk.top();
  }

  bool empty() {
    return in_stk.empty() && out_stk.empty();
  }

  private:
  stack<int> in_stk;
  stack<int> out_stk;
};

int main() {
  MyQueue *obj = new MyQueue();
  obj->push(1);
  int param_2 = obj->pop();
  int param_3 = obj->peek();
  bool param_4 = obj->empty();
  cout << param_2 << " " << param_3 << " " << param_4 << endl;
  return 0;
}