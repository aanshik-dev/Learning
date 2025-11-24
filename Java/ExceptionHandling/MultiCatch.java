package MyPackage;

public class MultiCatch {
	public static void main(String[] args) {
		try {
			int a[]=new int[5];
			a[3]=30/0;
			System.out.println(a[10]);			
		}
		catch(ArithmeticException e) {
			System.out.println("Arithmatic Exception occurs");	
		}
		catch(ArrayIndexOutOfBoundsException e) {
			System.out.println("Array Index Out Of Bounds Exception occurs");
		}
		catch(Exception e) {
			System.out.println("Exception occurs");
		}
	}

}
