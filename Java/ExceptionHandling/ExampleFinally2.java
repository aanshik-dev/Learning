package ExceptionHandling;

public class ExampleFinally2 {

	public static void main(String[] args) {
		int a=8;
		int b=4;
		
		while(true)
		{
			try {
				System.out.println("a= "+a+" b= "+b+ " a/b = "+a/b);
			}
			catch(Exception e)
			{
				System.out.println(e);
				break;
			}
			finally {
				System.out.println("Finally value of b = "+b);
				b--;
				//return;
			}
				
		}
		
		
	}

}
