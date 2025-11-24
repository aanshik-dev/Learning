	package MyPackage;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStreamReader;

public class InputFromConsole {
	public static void main(String[] args) {
		try {
			InputStreamReader f=new InputStreamReader(System.in);
			BufferedReader bf=new BufferedReader(f);
			
			System.out.print(bf.readLine()+"\n");
				
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}catch (IOException e)
		{
			e.printStackTrace();
			
		}
		
	}

}
