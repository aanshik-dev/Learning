import java.io.*;
import java.util.ArrayList;
import java.util.Scanner;

class Student {
  String SrNo;
  String name;
  String major;
  String level;
  String age;

  Student(String SrNo, String name, String major, String level, String age) {
    this.SrNo = SrNo;
    this.name = name;
    this.major = major;
    this.level = level;
    this.age = age;
  }
}

class Factulty {
  String id;
  String name;
  String depart;

  Factulty(String id, String name, String depart) {
    this.id = id;
    this.name = name;
    this.depart = depart;
  }
}

class StudentData {

  ArrayList<Student> studentList = new ArrayList<Student>();

  StudentData() {
    setStudentData();
  }

  void setStudentData() {
    try {
      studentList.clear();
      BufferedReader br = new BufferedReader(new FileReader("files/student.txt"));
      String line = br.readLine();
      String array[] = new String[5];
      while (line != null) {
        if (line.contains("(")) {
          line = line.substring(line.indexOf("(") + 1);
        }
        for (int i = 0; i < 4; i++) {
          array[i] = line.substring(0, line.indexOf(","));
          line = line.substring(line.indexOf(",") + 1);
        }
        array[4] = line.substring(0, 2);
        studentList.add(new Student(array[0], array[1], array[2], array[3], array[4]));
        line = br.readLine();
      }
      br.close();
    } catch (Exception e) {
      System.out.println(e);
    }
  }

  // Question 1
  void prStudent() {
    for (int i = 0; i < studentList.size(); i++) {
      System.out.println("\nName: " + studentList.get(i).name + "\nAge: " + studentList.get(i).age);
    }
  }

  // Question 2
  void printStudent(int age) {
    boolean empty = true;
    System.out.print("\n");
    for (int i = 0; i < studentList.size(); i++) {
      if (Integer.parseInt(studentList.get(i).age) > age) {
        empty = false;
        System.out.println("SrNo: " + studentList.get(i).SrNo + " | Name: " + studentList.get(i).name + " | Major: "
            + studentList.get(i).major + " | Level: " + studentList.get(i).level + " | Age: " + studentList.get(i).age);
      }
    }
    if (empty) {
      System.out.println("No student found above " + age);
    }
  }

  // Question 4
  void srToName(ArrayList<String> sr) {
    boolean empty = true;
    System.out.print("\n");
    for (int i = 0; i < sr.size(); i++) {
      for (int j = 0; j < studentList.size(); j++) {
        if (sr.get(i).equals(studentList.get(j).SrNo)) {
          empty = false;
          System.out.println("Name: " + studentList.get(j).name);
        }
      }
    }
    if (empty) {
      System.out.println("No student found !!");
    }
  }

}

class FacultyData {
  ArrayList<Factulty> facultyList = new ArrayList<Factulty>();

  FacultyData() {
    setFacultyData();
  }

  void setFacultyData() {
    try {
      facultyList.clear();
      BufferedReader br = new BufferedReader(new FileReader("files/faculty.txt"));
      String line = br.readLine();
      String array[] = new String[3];
      while (line != null) {
        for (int i = 0; i < 2; i++) {
          array[i] = line.substring(0, line.indexOf(","));
          line = line.substring(line.indexOf(",") + 1);
        }
        array[2] = line;
        facultyList.add(new Factulty(array[0], array[1], array[2]));
        line = br.readLine();
      }
      br.close();
    } catch (Exception e) {
      System.out.println(e);
    }
  }

  // Question 5
  void printFaculty(String depart) {
    boolean empty = true;
    System.out.print("\n");
    for (int i = 0; i < facultyList.size(); i++) {
      if (facultyList.get(i).depart.equals(depart)) {
        empty = false;
        System.out.println("Name: " + facultyList.get(i).name);
      }
    }
    if (empty) {
      System.out.println("No faculty found with this department code !!");
    }
  }

}

class Enrolled {

  // Question 3
  ArrayList<String> getEnrolled(String course) {
    ArrayList<String> enrolled = new ArrayList<String>();
    try {
      BufferedReader br = new BufferedReader(new FileReader("files/enrolled.txt"));
      String line = br.readLine();
      String array[] = new String[2];
      while (line != null) {
        array[0] = line.substring(0, line.indexOf(","));
        line = line.substring(line.indexOf(",") + 1);
        array[1] = line;
        if (array[1].equals(course)) {
          enrolled.add(array[0]);
        }
        line = br.readLine();
      }
      br.close();
    } catch (Exception e) {
      System.out.println(e);
    }
    return enrolled;
  }
}

public class manager {
  public static Scanner sc = new Scanner(System.in);

  public static void main(String[] args) {
    while (true) {
      System.out.println("\n======= MENU =======");
      System.out.println(
          "1. Print Student Name and Age\n2. Filter Students based on Age\n3. Find Student Sr No. based on course enrolled\n4. Find name of student enrolled for course\n5. List Factulty Members belonging to department\n6. Exit\n");
      System.out.print("Enter your choice : ");
      int choice = sc.nextInt();

      if (choice == 1) {
        StudentData sd = new StudentData();
        sd.prStudent();
      } else if (choice == 2) {
        System.out.print("Enter the age: ");
        int age = sc.nextInt();
        StudentData sd = new StudentData();
        sd.printStudent(age);
      } else if (choice == 3) {
        System.out.print("Enter the course name: ");
        sc.nextLine();
        String course = sc.nextLine();
        Enrolled e = new Enrolled();
        ArrayList<String> enrolled = e.getEnrolled(course);
        System.out.print("\n");
        if (enrolled.size() == 0) {
          System.out.println("No student enrolled for this course !!");
        }
        for (int i = 0; i < enrolled.size(); i++) {
          System.out.println("SrNo: " + enrolled.get(i));
        }
      } else if (choice == 4) {
        System.out.print("Enter the course name: ");
        sc.nextLine();
        String course = sc.nextLine();
        Enrolled e = new Enrolled();
        ArrayList<String> enrolled = e.getEnrolled(course);
        StudentData sd = new StudentData();
        sd.srToName(enrolled);
      } else if (choice == 5) {
        System.out.print("Enter the department Code: ");
        String code = sc.next();
        FacultyData fd = new FacultyData();
        fd.printFaculty(code);
      } else if (choice == 6) {
        break;
      } else {
        System.out.println("Invalid Choice !!");
      }
    }
  }
}
