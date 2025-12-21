package ExceptionHandling;

class finallyExample{
	public static int fun() {
		try {
			int a =9;
			int b=0;
			int c=(a/b);
			System.out.println("ABCCCCC");
			return c;
		}
		catch(Exception e)
		{
			System.out.println("Class s2222 "+e);
			return 3;
		}
		finally {
			System.out.println("Cleaning up the resources");
			return 14;
		}
		
	//tem.out.println("Outside finally ::: Cleaning up the resources");
		//System.out.println("Afrer finally");
		//return 2;
	}
	
	
}
public class ExampleFinally1 {
	public static void main(String[] args) {
		System.out.println(finallyExample.fun());
	}
}




