package MyPackage;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class JavaStreamExample3 {
	public static void main(String[] args) {
		try {
			FileReader f=new FileReader("Input.txt");
			BufferedReader bf=new BufferedReader(f);
			
			System.out.print(bf.readLine()+"\n");
			System.out.print(bf.readLine()+"\n");
			System.out.print(bf.readLine()+"\n");
			
			
		
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}catch (IOException e)
		{
			e.printStackTrace();
			
		}
		
	}

}
