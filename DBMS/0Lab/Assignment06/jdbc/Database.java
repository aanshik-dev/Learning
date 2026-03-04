import java.sql.*;
import java.util.*;

public class Database {

  static String url = "jdbc:mysql://localhost:3306/lab";
  static String username = "root";
  static String pass = "Aanshik@4632";

  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    try {
      Connection conn = DriverManager.getConnection(url, username, pass);

      while (true) {
        System.out.println("\n===== MENU =====");
        System.out.println("1. Show Tables");
        System.out.println("2. Print Classes in Room");
        System.out.println("3. Print Course Room & Time");
        System.out.println("4. Print Faculty Courses");
        System.out.println("5. Exit");
        System.out.print("Enter choice: ");

        int choice = sc.nextInt();
        sc.nextLine();

        switch (choice) {
          case 1:
            showTables(conn, sc);
            break;
          case 2:
            queryA(conn, sc);
            break;
          case 3:
            queryB(conn, sc);
            break;
          case 4:
            queryC(conn, sc);
            break;
          case 5:
            conn.close();
            System.out.println("\nTerminating...");
            return;
          default:
            System.out.println("Invalid choice !!");
        }
      }

    } catch (Exception e) {
      System.out.println("Connection Error: " + e.getMessage());
    }
  }

  public static void showTables(Connection conn, Scanner sc) {
    try {
      DatabaseMetaData metaData = conn.getMetaData();
      ResultSet rs = metaData.getTables("lab", null, "%", new String[] { "TABLE" });
      System.out.println("\nTables in Lab DB:");
      while (rs.next()) {
        System.out.println(" >> " + rs.getString("TABLE_NAME"));
      }

      System.out.print("Enter table name: ");
      String table = sc.nextLine();

      Statement stmt = conn.createStatement();
      ResultSet tableData = stmt.executeQuery("SELECT * FROM " + table);
      ResultSetMetaData tableMeta = tableData.getMetaData();
      int cols = tableMeta.getColumnCount();

      for (int i = 1; i <= cols; i++) {
        System.out.print(tableMeta.getColumnName(i) + "    ");
      }
      System.out.println();
      while (tableData.next()) {
        for (int i = 1; i <= cols; i++) {
          System.out.print(tableData.getString(i) + "    ");
        }
        System.out.println();
      }

    } catch (SQLException e) {
      System.out.println("SQL Error: " + e.getMessage());
    }
  }

  public static void queryA(Connection conn, Scanner sc) {
    try {
      System.out.print("Enter room name: ");
      String room = sc.nextLine();

      PreparedStatement ps = conn.prepareStatement(
          "SELECT name FROM Class WHERE room = ?");

      ps.setString(1, room);
      ResultSet rs = ps.executeQuery();

      System.out.println("\nClasses in room " + room + ":");
      boolean flag = false;
      while (rs.next()) {
        flag = true;
        System.out.println(rs.getString(1));
      }
      if (!flag) {
        System.out.println("No classes found in room " + room);
      }

    } catch (SQLException e) {
      System.out.println("SQL Error: " + e.getMessage());
    }
  }

  public static void queryB(Connection conn, Scanner sc) {
    try {
      System.out.print("Enter course name: ");
      String course = sc.nextLine();

      PreparedStatement ps = conn.prepareStatement(
          "SELECT room, meets_at FROM Class WHERE name = ?");

      ps.setString(1, course);
      ResultSet rs = ps.executeQuery();

      boolean flag = false;
      while (rs.next()) {
        flag = true;
        System.out.println("Room: " + rs.getString("room") +
            " | Time: " + rs.getString("meets_at"));
      }
      if (!flag) {
        System.out.println("No classes found for course " + course);
      }

    } catch (SQLException e) {
      System.out.println("SQL Error: " + e.getMessage());
    }
  }

  public static void queryC(Connection conn, Scanner sc) {
    try {
      System.out.print("Enter faculty name: ");
      String fname = sc.nextLine();

      PreparedStatement ps = conn.prepareStatement(
          "SELECT Class.name FROM Class JOIN Faculty ON Class.fid = Faculty.fid WHERE Faculty.fname = ?");

      ps.setString(1, fname);
      ResultSet rs = ps.executeQuery();

      System.out.println("\nCourses taught by " + fname + ":");
      boolean flag = false;
      while (rs.next()) {
        flag = true;
        System.out.println(rs.getString("name"));
      }
      if (!flag) {
        System.out.println("No courses found for faculty " + fname);
      }

    } catch (SQLException e) {
      System.out.println("SQL Error: " + e.getMessage());
    }
  }
}