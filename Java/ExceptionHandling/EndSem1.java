public class EndSem1 {
  public static void main(String[] args) {
    try {
      System.out.println("In outer try block");
      throw new Exception();
    } catch (Exception e) {
      System.out.println("Caught in outer catch");
      try {
        System.out.println("In inner try block");
        throw new RuntimeException();
      } catch (RuntimeException re) {
        System.out.println("Caught in inner catch");
        return;
      } finally {
        System.out.println("Finally block of inner try-catch");
        return;
      }
    } finally {
      System.out.println("Finally block of outer try-catch");
    }
  }
}
