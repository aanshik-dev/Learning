package MyPackage;

import java.io.BufferedOutputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

public class JavaExampleStream4 {
	public static void main(String[] args) {
		try {
			FileOutputStream fout=new FileOutputStream("Test.txt");
			BufferedOutputStream bout=new BufferedOutputStream(fout);
			
			String s="Happy Puja Vacation";
			byte b[]=s.getBytes();
			bout.write(b);
			bout.flush();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}catch(IOException e)
		{
			e.printStackTrace();
		}
		
		
		
		
	}

}
