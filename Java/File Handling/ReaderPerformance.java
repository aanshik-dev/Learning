package MyPackage;
import java.io.*;

public class ReaderPerformance {
	public static void main(String[] args) {
        String filePath = "C:\\FilesList\\Attendance_S21.txt"; // use any large text file

        // -------- FileReader Test --------
        try {
	            FileReader fr = new FileReader(filePath);
	            long start1 = System.currentTimeMillis();

	            int ch;
	            while ((ch = fr.read()) != -1) {}

	            long end1 = System.currentTimeMillis();
	            fr.close();

	            System.out.println("Time taken using FileReader: " + (end1 - start1) + " ms");

        } catch (IOException e) {
            System.out.println("Error using FileReader: " + e.getMessage());
        }

        try {
	            BufferedReader br = new BufferedReader(new FileReader(filePath));
	            long start2 = System.currentTimeMillis();

	            while (br.read() != -1) {}

	            long end2 = System.currentTimeMillis();
	            br.close();

	            System.out.println("Time taken using BufferedReader: " + (end2 - start2) + " ms");

        } catch (IOException e) {
            System.out.println("Error using BufferedReader: " + e.getMessage());
        }
    }
	


}
