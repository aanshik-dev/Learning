package MyPackage;

import java.io.IOException;

public class IOStreamsExamples {
	public static void main(String[] args) {
		try {
			int i=System.in.read();
			System.out.println(i);
		} catch (IOException e) {
			e.printStackTrace();
		}
		
	
	
	}

}
