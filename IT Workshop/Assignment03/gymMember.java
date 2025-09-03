import java.util.Scanner;

class Member {
  int memberId;
  String name;
  String plan;
  double fee;

  Member(int memberId) {
    this.memberId = memberId;
  }

}

public class gymMember {

  public static void main(String[] args) {
    Member[] memberList = new Member[100];

    while (true) {

      int choice;
      System.out.println(
          "\n======= MENU =======\n1: Add Member\n2: Search Member\n3: Displey All\n4: Total Fee Collected\n5: Exit\n");
      System.out.print("Enter your choice: ");
      choice = sc.nextInt();

      if (choice == 1) {
        System.out.print("Enter Member ID: ");
        int memberId = sc.nextInt();
        System.out.print("Enter Name: ");
        String name = sc.next();
        System.out.print("Enter Plan: ");
        String plan = sc.next();
        System.out.print("Enter Fee: ");
        double fee = sc.nextDouble();
        Member member = new Member(memberId);
        member.name = name;
        member.plan = plan;
        member.fee = fee;
        System.out.println("Member added successfully.");
      } else if (choice == 2) {

      } else if (choice == 3) {

      } else if (choice == 4) {

      } else if (choice == 5) {

      } else {

      }

    }
    sc.close();
  }

}
