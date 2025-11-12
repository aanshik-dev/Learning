import java.io.*;
import java.util.*;

class fileThread extends Thread {
  String fileName;
  String folder;
  String output;
  private static Object lock = new Object();
  int students = 0;
  int highest = 0;
  int lowest = 100;
  float average = 0;

  public fileThread(String fileName, String output, String folder) {
    this.fileName = fileName;
    this.output = output;
    this.folder = folder;
  }

  public void run() {
    ArrayList<Integer> marks = new ArrayList<Integer>();

    try {
      FileReader file = new FileReader(folder + fileName);
      BufferedReader br = new BufferedReader(file);
      String line;
      while ((line = br.readLine()) != null) {
        if (!line.isEmpty()) {
          marks.add(Integer.parseInt(line));
        }
      }
      br.close();
    } catch (IOException e) {
      System.err.println(e);
    }

    for (int i = 0; i < marks.size(); i++) {
      students++;
      if (marks.get(i) > highest) {
        highest = marks.get(i);
      }
      if (marks.get(i) < lowest) {
        lowest = marks.get(i);
      }
      average += marks.get(i);
    }
    average /= students;
    System.out
        .println(String.format(
            "Class: %s | Students: %d | Highest: %d | Lowest: %d | Average: %.2f",
            fileName, students, highest, lowest, average));
    synchronized (lock) {
      try {
        FileWriter fw = new FileWriter(folder + output, true);
        fw.write(String.format(
            "Class: %s | Students: %d | Highest: %d | Lowest: %d | Average: %.2f%n",
            fileName, students, highest, lowest, average));
        fw.close();
      } catch (IOException e) {
        System.err.println(e);
      }
    }
  }
}

public class MultiThread {

  public static void main(String[] args) {

    int files = 3 + (int) (Math.random() * 10) % 4;
    String output = "MarksSummary.txt";
    String folder = "Files\\";
    createFile(files, folder);
    String[] filenames = new String[files];
    for (int i = 0; i < files; i++) {
      String fileName = "class" + (char) ('A' + i) + ".txt";
      filenames[i] = fileName;
    }

    try {
      FileWriter fw = new FileWriter(folder + output);
      fw.close();
    } catch (IOException e) {
      System.err.println(e);
    }

    fileThread[] threads = new fileThread[files];
    for (int i = 0; i < files; i++) {
      threads[i] = new fileThread(filenames[i], output, folder);
      threads[i].start();
    }

    for (int i = 0; i < files; i++) {
      try {
        threads[i].join();
      } catch (InterruptedException e) {
        System.err.println(e);
      }
    }

    System.out.println("\nAll class records processed successfully. MarksSummary.txt is ready.\n");
  }

  public static void createFile(int files, String folder) {
    System.out.println("\nNumber of files created: " + files + "\n");
    File dir = new File(folder);
    if (dir.exists()) {
      for (File file : dir.listFiles()) {
        if (!file.isDirectory()) {
          file.delete();
        }
      }
    } else {
      dir.mkdirs(); // Create if not exists
    }
    for (int i = 0; i < files; i++) {
      String fileName = "class" + (char) ('A' + i) + ".txt";
      try {
        FileWriter fw = new FileWriter(folder + fileName);
        int students = 3 + (int) (Math.random() * 10) % 7;
        for (int j = 0; j < students; j++) {
          fw.write((20 + (int) (Math.random() * 80)) + "\n");
        }
        fw.close();
      } catch (IOException e) {
        System.err.println(e);
      }
    }
  }
}