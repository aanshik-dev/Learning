import java.util.*;
import java.lang.*;

abstract class FoodItem {
  protected String name;
  protected double price;

  public FoodItem(String name, double price) {
    this.name = name;
    this.price = price;
  }

  public abstract void display();

  public double getPrice() {
    return price;
  }
}

abstract class Pizza extends FoodItem {

  public Pizza(String name, double price) {
    super(name, price);
  }

  public abstract void display();
}

abstract class Burger extends FoodItem {

  public Burger(String name, double price) {
    super(name, price);
  }

  public abstract void display();
}

abstract class Biriyani extends FoodItem {

  public Biriyani(String name, double price) {
    super(name, price);
  }

  public abstract void display();
}

class VegPizza extends Pizza {
  public VegPizza() {
    super("Veg Pizza", 100);
  }

  @Override
  public void display() {
    System.out.println("Food Item : " + name);
    System.out.println("Price : " + price);
  };
}

class ChickenPizza extends Pizza {
  public ChickenPizza() {
    super("Chicken Pizza", 150);
  }

  @Override
  public void display() {
    System.out.println("Food Item : " + name);
    System.out.println("Price : " + price);
  };
}

class VegBurger extends Burger {
  public VegBurger() {
    super("Veg Burger", 80);
  }

  @Override
  public void display() {
    System.out.println("Food Item : " + name);
    System.out.println("Price : " + price);
  };
}

class CheeseBurger extends Burger {
  public CheeseBurger() {
    super("Cheese Burger", 120);
  }

  @Override
  public void display() {
    System.out.println("Food Item : " + name);
    System.out.println("Price : " + price);
  };
}

class VegBiriyani extends Biriyani {
  public VegBiriyani() {
    super("Veg Biriyani", 100);
  }

  @Override
  public void display() {
    System.out.println("Food Item : " + name);
    System.out.println("Price : " + price);
  };
}

class ChickenBiriyani extends Biriyani {
  public ChickenBiriyani() {
    super("Chicken Biriyani", 150);
  }

  @Override
  public void display() {
    System.out.println("Food Item : " + name);
    System.out.println("Price : " + price);
  };
}

class Order {
  public String customerName;
  private FoodItem item;
  private int quantity;
  private double finalAmount;
  private double discount = 0;

  public Order(String customerName, FoodItem item, int quantity, double price) {
    this.customerName = customerName;
    this.item = item;
    this.quantity = quantity;
    this.finalAmount = price * quantity;
    applyDiscount();
  }

  public void applyDiscount() {
    if (quantity > 3) {
      discount = finalAmount * 0.1;
    }
  }

  public void printOrderDetails() {
    System.out.println("\nCustomer Name: " + customerName);
    item.display();
    System.out.println("Quantity: " + quantity);
    System.out.println("Total Amount: " + finalAmount);
    System.out.println("Final Amount: " + (finalAmount - discount));
    System.out.println("Discount : " + discount);
  }

  public void printDiscounted() {
    System.out.println("\nCustomer Name: " + customerName);
    System.out.println("Total Amount: " + finalAmount);
    System.out.println("Discounted Amount: " + (finalAmount - discount));
  }

  public int getQuantity() {
    return quantity;
  }

  public double getFinalAmount() {
    return finalAmount;
  }

  public double getDiscount() {
    return discount;
  }

  public FoodItem getItem() {
    return item;
  }
}

class OrderManager {
  public static OrderManager instance;
  private ArrayList<Order> orderList = new ArrayList<Order>();
  private static int totalOrders;
  public boolean isDisplayInProgress;

  private OrderManager() {
    totalOrders = 0;
    isDisplayInProgress = false;
  }

  public static synchronized OrderManager getInstance() {
    if (instance == null)
      instance = new OrderManager();
    return instance;
  }

  public synchronized void addOrder(Order order) {
    if (isDisplayInProgress) {
      try {
        wait();
      } catch (Exception e) {
      }
    } else {
      orderList.add(order);
      totalOrders++;
      notifyAll();
    }
  }

  public synchronized void displayOrder() {
    if (orderList.size() == 0) {
      try {
        System.out.println("No orders found !!");
        wait();
      } catch (Exception e) {
      }
    } else {
      isDisplayInProgress = true;
      for (int i = 0; i < orderList.size(); i++) {
        orderList.get(i).printOrderDetails();
      }
      isDisplayInProgress = false;
      notifyAll();
    }
  }

  public void searchName(String name) {
    boolean found = false;
    for (int i = 0; i < orderList.size(); i++) {
      if (orderList.get(i).customerName.equals(name)) {
        orderList.get(i).printOrderDetails();
        found = true;
      }
    }
    if (!found) {
      System.out.println("Customer not found !!");
    }
  }

  public int getOrders() {
    return totalOrders;
  }

  public void discounted() {
    boolean found = false;
    for (Order o : orderList) {
      if (o.getDiscount() > 0) {
        o.printDiscounted();
        found = true;
      }
    }
    if (!found)
      System.out.println("No discounted orders.");
  }

  public double highestPrice() {
    double highest = 0;
    for (int i = 0; i < orderList.size(); i++) {
      if (orderList.get(i).getFinalAmount() > highest) {
        highest = orderList.get(i).getFinalAmount();
      }
    }
    return highest;
  }

  public double averagePrice() {
    double sum = 0;
    for (int i = 0; i < orderList.size(); i++) {
      sum += orderList.get(i).getFinalAmount();
    }
    return sum / orderList.size();
  }

}

class CustomerThread extends Thread {

  public Order order;

  public CustomerThread(Order order) {
    this.order = order;
  }

  public void run() {
    OrderManager.getInstance().addOrder(order);
  }

}

class DisplayThreads extends Thread {
  public void run() {
    OrderManager.getInstance().displayOrder();
  }
}

public class FoodMenu {
  public static Scanner sc = new Scanner(System.in);

  public static void inputData(FoodItem item) {
    System.out.print("Enter your name: ");
    String name = sc.next();
    System.out.print("Enter quantity: ");
    int quantity = sc.nextInt();
    Order order = new Order(name, item, quantity, item.price);
    CustomerThread customerThread = new CustomerThread(order);
    customerThread.start();
    try {
      customerThread.join();
    } catch (Exception e) {
    }
  }

  public static void main(String[] args) {
    OrderManager orderManager = OrderManager.getInstance();
    while (true) {
      System.out.println("\n======= MENU =======");
      System.out.println("1. Order Pizza");
      System.out.println("2. Order Burger");
      System.out.println("3. Order Biriyani");
      System.out.println("4. Display Orders");
      System.out.println("5. Total Orders");
      System.out.println("6. Search By Customer Name");
      System.out.println("7. Discounted Customers");
      System.out.println("8. Highest Price");
      System.out.println("9. Average Price");
      System.out.println("10. Exit\n");

      int choice = 0;
      int ch = 0;
      System.out.print("Enter your choice: ");
      choice = sc.nextInt();

      if (choice == 1) {
        System.out.println("1. Veg Pizza");
        System.out.println("2. Chicken Pizza");
        System.out.print("Enter your choice : ");
        ch = sc.nextInt();
        FoodItem item = null;
        if (ch == 1) {
          item = new VegPizza();
        } else if (ch == 2) {
          item = new ChickenPizza();
        } else {
          System.out.println("Invalid choice !!");
          continue;
        }
        inputData(item);
      } else if (choice == 2) {
        System.out.println("1. Veg Burger");
        System.out.println("2. Cheese Burger");
        System.out.print("Enter your choice : ");
        ch = sc.nextInt();
        FoodItem item = null;
        if (ch == 1) {
          item = new VegBurger();
        } else if (ch == 2) {
          item = new CheeseBurger();
        } else {
          System.out.println("Invalid choice !!");
          continue;
        }
        inputData(item);
      } else if (choice == 3) {
        System.out.println("1. Veg Biriyani");
        System.out.println("2. Chicken Biriyani");
        System.out.print("Enter your choice : ");
        ch = sc.nextInt();
        FoodItem item = null;
        if (ch == 1) {
          item = new VegBiriyani();
        } else if (ch == 2) {
          item = new ChickenBiriyani();
        } else {
          System.out.println("Invalid choice !!");
          continue;
        }
        inputData(item);
      } else if (choice == 4) {
        DisplayThreads displayThread = new DisplayThreads();
        displayThread.start();
        try {
          displayThread.join();
        } catch (Exception e) {
        }
      } else if (choice == 5) {
        System.out.println("Total Orders: " + orderManager.getOrders());
      } else if (choice == 6) {
        System.out.print("Enter Customer Name: ");
        String name = sc.next();
        orderManager.searchName(name);
      } else if (choice == 7) {
        System.out.println("Discounted Customers: ");
        orderManager.discounted();
      } else if (choice == 8) {
        System.out.println("Highest Price Order: " + orderManager.highestPrice());
      } else if (choice == 9) {
        System.out.println("Average Price: " + orderManager.averagePrice());
      } else if (choice == 10) {
        System.out.println("Terminating...");
        break;
      } else {
        System.out.println("Invalid Choice !!");
      }
    }
  }
}
