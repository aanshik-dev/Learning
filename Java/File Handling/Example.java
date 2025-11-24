package MyPackage;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Example {
  public static void main(String[] args) throws IOException {
    // Creating a file

    File f = new File("C:\\FilesList\\CS202.txt");
    f.createNewFile();

    System.out.println(f.exists());
    System.out.println(f.getName());
    System.out.println(f.getAbsolutePath());
    System.out.println("Can we write? " + f.canWrite());
    System.out.println("Can we read? " + f.canRead());
    System.out.println("Length of the file " + f.length());

    // Writing some lines to the created file
    // FileWriter is a character-oriented stream

    try {
      FileWriter f1 = new FileWriter("C:\\FilesList\\CS202.txt");
      f1.write("Writing the first line\nSecond line\nThird line");
      f1.flush();
      f1.close();
    }

    catch (IOException e) { // TODO Auto-generated catch block
      e.printStackTrace();
    }

    // Reading lines from the created file

    File f2 = new File("C:\\FilesList\\CS202.txt");
    Scanner sc1 = new Scanner(f2);
    // Scanner sc2 = new Scanner(f2);

    while (sc1.hasNextLine()) {
      System.out.println(sc1.nextLine());
    }

    // while(sc2.hasNext()) {
    // System.out.println(sc2.next()); }

    // File f=new File("CS202.txt");
    // f.createNewFile();

    // if(f.delete())
    // {
    // System.out.println("The file with name CS202.txt is successfully deleted"); }
    // else {
    // System.out.println("Some problem occurred while trying to delete the file");
    // }

  }

}
