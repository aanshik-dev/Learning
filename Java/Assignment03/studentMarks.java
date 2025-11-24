import java.util.Scanner;

class Student {
  private int studentId;
  private int[] marks;
  private int[] subjectIds;

  Student(int studentId, int[] subjectIds, int[] marks) {
    this.studentId = studentId;
    this.subjectIds = subjectIds;
    this.marks = marks;
  }

  public int getStudentId() {
    return studentId;
  }

  public void display() {
    System.out.println("Student ID : " + studentId);
    for (int i = 0; i < subjectIds.length; i++) {
      System.out.println("Subject : " + subjectIds[i] + " Marks : " + marks[i]);
    }
    System.out.print("\n");
  }

  public double average() {
    double doubleSum = 0;
    for (int i = 0; i < marks.length; i++) {
      doubleSum += marks[i];
    }
    return doubleSum / marks.length;
  }

  public int subjectMarks(int subjectId) {
    int m = -1;
    for (int i = 0; i < subjectIds.length; i++) {
      if (subjectIds[i] == subjectId) {
        m = marks[i];
      }
    }
    return m;
  }

}

public class studentMarks {

  private static Scanner sc = new Scanner(System.in);
  private static int maxSize = 100;
  private static int counter = 0;
  private static Student[] studentData = new Student[maxSize];

  private static int search(int studentId) {
    for (int i = 0; i < counter; i++) {
      if (studentData[i].getStudentId() == studentId) {
        return i;
      }
    }
    return -1;
  }

  private static void enterMarks() {
    if (counter < maxSize) {
      System.out.print("Enter Student ID: ");
      int studentId = sc.nextInt();
      int index = search(studentId);
      if (index != -1) {
        System.out.println("Member ID already exists !!");
      } else {
        System.out.print("Enter number of subjects registered: ");
        int n = sc.nextInt();
        int[] subjectIds = new int[n];
        int[] marks = new int[n];
        System.out.println("Enter subject ID and Marks in format: ID MARKS");
        for (int i = 0; i < n; i++) {
          System.out.print(">> ");
          subjectIds[i] = sc.nextInt();
          marks[i] = sc.nextInt();
        }
        studentData[counter++] = new Student(studentId, subjectIds, marks);
        System.out.println("Student Marks Added Successfully !!");
      }
    } else {
      System.out.println("Student Database is Full !!");
    }
  }

  private static void average() {
    System.out.print("Enter Student ID: ");
    int studentId = sc.nextInt();
    int index = search(studentId);
    if (index != -1) {
      double avg = studentData[index].average();
      System.out.println("Student Average Marks: " + avg);
    } else {
      System.out.println("Student does not exist in database !!");
    }
  }

  private static void highestInSubject() {
    System.out.print("Enter Subject ID: ");
    int subjectId = sc.nextInt();
    int highest = -1;
    for (int i = 0; i < counter; i++) {
      int marks = studentData[i].subjectMarks(subjectId);
      if (marks > highest) {
        highest = marks;
      }
    }
    if (highest == -1) {
      System.out.println("Subject does not exist !!");
      return;
    }
    System.out.println("Highest Marks in Subject " + subjectId + " : " + highest);
  }

  public static void main(String[] args) {

    while (true) {
      int choice;
      System.out.println(
          "\n======= MENU =======\n1: Add Student Marks\n2: Student's Average\n3: Hightest of Subject\n4: Display\n5: Exit\n");
      System.out.print("Enter your choice: ");
      choice = sc.nextInt();

      if (choice == 1) {
        enterMarks();
      } else if (choice == 2) {
        average();
      } else if (choice == 3) {
        highestInSubject();
      } else if (choice == 4) {
        if (counter > 0) {
          System.out.println("Displaying All Students Marks !! \n");
          for (int i = 0; i < counter; i++) {
            studentData[i].display();
          }
        } else {
          System.out.println("Database is Empty !!");
        }
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
