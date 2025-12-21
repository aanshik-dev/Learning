package MyPackage;

import java.util.Scanner;

public class TryCatch1 {

	public static void main(String[] args) {
		int k;
		Scanner sc=new Scanner(System.in);
		k=sc.nextInt();
		
		try {
			System.out.println("100/k=" + 100/k);
			System.out.println("Second statement");
		}
		catch(Exception e)
		{
			System.out.println("Encountered an exception");
			System.out.println("Which is "+e);
		}
	
		System.out.println("Finished");
		 
	}

}
