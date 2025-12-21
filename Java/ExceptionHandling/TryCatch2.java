//Using multiple catch
package MyPackage;

import java.util.Scanner;

public class TryCatch2 {
	public static void main(String[] args) {
		int[] array=new int[3];
		
		array[0]=18;
		array[1]=8;
		array[2]=22;
	
		Scanner sc=new Scanner(System.in);
		System.out.println("Enter the array index");
		int ind=sc.nextInt();
		
		System.out.println("Enter divisor");
		int divisor=sc.nextInt();
		
		try {
			System.out.println("Array[index]/divisor = "+ array[ind]/divisor);
			//System.out.println(array[1]);
		}
		catch(Exception e)
		{
			System.out.println("Other exception "+e);
		}
		
		
		
		System.out.println("Finallllll ");
		
		
	}

}
