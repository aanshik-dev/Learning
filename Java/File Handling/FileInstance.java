package MyPackage;
import java.io.File;

public class FileInstance {
	public static void main(String[] args) {
		//File file = new File ("C:\\Users\\Arijit\\eclipse-workspace\\FileHandling\\FilesByArijit");
		File file = new File ("C:\\FilesList");
		
		String[] paths=file.list();
		
		for(String str:paths) {
			System.out.println(str);
		}
	
	}

}
