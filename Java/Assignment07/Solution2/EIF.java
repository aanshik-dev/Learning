interface Driver {
  int driveCar();

  int driveBike();
}

interface Singer {
  int riyaz();

  int sing();
}

class Person {
  int age;

  Person(int age) {
    this.age = age;
  }

  void eat() {
    System.out.println("Person Eating");
  }

  void sleep() {
    System.out.println("Person Sleeping");
  }
}

class Employee extends Person implements Driver, Singer {

  public Employee(int age) {
    super(age);
  }

  int officeWork() {
    if (age < 40) {
      return 20;
    } else {
      return 10;
    }
  }

  public int driveCar() {
    if (age < 40) {
      return 10;
    } else {
      return 0;
    }
  }

  public int driveBike() {
    if (age < 40) {
      return 5;
    } else {
      return 0;
    }
  }

  public int sing() {
    if (age < 20) {
      return 15;
    } else {
      return 0;
    }
  }

  public int riyaz() {
    if (age < 20) {
      return 25;
    } else {
      return 0;
    }
  }

}

public class EIF {
  public static void sort(Employee[] emp, int[] ifactor) {
    for (int i = 0; i < emp.length; i++) {
      for (int j = i + 1; j < emp.length; j++) {
        if (ifactor[i] > ifactor[j]) {
          int temp1 = ifactor[i];
          ifactor[i] = ifactor[j];
          ifactor[j] = temp1;
          Employee temp2 = emp[i];
          emp[i] = emp[j];
          emp[j] = temp2;
        }
      }
    }
  }

  public static void main(String[] args) {
    Employee emp[] = new Employee[5];
    emp[0] = new Employee(18);
    emp[1] = new Employee(50);
    emp[2] = new Employee(25);
    emp[3] = new Employee(45);
    emp[4] = new Employee(35);

    int eif[] = new int[5];
    for (int i = 0; i < emp.length; i++) {
      eif[i] = emp[i].driveCar() + emp[i].driveBike() + emp[i].sing() + emp[i].officeWork();
    }

    for (int i = 0; i < emp.length; i++) {
      System.out.println("EIF:" + eif[i] + " Age:" + emp[i].age + " Car:" + emp[i].driveCar() + " Bike:"
          + emp[i].driveBike() + " Sing:" + emp[i].sing() + " Work:" + emp[i].officeWork());
    }

    sort(emp, eif);
    System.out.println("");

    for (int i = 0; i < emp.length; i++) {
      System.out.println("EIF:" + eif[i] + " Age:" + emp[i].age + " Car:" + emp[i].driveCar() + " Bike:"
          + emp[i].driveBike() + " Sing:" + emp[i].sing() + " Work:" + emp[i].officeWork());
    }
  }

}
