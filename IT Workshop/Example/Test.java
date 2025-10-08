
class Base {
  public static void main(String[] args) {
    System.out.println("Running main() from the Base class.");
    // This line confirms that Base is the superclass
    Test t = new Test();
    t.testMethod();
  }

  public void testMethod() {
    System.out.println("Base's testMethod() called.");
  }
}

public class Test extends Base {
  // Test inherits main from Base, but we will not define a main here.

  // @Override
  // public void testMethod() {
  //   System.out.println("Test's overridden testMethod() called.");
  // }
}