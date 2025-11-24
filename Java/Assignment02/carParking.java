import java.util.Scanner;

public class carParking {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int[] lot = new int[10];
    int pos = 0;
    int choice;
    boolean run = true;

    while (run) {
      System.out.println("\n======= MENU =======\n1: Park Car\n2: Remove Car\n3: Show Parked Cars\n4: Exit\n");
      System.out.print("Enter your choice: ");
      choice = sc.nextInt();

      switch (choice) {
        case 1:
          if (pos < 10) {
            System.out.print("Enter Car Number: ");
            int car = sc.nextInt();
            boolean isParked = false;
            for (int i = 0; i < pos; i++) {
              if (lot[i] == car) {
                isParked = true;
                break;
              }
            }
            if (isParked) {
              System.out.println("Car already parked");
            } else {
              lot[pos++] = car;
              System.out.println("Car parked successfully");
            }
          } else {
            System.out.println("Parking lot is full");
          }
          break;
        case 2:
          if (pos > 0) {
            System.out.print("Enter Car Number: ");
            int car = sc.nextInt();
            int carIdx = -1;
            for (int i = 0; i < pos; i++) {
              if (lot[i] == car) { // searching for the car
                carIdx = i;
              }
            }
            if (carIdx == -1) {
              System.out.println("Car not found");
            } else {
              int[] tempLot = new int[carIdx];
              for (int i = 0; i < carIdx; i++) { // temporary movement of the cars
                tempLot[i] = lot[i];
              }
              for (int i = carIdx; i < pos; i++) {
                lot[i] = lot[i + 1]; // removing the car
              }
              pos--;
              for (int i = carIdx - 1; i >= 0; i--) {
                lot[i] = tempLot[i]; // reshifting the cars
              }
              System.out.println("Car " + car + " removed");
            }
          } else {
            System.out.println("Parking lot is empty");
          }
          break;
        case 3:
          if (pos > 0) {
            System.out.print("Parked Cars: ");
            for (int i = 0; i < pos; i++) {
              System.out.print(lot[i] + " ");
            }
          } else {
            System.out.println("Parking lot is empty");
          }
          break;
        case 4: {
          System.out.println("Terminating...\n");
          run = false;
          break;
        }
        default:
          System.out.println("Invalid Choice");
          break;
      }
    }
    sc.close();
  }
}
