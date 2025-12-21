class MyException extends Exception {
  @Override
  public String toString() {
    return "Overriden toString()";
  }

  @Override
  public String getMessage() {
    return "Overriden getMesssage()";
  }

}

public class CustomException {
  public static void main(String[] args) {
    int a = 13;

    if (a < 9) {
      try {
        throw new MyException();
      } catch (Exception e) {
        System.out.println(e);
        System.out.println(e.toString());
        System.out.println(e.getMessage());
      }

    }

    System.out.println("Program ended");

  }

}
