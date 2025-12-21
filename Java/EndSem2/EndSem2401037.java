import java.util.*;

abstract class Cab {
  protected String cabId;
  protected double baseFare = 20;

  public Cab(String cabId, double mult) {
    this.cabId = cabId;
    baseFare *= mult;
  }

  public abstract void display();

  public double getFare() {
    return baseFare;
  }
}

class MiniCab extends Cab {

  public MiniCab() {
    super("MiniCab", 1.0);
  }

  public MiniCab(String cabId, double mult) {
    super(cabId, mult);
  }

  public void display() {
    System.out.println("Cab ID : " + cabId);
    System.out.println("Cab BaseFare : " + baseFare);
  }
}

class Sedan extends MiniCab {

  public Sedan() {
    super("Sedan", 1.5);
  }

  public Sedan(String cabId, double mult) {
    super(cabId, mult);
  }

  public void display() {
    System.out.println("Cab ID : " + cabId);
    System.out.println("Cab BaseFare : " + baseFare);
  }
}

class SUVCab extends Sedan {
  public SUVCab() {
    super("SUVCab", 2.0);
  }

  public void display() {
    System.out.println("Cab ID : " + cabId);
    System.out.println("Cab BaseFare : " + baseFare);
  }
}

class Booking {
  public String customerName;
  private Cab cab;
  private double distanceInKm;
  private double totalFare;
  private double discount = 0;

  public Booking(String customerName, Cab cab, int distanceInKm, double fare) {
    this.customerName = customerName;
    this.cab = cab;
    this.distanceInKm = distanceInKm;
    this.totalFare = fare * distanceInKm;
    applyDiscount();
  }

  public void applyDiscount() {
    if (distanceInKm > 20) {
      discount = totalFare * 0.1;
    }
  }

  public void printBookingDetails() {
    System.out.println("\nCustomer Name: " + customerName);
    cab.display();
    System.out.println("Distance: " + distanceInKm);
    System.out.println("Total Fare: " + totalFare);
    System.out.println("Final Fare: " + (totalFare - discount));
    System.out.println("Discount : " + discount);
  }

  public void printDiscounted() {
    System.out.println("\nCustomer Name: " + customerName);
    System.out.println("Total Fare: " + totalFare);
    System.out.println("Discounted Fare: " + (totalFare - discount));
  }

  public double getdistance() {
    return distanceInKm;
  }

  public double getTotalFare() {
    return totalFare;
  }

  public double getDiscount() {
    return discount;
  }

  public Cab getCab() {
    return cab;
  }
}

class BookingManager {
  public static BookingManager instance = null;
  private ArrayList<Booking> bookingList = new ArrayList<Booking>();
  public boolean isDisplaying = false;
  public int totalBookings = 0;
  public double highest = 0;
  public double average = 0;

  private BookingManager() {
  }

  public static synchronized BookingManager getInstance() {
    if (instance == null)
      instance = new BookingManager();
    return instance;
  }

  public synchronized void addRequest(Booking booking) {
    if (isDisplaying) {
      try {
        wait();
      } catch (Exception e) {
      }
    } else {
      bookingList.add(booking);
      notifyAll();
    }
  }

  public synchronized void processRequest() {
    if (bookingList.size() == 0) {
      try {
        System.out.println("No Bookings found !!");
        wait();
      } catch (Exception e) {
      }
    } else {
      isDisplaying = true;
      for (int i = 0; i < bookingList.size(); i++) {
        bookingList.get(i).printBookingDetails();
      }
      isDisplaying = false;
      notifyAll();
    }
  }

  public synchronized void calculateSummary() {
    totalBookings = bookingList.size();
    double sum = 0;
    for (int i = 0; i < bookingList.size(); i++) {
      if (bookingList.get(i).getTotalFare() > highest) {
        highest = bookingList.get(i).getTotalFare();
      }
      sum += bookingList.get(i).getTotalFare();
    }
    average = sum / totalBookings;
  }

  public void searchName(String name) {
    boolean found = false;
    for (int i = 0; i < bookingList.size(); i++) {
      if (bookingList.get(i).customerName.equals(name)) {
        bookingList.get(i).printBookingDetails();
        found = true;
      }
    }
    if (!found) {
      System.out.println("Customer not found !!");
    }
  }

  public int getBookings() {
    calculateSummary();
    return totalBookings;
  }

  public void discounted() {
    boolean found = false;
    for (Booking book : bookingList) {
      if (book.getDiscount() > 0) {
        book.printDiscounted();
        found = true;
      }
    }
    if (!found)
      System.out.println("No discounted Bookings.");
  }

  public void sortList() {
    Collections.sort(bookingList, new Comparator<Booking>() {
      public int compare(Booking b1, Booking b2) {
        return Double.compare(b1.getTotalFare(), b2.getTotalFare());
      }
    });
  }

  public double getHighest() {
    calculateSummary();
    return highest;
  }

  public double getAverage() {
    calculateSummary();
    return average;
  }

}

class CustomerThread extends Thread {

  public Booking booking;

  public CustomerThread(Booking booking) {
    this.booking = booking;
  }

  public void run() {
    BookingManager.getInstance().addRequest(booking);
  }

}

class DisplayThread extends Thread {
  public void run() {
    BookingManager.getInstance().processRequest();
  }
}

public class EndSem2401037 {
  public static Scanner sc = new Scanner(System.in);
  public static BookingManager bookManage = BookingManager.getInstance();

  public static void inputData(Cab cab) {
    System.out.print("Enter Customer name: ");
    String name = sc.next();
    System.out.print("Enter Distance in KM: ");
    int distance = sc.nextInt();
    Booking book = new Booking(name, cab, distance, cab.getFare());
    CustomerThread customerThread = new CustomerThread(book);
    customerThread.start();
    try {
      customerThread.join();
    } catch (Exception e) {
    }
  }

  public static void main(String[] args) {
    while (true) {
      System.out.println("\n======= MENU =======");
      System.out.println("1. Book Mini Cab");
      System.out.println("2. Book Sedan");
      System.out.println("3. Book SUV");
      System.out.println("4. Show All Bookings");
      System.out.println("5. Show Total Bookings");
      System.out.println("6. Search by Customer Name");
      System.out.println("7. Sort by Fare");
      System.out.println("8. Discount Receivers");
      System.out.println("9. Show Highest Fare");
      System.out.println("10. Average Fare");
      System.out.println("11. Exit\n");

      int choice = 0;
      System.out.print("Enter your choice: ");
      choice = sc.nextInt();

      if (choice == 1) {
        Cab cab = new MiniCab();
        inputData(cab);
      } else if (choice == 2) {
        Cab cab = new Sedan();
        inputData(cab);
      } else if (choice == 3) {
        Cab cab = new SUVCab();
        inputData(cab);
      } else if (choice == 4) {
        DisplayThread displayThread = new DisplayThread();
        displayThread.start();
        try {
          displayThread.join();
        } catch (Exception e) {
        }
      } else if (choice == 5) {
        System.out.println("Total Bookings: " + bookManage.getBookings());
      } else if (choice == 6) {
        System.out.print("Enter Customer Name: ");
        String name = sc.next();
        bookManage.searchName(name);
      } else if (choice == 7) {
        System.out.println("The List has been Sorted based on the Fare !!");
        bookManage.sortList();
      } else if (choice == 8) {
        System.out.println("Discount Receivers: ");
        bookManage.discounted();
      } else if (choice == 9) {
        System.out.println("Highest Fare Booking: " + bookManage.getHighest());
      } else if (choice == 10) {
        System.out.println("Average Price: " + bookManage.getAverage());
      } else if (choice == 11) {
        System.out.println("Terminating...\n");
        break;
      } else {
        System.out.println("Invalid Choice !!");
      }
    }
  }
}