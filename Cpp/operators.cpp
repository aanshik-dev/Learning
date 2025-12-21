#include <iostream>
using namespace std;

int main() {

  //  ARITHMETIC OPERATORS
  int a = 9, b = 4;
  int sum = a + b;
  int dif = a - b;
  int mul = a * b;
  int div = a / b;
  float div2 = (float)a / b;
  int mod = a % b;
  cout << "sum : " << sum << endl;
  cout << "difference : " << dif << endl;
  cout << "Mul : " << mul << endl;
  cout << "Divide : " << div << endl;
  cout << "Divide : " << div2 << endl;
  cout << "mod : " << mod << "\n\n";

  // RELATIONAL OPERATORS
  int p = 5, q = 8;
  cout << (p == q) << (p != q) << (p < q) << (p > q) << (p <= q) << (p >= q) << endl;

  // LOGICAL OPERATORS
  cout << (1 && 0) << (1 && 1) << (1 || 0) << (0 || 0) << (!0) << (!1) << endl;

  // BITWISE OPERATOR
  cout << "AND:" << (1 & 0) << " OR:" << (1 | 0) << " X-OR:" << (1 ^ 0) << " NOT:" << (~1) << " LEFT SHIFT:" << (1 << 2) << " RIGHT SHIFT:" << (1 >> 2) << endl;

  return 0;
}