package MyPackage;

import java.util.Scanner;

public class TryCatch3 {
	public static void main(String[] args) {
		int[] array=new int[3];
		array[0]=18;
		array[1]=8;
		array[2]=22;
	
		Scanner sc=new Scanner(System.in);
		System.out.println("Enter index value ");
		int ind=sc.nextInt();
		
		System.out.println("Enter divisor");
		int divisor=sc.nextInt();
		
		try {
			System.out.println("Checking index value");
			
			try {
				System.out.println("Element at index inx "+array[ind]);
				System.out.println("yyy "+10/divisor);
				
			}
			catch(ArrayIndexOutOfBoundsException e) {
				System.out.println("Hii...Array out of bound Exception "+e);
			}
		}
		catch(Exception e)
		{
			System.out.println("Other exception "+e);
		
		
		}
	
	
	}

}
