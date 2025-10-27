import java.util.Scanner;

class Calculator {
  public double multiply() {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter first number: ");
    double a = sc.nextDouble();
    System.out.print("Enter second number: ");
    double b = sc.nextDouble();
    return a * b;
  }

  public double multiply(double a, double b) {
    return a * b;
  }

  public double multiply(double a, double b, double c) {
    return a * b * c;
  }

  public double multiply(double[] numbers) {
    double product = 1;
    for (double num : numbers) {
      product *= num;
    }
    return product;
  }
}

class MethodOverloading {
  public static void main(String[] args) {
    Calculator calculator = new Calculator();
    double result1 = calculator.multiply();
    double result2 = calculator.multiply(2.5, 3.0);
    double result3 = calculator.multiply(2.0, 3.5, 4.0);
    double[] numbers = { 10.0, 12.6, 3.0 };
    double result4 = calculator.multiply(numbers);
    System.out.println("Result 1: " + result1);
    System.out.println("Result 2: " + result2);
    System.out.println("Result 3: " + result3);
    System.out.println("Result 4: " + result4);
  }
}