package MyPackage;
import java.io.IOException;
import java.nio.file.*;

public class Path_NIO1 {
	public static void main(String[] args) {
	    Path path = Paths.get("C:\\FilesList\\CS202_output.txt");
	    try {
			Files.createFile(path);
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	    System.out.println("File Name : "+path.getFileName());   
	    System.out.println("Root : "+path.getRoot());     
	    System.out.println("Parent : "+path.getParent());     
	    System.out.println("Absolute Path : "+path.toAbsolutePath()); 
	}

}
