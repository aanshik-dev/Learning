package MyPackage;
import java.io.*;

public class ExampleDeserialization {
	public static void main(String[] args) throws IOException, ClassNotFoundException {
		FileInputStream f=new FileInputStream("Serial.txt");
		ObjectInputStream oin=new ObjectInputStream(f);
		
		Employee e=(Employee)oin.readObject();
		
		System.out.println("Name = "+e.name);
		System.out.println("Emp id = "+e.emp_id);
		
	}

}
