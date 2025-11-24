package MyPackage;

import java.io.FileWriter;
import java.io.IOException;

public class WriteToFile {

	public static void main(String[] args) {
		//Writing to a file 
		try {
				FileWriter fileWrite=new FileWriter("outsss.txt");
				fileWrite.write("1st line\nsecond line");
				System.out.println("Writing to the file");
				fileWrite.close();
				
			} 
		catch (IOException e) {
					e.printStackTrace();
			}

	}

}
