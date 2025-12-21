//This program takes out of bound indices continuously
//until the valid input is fed

package MyPackage;


import java.util.Scanner;

public class TryCatch4 {
	public static void main(String[] args) {
		int[] array=new int[3];
		array[0]=18;
		array[1]=8;
		array[2]=22;
	
		Scanner sc=new Scanner(System.in);
		int flag=1;
		
		while(flag==1) {
			try {
				System.out.println("Enter index value ");
				int ind=sc.nextInt();
				
				if(ind>(array.length-1))
				{	
					flag=0;
					System.out.println("Element at index ind "+array[ind]);
				}
				else
				{
					System.out.println("Array element at index "+ind+" = "+array[ind]);
				}
								
			}
			catch(ArrayIndexOutOfBoundsException e)
			{
				System.out.println("Bound exception "+e);
			}
			
			
		}
		
		System.out.println("Program ended sucessfully");
	
	}

}
