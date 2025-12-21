package MyPackage;

import java.io.IOException;
import java.nio.file.*;

public class Path_NIO3 {
	public static void main(String[] args) {
        // Define source and destination paths
        Path source = Paths.get("C:\\FilesList\\CS202.txt");
        Path destination = Paths.get("C:\\FilesList\\newFile.txt");

        try {
            // Copy the file (replace if it already exists)
            Files.copy(source, destination);
            System.out.println("File copied successfully!");
        } catch (IOException e) {
            System.out.println("Error copying file: " + e.getMessage());
        }
    }

}
