package MyPackage;

import java.util.Scanner;

class NegativeRadiusException2 extends Exception{
	@Override
	public String toString() {
		return "Negative radius is provided";
	}
	public String getMessage() {
		return "Getting the message";
	}
}

class throwsClass2{
	public static double area(int r){
		return Math.PI*r*r;
		}
}

public class ExampleThrows2 {
	public static void main(String[] args) {
		System.out.println("Please input the radius of the circle");
		Scanner sc=new Scanner(System.in);
		int r=sc.nextInt();
		
		try {
			if(r<0)
			{
				throw new NegativeRadiusException2();
			}
			
			System.out.println("Area of circle = "+throwsClass2.area(r));
		}
		catch (NegativeRadiusException2 e)
		//catch(ArrayIndexOutOfBoundsException e)
		{
			System.out.println(e.toString()); 
			System.out.println(e.getMessage()); 
			
		}
		 
		
		System.out.println("End of the program");
		
	}

}
