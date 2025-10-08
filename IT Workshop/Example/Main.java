class SuperParent {
  int x = 10;
  static {
    System.out.print("S1");
  }

  public SuperParent() {
    System.out.print("P" + x);
  }

  public void display() {
    System.out.print("D" + x);
  }
}

class Child extends SuperParent {
  int x = 20;
  static {
    System.out.print("S2");
  }
  { 
    System.out.print("I" + x);
  }

  public Child() {
    this(5);
    System.out.print("C1");
  }

  public Child(int x) {
    super();
    this.x = x + this.x;
    System.out.print("C2");
  }

  @Override
  public void display() {
    super.display();
    System.out.print("D" + this.x);
  }
}

public class Main {
  public static void main(String[] args) {
    Child c = new Child();
    c.display();
  }
}