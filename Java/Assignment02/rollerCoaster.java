import java.util.Scanner;

public class rollerCoaster {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int[] que = new int[10];
    int pos = 0;
    int choice;

    while (true) {
      System.out.println("\n======= MENU =======\n1: Join Queue\n2: Ride\n3: Display Queue\n4: Exit\n");
      System.out.print("Enter your choice: ");
      choice = sc.nextInt();

      if (choice == 1) {
        if (pos < 10) {
          System.out.print("Enter Visitor ID: ");
          int vis = sc.nextInt();
          boolean isEnqueued = false;
          for (int i = 0; i < pos; i++) {
            if (que[i] == vis) {
              isEnqueued = true;
            }
          }
          if (isEnqueued) {
            System.out.println("Visitor is already in queue !!");
          } else {
            que[pos++] = vis;
            System.out.println("Visitor Enqueued Successfully !!");
          }
        } else {
          System.out.println("Queue Full");
        }
      } else if (choice == 2) {
        if (pos > 0) {
          if (pos <= 3) {
            pos = 0;
          } else {
            for (int i = 3; i < pos; i++) {
              que[i - 3] = que[i];
            }
            pos -= 3;
          }
          System.out.println("Atmost 3 Visitors Ridden Successfully !!");
        } else {
          System.out.println("Queue Empty");
        }
      } else if (choice == 3) {
        if (pos > 0) {
          System.out.print("Queue: ");
          for (int i = 0; i < pos; i++) {
            System.out.print(que[i] + " ");
          }
          System.out.println("\n");
        } else {
          System.out.println("Queue Empty");
        }
      } else if (choice == 4) {
        System.out.println("Terminating...\n");
        break;
      } else {
        System.out.println("Invalid Choice !!");
      }
    }
    sc.close();
  }
}
