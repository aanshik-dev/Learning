import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class Example_Stream2 {
	public static void main(String[] args){
		
		try {
			FileInputStream fin= new FileInputStream("CS202.txt");
			int i=fin.read();
			while(i!=-1) {
				System.out.print((char)i);
				System.out.println(i);
				
				i=fin.read();
			
			}
			
			fin.close();
			
			
		} catch (IOException e) {
			e.printStackTrace();
		}
	
	
	}
}
