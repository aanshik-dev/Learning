package MyPackage;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.util.Scanner;

public class ReadFromFile {
	public static void main(String[] args) {
		
		try {
			File myFile=new File("TrialFile.txt");
			Scanner sc = new Scanner(myFile);
			
			while(sc.hasNextLine())
				 System.out.println(sc.nextLine());
			
			sc.close();
		} 
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
	
	}

}
