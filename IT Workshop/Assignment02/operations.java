import java.util.Scanner;

public class operations {

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    System.out.print("Enter the size of the array: ");
    int size = sc.nextInt();
    int[] nums = new int[size];
    System.out.print("Enter the array: ");
    for (int i = 0; i < size; i++) {
      nums[i] = sc.nextInt();
    }
    int choice;
    while (true) {
      System.out.println("\n======= MENU =======\n1: Find Average\n2: Second Largest\n3: Count Frequency\n4: Exit\n");
      System.out.print("Enter your choice: ");
      choice = sc.nextInt();

      if (choice == 1) {
        if (nums.length > 0) {
          double sum = 0;
          for (int i = 0; i < nums.length; i++) {
            sum += nums[i];
          }
          double avg = sum / nums.length;
          System.out.printf("Average: %.2f\n", avg);
        } else {
          System.out.println("Array should be of size grater than 0 !!");
        }
      } else if (choice == 2) {
        int largest = nums[0];
        for (int i = 0; i < nums.length; i++) {
          if (nums[i] > largest) {
            largest = nums[i];
          }
        }
        int secLargest = nums[0];
        for (int i = 0; i < nums.length; i++) {
          if (nums[i] == largest) {
            continue;
          } else if (nums[i] > secLargest) {
            secLargest = nums[i];
          }
        }
        if (secLargest == largest) {
          System.out.println("Second Largest does not exist !!");
        } else {
          System.out.println("Second Largest: " + secLargest);
        }
      } else if (choice == 3) {
        if (nums.length > 0) {
          System.out.print("Enter a number to check frequency: ");
          int num = sc.nextInt();
          int freq = 0;
          for (int i = 0; i < nums.length; i++) {
            if (nums[i] == num) {
              freq++;
            }
          }
          System.out.println("Frequency of " + num + " is " + freq);
        } else {
          System.out.println("Array should be of size grater than 0 !!");
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
