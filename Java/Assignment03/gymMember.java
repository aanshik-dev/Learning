import java.util.Scanner;

class Member {
  private int memberId;
  private String name;
  private String plan;
  private double fee;

  Member(int memberId) {
    this.memberId = memberId;
  }

  Member(int memberId, String name, String plan, double fee) {
    this.memberId = memberId;
    this.name = name;
    this.plan = plan;
    this.fee = fee;
  }

  public int getMemberId() {
    return memberId;
  }

  public String getName() {
    return name;
  }

  public String getPlan() {
    return plan;
  }

  public double getFee() {
    return fee;
  }

  public void display() {
    System.out.println("Member ID: " + memberId);
    System.out.println("Name: " + name);
    System.out.println("Plan: " + plan);
    System.out.println("Fee: " + fee + "\n");
  }

}

public class gymMember {

  private static int maxSize = 100;
  private static int counter = 0;
  private static Member[] memberList = new Member[maxSize];

  private static int search(int memberId) {
    for (int i = 0; i < counter; i++) {
      if (memberList[i].getMemberId() == memberId) {
        return i;
      }
    }
    return -1;
  }

  public static void main(String[] args) {

    Scanner sc = new Scanner(System.in);

    while (true) {

      int choice;
      System.out.println(
          "\n======= MENU =======\n1: Add Member\n2: Search Member\n3: Displey All\n4: Total Fee Collected\n5: Exit\n");
      System.out.print("Enter your choice: ");
      choice = sc.nextInt();

      if (choice == 1) {
        if (counter < maxSize) {
          System.out.print("Enter Member ID: ");
          int memberId = sc.nextInt();
          int index = search(memberId);
          if (index != -1) {
            System.out.println("Member ID already exists !!");
            continue;
          }
          System.out.print("Enter Name: ");
          String name = sc.next();
          System.out.println("Choose Plan ---- ");
          System.out.println("1. Monthly\n2. Quarterly\n3. Yearly");
          System.out.print("Plan Choice: ");
          choice = sc.nextInt();
          String plan = "Monthly";
          if (choice == 1) {
            plan = "Monthly";
          } else if (choice == 2) {
            plan = "Quarterly";
          } else if (choice == 3) {
            plan = "Yearly";
          } else {
            System.out.println("Invalid Choice !!");
            continue;
          }
          System.out.print("Enter Fee: ");
          double fee = sc.nextDouble();
          memberList[counter++] = new Member(memberId, name, plan, fee);
          System.out.println(memberList[counter - 1].getName() + " added Successfully !!");

        } else {
          System.out.println("Member List Full !!");
        }
      } else if (choice == 2) {
        System.out.print("Enter Member ID: ");
        int memberId = sc.nextInt();
        int index = search(memberId);
        if (index != -1) {
          System.out.println("\nMember found !!");
          memberList[index].display();
        } else {
          System.out.println("Member ID not found !!");
        }
      } else if (choice == 3) {
        if (counter > 0) {
          System.out.println("Displaying All Members !! \n");
          for (int i = 0; i < counter; i++) {
            memberList[i].display();
          }
        } else {
          System.out.println("Member List is Empty !!");
        }
      } else if (choice == 4) {
        double totalFee = 0;
        for (int i = 0; i < counter; i++) {
          totalFee += memberList[i].getFee();
        }
        System.out.println("Total Fee Collected: " + totalFee);
      } else if (choice == 5) {
        System.out.println("Process Terminating...\n");
        break;
      } else {
        System.out.println("Invalid Choice !!");
      }

    }
    sc.close();
  }

}
