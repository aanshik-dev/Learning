import java.util.Scanner;

abstract class Customer {
  String name;
  double purchaseAmount;

  public Customer(String name, double purchaseAmount) {
    this.name = name;
    this.purchaseAmount = purchaseAmount;
  }

  public abstract double calculateBill();
}

interface Taxable {
  double TAX_RATE = 0.05;

  double addTax(double amount);
}

class RegularCustomer extends Customer implements Taxable {

  public RegularCustomer(String name, double purchaseAmount) {
    super(name, purchaseAmount);
  }

  public double calculateBill() {
    return purchaseAmount - (purchaseAmount * 0.05);
  };

  public double addTax(double amount) {
    return amount + (amount * TAX_RATE);
  }
}

class PremiumCustomer extends Customer implements Taxable {

  public PremiumCustomer(String name, double purchaseAmount) {
    super(name, purchaseAmount);
  }

  public double calculateBill() {
    return purchaseAmount - (purchaseAmount * 0.1);
  };

  public double addTax(double amount) {
    return amount + (amount * TAX_RATE);
  }
}

class CorporateCustomer extends Customer implements Taxable {

  public CorporateCustomer(String name, double purchaseAmount) {
    super(name, purchaseAmount);
  }

  public double calculateBill() {
    return purchaseAmount > 10000 ? purchaseAmount - (purchaseAmount * 0.15) : purchaseAmount - (purchaseAmount * 0.05);
  };

  public double addTax(double amount) {
    return amount + (amount * TAX_RATE);
  }
}

public class BillingSys {

  static Scanner sc = new Scanner(System.in);

  public static void main(String[] args) {
    System.out.println("");
    System.out.print("Enter number of customers: ");
    int n = sc.nextInt();
    Customer[] customers = new Customer[n];
    int index = 0;

    for (int i = 0; i < n; i++) {
      System.out.print("Enter customer name: ");
      String name = sc.next();
      System.out.print("Enter customer type: ");
      int type = sc.nextInt();
      System.out.print("Enter purchase amount: ");
      double amount = sc.nextDouble();
      System.out.println("");
      switch (type) {
        case 1:
          customers[index++] = new RegularCustomer(name, amount);
          break;
        case 2:
          customers[index++] = new PremiumCustomer(name, amount);
          break;
        case 3:
          customers[index++] = new CorporateCustomer(name, amount);
          break;
        default:
          System.out.println("Invalid customer type !!");
      }
    }

    System.out.println("\n");
    for (int i = 0; i < index; i++) {
      System.out.println("Customer " + (i + 1));
      System.out.println("Name: " + customers[i].name);
      System.out.println("Purchase Amount: " + customers[i].purchaseAmount);
      System.out.println("Discounted Bill: " + customers[i].calculateBill());
      System.out.println("Final Bill: " + ((Taxable) customers[i]).addTax(customers[i].calculateBill()));
      System.out.println("");
    }
  }

}
