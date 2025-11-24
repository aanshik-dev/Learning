package MyPackage;
import java.io.*;

public class JavaStreamExample2 {
	public static void main(String[] args) {
		try {
			FileReader in=new FileReader("C:\\FilesList\\Doc1.pdf");
			FileWriter out=new FileWriter("C:\\FilesList\\Doc2.pdf");
			int c;
			
			while((c=in.read())!=-1)
			{
				//System.out.println((char)c);
				out.write(c);
			}
			//out.close();
			out.flush();
			
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		}
		
		
	}

}
