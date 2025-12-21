package MyPackage;

import java.util.Scanner;

class NegativeRadiusException extends Exception{
	@Override
	public String toString() {
		return "Negative radius is provided";
	}
	public String getMessage() {
		return "Getting the message";
	}
}

class throwsClass{
	public static double area(int r) throws NegativeRadiusException{
		if(r<0) {
			throw new NegativeRadiusException();
		}
			
		return Math.PI*r*r;
		}
}

public class ExampleThrows {
	public static void main(String[] args) {
		System.out.println("Please input the radius of the circle");
		Scanner sc=new Scanner(System.in);
		int r=sc.nextInt();
		
		try{ 
			System.out.println("Area of circle = "+throwsClass.area(r));
		}
		catch(NegativeRadiusException e) 
		{ 
			System.out.println(e.toString()); 
		}
		 
		
		System.out.println("End of the program");
		
	}

}
