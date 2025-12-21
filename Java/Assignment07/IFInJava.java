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

public class IFInJava {

  public static void main(String[] args) {
    Driver d = new Employee(30);
    System.out.println(d.driveCar());
    System.out.println(d.driveBike());
    // System.out.println(d.officeWork());
    // System.out.println(d.sing());
    // System.out.println(d.riyaz());

    Singer s = new Employee(30);
    System.out.println(s.sing());
    System.out.println(s.riyaz());
    // System.out.println(s.officeWork());
    // System.out.println(s.driveBike());
    // System.out.println(s.driveCar());
  }

}
