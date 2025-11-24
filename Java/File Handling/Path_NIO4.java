package MyPackage;

import java.io.IOException;
import java.nio.file.*;
import java.util.List;

public class Path_NIO4 {
    public static void main(String[] args) {
        Path filePath = Paths.get("C:\\FilesList\\CS202.txt");

        try {
            List<String> lines = Files.readAllLines(filePath);

            System.out.println("Contents of the file:");
            for (String line : lines) {
                System.out.println(line);
            }

        } catch (IOException e) {
            System.out.println("Error reading file: " + e.getMessage());
        }
    }
}
