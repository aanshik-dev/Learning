#include <iostream>
#include <string>
using namespace std;

string trimZero(string s) {
  int i = 0;
  while (i < s.length() - 1 && s[i] == '0')
    i++;
  return s.substr(i);
}

string addString(string s1, string s2) {
  int n1 = s1.length(), n2 = s2.length();
  int carry = 0;
  string res = "";
  for (int i = n1 - 1, j = n2 - 1; i >= 0 || j >= 0; i--, j--) {
    int sum = carry;
    if (i >= 0)
      sum += s1[i] - '0';
    if (j >= 0)
      sum += s2[j] - '0';
    carry = sum / 10;
    res = to_string(sum % 10) + res;
  }
  if (carry)
    res = to_string(carry) + res;
  return res;
}

string difString(string s1, string s2) {
  int n1 = s1.length(), n2 = s2.length();
  bool isNeg = false;
  if (n1 < n2 || (n1 == n2 && s1 < s2)) {
    swap(s1, s2);
    swap(n1, n2);
    isNeg = true;
  }
  int borrow = 0;
  string res = "";
  for (int i = n1 - 1, j = n2 - 1; i >= 0 || j >= 0; i--, j--) {
    int dif = borrow;
    if (i >= 0) {
      dif += s1[i] - '0';
    }
    if (j >= 0) {
      dif -= s2[j] - '0';
    }
    if (dif < 0) {
      dif += 10;
      borrow = -1;
    } else {
      borrow = 0;
    }
    res = to_string(dif) + res;
  }
  res = trimZero(res);
  if (isNeg) {
    res = "-" + res;
  }
  return res;
}

string karatsuba(string s1, string s2) {
  s1 = trimZero(s1);
  s2 = trimZero(s2);
  if (s1 == "0" || s2 == "0")
    return "0";

  int n1 = s1.length(), n2 = s2.length();
  int n = max(n1, n2);

  if (n1 == 1 && n2 == 1) {
    return to_string((s1[0] - '0') * (s2[0] - '0'));
  }

  while (s1.size() < n) {
    s1 = "0" + s1;
  }
  while (s2.size() < n) {
    s2 = "0" + s2;
  }

  int m = n / 2;
  int half = n - m;

  string a = s1.substr(0, m);
  string b = s1.substr(m);
  string c = s2.substr(0, m);
  string d = s2.substr(m);

  string ac = karatsuba(a, c);
  string bd = karatsuba(b, d);
  string sumAB = addString(a, b);
  string sumCD = addString(c, d);
  string bracket = karatsuba(sumAB, sumCD);
  string adbc = difString(bracket, addString(ac, bd));

  for (int i = 0; i < 2 * half; i++)
    ac += "0";
  for (int i = 0; i < half; i++)
    adbc += "0";

  string res = addString(addString(ac, adbc), bd);

  return res;
}

int main() {
  string s1 = "12345678", s2 = "87654321";
  string res = karatsuba(s1, s2);
  cout
      << "\nProduct: " << s1 << " X " << s2 << " = " << res << "\n\n";
  return 0;
}
