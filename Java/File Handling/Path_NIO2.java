package MyPackage;
import java.io.*;
import java.nio.file.*; 
import java.nio.file.LinkOption;

public class Path_NIO2 {
    public static void main(String[] args) {
        try {
            // Create a Path object for the file
            Path filePath = Paths.get("C:\\FilesList\\newFile.txt");

            // Create the file if it doesn't exist
            if (!Files.exists(filePath)) {
                Files.createFile(filePath);
                System.out.println("File created: " + filePath.toAbsolutePath());
                Files.writeString(filePath, "Hello, NIO!");
            } else {
                System.out.println("File already exists: " + filePath.toAbsolutePath());
            }

            // Create a Path object for the directory
            Path dirPath = Paths.get("C:\\FilesList\\myDir");

            // Create the directory if it doesn't exist
            if (!Files.exists(dirPath)) {
                Files.createDirectory(dirPath);
                System.out.println("Directory created: " + dirPath.toAbsolutePath());
            } else {
                System.out.println("Directory already exists: " + dirPath.toAbsolutePath());
            }

        } catch (IOException e) {
            System.out.println("An error occurred: " + e.getMessage());
        }
    }
}
