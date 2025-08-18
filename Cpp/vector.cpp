#include <climits>
#include <iostream>
#include <vector>
using namespace std;

void revVect(vector<int> &vect) {
  int size = vect.size();
  for (int i = 0, j = size - 1; i <= j; i++, j--) {
    if (&vect[i] != &vect[j]) {
      vect[i] = vect[i] ^ vect[j];
      vect[j] = vect[i] ^ vect[j];
      vect[i] = vect[i] ^ vect[j];
    }
  }
}

// Majority Element: {1, 5, 1, 5, 5, 1, 5};
int major(vector<int> vect) {
  int size = vect.size();
  int count = 0, major = 0;
  for (int i = 0; i < size; i++) {
    if (count == 0) {
      major = vect[i];
    }
    if (major == vect[i]) {
      count++;
    } else {
      count--;
    }
  }
  return major;
}

int main() {
  // Excercise 1: This is the implementation of vector declaration and initiallisation
  {
    vector<int> vect;
    vect = {1, 2, 3, 4, 5};
    vect = {5, 4, 11, 24, 25}; // this retains
    vector<int> vect1(5, 0);   // size five with value 0
    vector<char> vect2(10);    // by default value is \0
    vect2[0] = 'A';
    vect2[1] = 'B';
    vect2[2] = '$';
    cout
        << endl
        << "Excercise 1: "
        << vect2[2] << " ";

    vector<int> temp(vect.begin() + 1, vect.begin() + 4);
    cout << "Sub vector: "; // Gives a Sub Vector on passinng iterators
    for (int i : temp) {
      cout << i << " ";
    }
    cout << endl;
  }

  // Excercise 2: This is the implementation of vector methods
  {
    cout << "Excercise 2: ";
    vector<int> v(10, 0);
    v = {11, 4, 6, 8, 21};

    cout << v.size() << " ";
    cout << v.capacity() << " ";
    cout << v.front() << " ";
    cout << v.back() << " ";
    v.push_back(24);
    cout << v.back() << " ";
    v.pop_back();
    cout << v.back() << " ";
    cout << v.at(2) << " ";
    v.shrink_to_fit();
    cout << v.capacity() << " ";
    v.clear();
    cout << v.empty() << " ";
    cout << v.size() << " ";
    cout << v.capacity() << endl;
  }

  // Excercise 3: This is the implementation of reallocation of vetor with double the size of the previous one
  {
    vector<int> vect;
    cout << "Excercise 3: ";
    cout << vect.capacity() << " ";
    vect.push_back(1);
    cout << vect.capacity() << " ";
    vect.push_back(2);
    cout << vect.capacity() << " ";
    vect.push_back(3);
    cout << vect.capacity() << " ";
    vect.push_back(4);
    cout << vect.capacity() << " ";
    vect.push_back(5);
    cout << vect.capacity() << endl;
  }

  // Excercise 4: Reversing a vector with reference
  {
    vector<int> vect = {1, 3, 6, 7, 45, 3, 28, 11, 24};
    cout << "Excercise 4: ";
    revVect(vect);
    for (int i : vect) {
      cout << i << " ";
    }
    cout << endl;
  }

  // Excercise 5: Kadane's Algorithm: Used to find Max subarray Sum of an array
  {
    vector<int> vect = {1, -2, 6, 45, 7, 3, -24, 11, -14};
    int sum = 0, maxSum = INT_MIN, st = 0, end = 0;
    for (int i = 0; i < vect.size(); i++) {
      sum += vect[i];
      if (sum > maxSum) {
        maxSum = sum;
        end = i;
      }
      if (sum < 0) {
        st = i + 1;
        sum = 0;
      }
    }
    cout << "Excercise 5: Sum: " << maxSum << " ";
    cout << "Range: [ " << st << " " << end << " ] SubArray : ";
    vector<int> temp(vect.begin() + st, vect.begin() + end + 1);
    for (int i : temp) {
      cout << i << " ";
    }
    cout << endl;
  }

  // Excercise 6: Moore's Algorithm
  {
    vector<int> vect = {1, 5, 1, 5, 5, 1, 5};
    cout << "Excercise 6: " << major(vect) << endl;
  }

  return 0;
}