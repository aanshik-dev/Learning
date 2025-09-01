#include <iostream>
using namespace std;

int main() {

  // COUT AND ENDL
  cout
      << "\n" // << and >> are overloaded operators
      << "HI" << endl
      << "I am Aanshik\n";
  std::cout << "I am learning CPP" << endl;

  printf("This Also Works.\n\n");
  // "\n is faster"

  // VARIABLES AND DATA TYPE
  int num = 25;              // 4 byte
  char grade = 'A';          // 1 byte
  float price = 75.56;       // 4 byte
  bool isValid = true;       // 1 byte
  double big = 25.545155461; // 8 byte

  // TYPE CASTING AND CONVERSION
  double value = price;     // Conversion - implicit - small to big
  int percent = (int)price; // Casting - Explicit - big to small
  cout << value << " & " << percent << "\n\n ";

  // USER INPUT
  cout << "Enter New Price: ";
  cin >> price;
  cout << "New Price: " << price << "\n";

  return 0;
}