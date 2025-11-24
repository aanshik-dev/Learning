package ExceptionHandling;

public class EndSem2 {

    public static void main(String[] args) {
        try {
            System.out.println("In outer try block");
            try {
                System.out.println("In inner try block");
                throw new ArithmeticException("Inner exception");
            } catch (ArithmeticException ae) {
                System.out.println("Caught in inner catch: " + ae.getMessage());
                throw new NullPointerException("Exception from inner catch");
            } finally {
                System.out.println("Finally block of inner try-catch");
            }
        } catch (Exception e) {
            System.out.println("Caught in outer catch: " + e.getMessage());
            throw new RuntimeException("Exception from outer catch");
        } finally {
            System.out.println("Finally block of outer try-catch");
        }
    }
}
