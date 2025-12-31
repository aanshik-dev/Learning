#include <bits/stdc++.h>
using namespace std;

class MinStack {
  private:
  stack<pair<int, int>> st;

  public:
  MinStack() {
  }
  void push(int val) {
    if (st.empty()) {
      st.push({val, val});
    } else {
      st.push({val, min(val, st.top().second)});
    }
  }

  void pop() {
    st.pop();
  }

  int top() {
    return st.empty() ? -1 : st.top().first;
  }

  int getMin() {
    return st.empty() ? -1 : st.top().second;
  }
};

int main() {

  MinStack *obj = new MinStack();
  obj->push(5);
  obj->push(8);
  obj->push(2);
  obj->push(6);
  cout << obj->top() << " " << obj->getMin() << endl;
  obj->pop();
  cout << obj->top() << " " << obj->getMin() << endl;
  obj->pop();
  cout << obj->top() << " " << obj->getMin() << endl;
  return 0;
}