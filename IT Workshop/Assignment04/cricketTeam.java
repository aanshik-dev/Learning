import java.util.Scanner;

class Coach {
  private static int counter = 0;
  private String name;
  private String coachId;

  private Coach() {
    counter++;
    System.out.println("Coach Added Successfully !!");
  }

  public static Coach createCoach(String name, String coachId) {
    if (counter >= 2) {
      System.out.println("Warning !! Maximum coach limit reached !!");
      return null;
    } else {
      Coach coach = new Coach();
      coach.name = name;
      coach.coachId = coachId;
      return coach;
    }
  }

  @Override
  public String toString() {
    return "Coach Name : " + this.name + " " + "Coach ID : " + this.coachId;
  }

  public String getName() {
    return this.name;
  }

  public String getId() {
    return this.coachId;
  }

  public void updateName(String name) {
    this.name = name;
  }
}

class Player {
  Scanner sc = new Scanner(System.in);
  private String name;
  private int jersyNo;
  private double battingAverage;
  private Coach coach;
  private String role;
  // private static int teamCode = 718;

  public Player() {
  }

  public Player(Coach Coach, int jn) {
    System.out.print("Enter Player Name: ");
    this.name = sc.next();
    this.jersyNo = jn;
    System.out.print("Enter Player Batting Average: ");
    this.battingAverage = sc.nextDouble();
    System.out.print("Enter Player Role: ");
    this.role = sc.next();
    this.coach = Coach;
    System.out.println("Player Added Successfully !!");
  }

  public void updatePlayerRecord() {
    System.out.print("Enter Player Name: ");
    this.name = sc.next();
    System.out.print("Enter Player new Jersy Number: ");
    this.jersyNo = sc.nextInt();
    System.out.print("Enter Player Batting Average: ");
    this.battingAverage = sc.nextDouble();
    System.out.print("Enter Player Role: ");
    this.role = sc.next();
  }

  public void getPlayerDetails() {
    System.out.println("Player Name: " + this.name);
    System.out.println("Player Jersy Number: " + this.jersyNo);
    System.out.println("Player Batting Average: " + this.battingAverage);
    System.out.println("Player Role: " + this.role);
    System.out.println("Coach Name: " + this.coach.getName());
  }

  public void getCoach() {
    System.out.println("Coach Name: " + this.coach.getName());
    System.out.println("Coach ID: " + this.coach.getId());
  }

  public int getJN() {
    return this.jersyNo;
  }

}

// Driver Class
public class cricketTeam {
  public static Scanner sc = new Scanner(System.in);
  private static Player player[] = new Player[5];
  private static Coach coach[] = new Coach[2];
  private static int cptr = 0;
  private static int pptr = 0;

  private static int searchCoach(String id) {
    int idx = -1;
    for (int i = 0; i < cptr; i++) {
      if (coach[i].getId().equals(id)) {
        idx = i;
      }
    }
    return idx;
  }

  private static int searchPlayer(int id) {
    int idx = -1;
    for (int i = 0; i < pptr; i++) {
      if (player[i].getJN() == id) {
        idx = i;
      }
    }
    return idx;
  }

  public static void addPlayer() {
    if (pptr < 5) {
      System.out.print("Enter Jersy Number: ");
      int jn = sc.nextInt();
      int is = searchPlayer(jn);
      if (is == -1) {
        System.out.print("Enter Coach ID: ");
        String id = sc.next();
        int idx = searchCoach(id);
        if (idx != -1) {
          player[pptr] = new Player(coach[idx], jn);
          pptr++;
        } else {
          System.out.println("Coach ID does not exists !!");
        }
      } else {
        System.out.println("Player already exists !!");
      }
    } else {
      System.out.println("Maximum Player Limit reached !!");
    }
  }

  public static void deletePlayer() {
    if (pptr > 0) {
      System.out.print("Enter Jersy Number: ");
      int jn = sc.nextInt();
      int is = searchPlayer(jn);
      if (is != -1) {
        for (int i = is; i < pptr - 1; i++) {
          player[i] = player[i + 1];
        }
        pptr--;
        System.out.println("Player Deleted Successfully !!");
      } else {
        System.out.println("Player does not exist !!");
      }
    } else {
      System.out.println("Player Database is Empty !!");
    }
  }

  public static void addCoach() {
    if (cptr < 2) {
      System.out.print("Enter the Coach ID: ");
      String id = sc.next();
      int is = searchCoach(id);
      if (is == -1) {
        System.out.print("Enter Coach Name: ");
        String name = sc.next();
        Coach c = Coach.createCoach(name, id);
        if (c != null) {
          coach[cptr] = c;
          cptr++;
        }
      } else {
        System.out.println("Coach ID already exists !!");
      }
    } else {
      System.out.println("Maximum Coach Limit reached !!");
    }
  }

  public static void updateCoach() {
    if (cptr > 0) {
      System.out.print("Enter Coach ID: ");
      String id = sc.next();
      int is = searchCoach(id);
      if (is != -1) {
        System.out.print("Enter Coach Name: ");
        String name = sc.next();
        coach[is].updateName(name);
        System.out.println("Coach Updated Successfully !!");
      } else {
        System.out.println("Coach does not exist !!");
      }
    } else {
      System.out.println("Coach Database is Empty !!");
    }
  }

  public static void updatePlayer() {
    if (pptr > 0) {
      System.out.print("Enter Jersy Number: ");
      int jn = sc.nextInt();
      int is = searchPlayer(jn);
      if (is != -1) {
        player[is].updatePlayerRecord();
        System.out.println("Player Updated Successfully !!");
      } else {
        System.out.println("Player does not exist !!");
      }
    } else {
      System.out.println("Player Database is Empty !!");
    }
  }

  public static void deleteCoach() {
    if (cptr > 0) {
      System.out.print("Enter Coach ID: ");
      String id = sc.next();
      int is = searchCoach(id);
      if (is != -1) {
        for (int i = is; i < cptr - 1; i++) {
          coach[i] = coach[i + 1];
        }
        cptr--;
        System.out.println("Coach Deleted Successfully !!");
      } else {
        System.out.println("Coach does not exist !!");
      }
    } else {
      System.out.println("Coach Database is Empty !!");
    }
  }

  public static void main(String[] args) {

    while (true) {
      int choice;
      System.out.println(
          "\n======= MENU =======\n1: Add Player\n2: Delete Player\n3: Add Coach\n4: Delete Coach\n5: Update Player\n6: Update Coach\n7: Display Player Details\n8: Display Coach Details\n9: Exit\n");
      System.out.print("Enter your choice: ");
      choice = sc.nextInt();

      if (choice == 1) {
        addPlayer();
      } else if (choice == 2) {
        deletePlayer();
      } else if (choice == 3) {
        addCoach();
      } else if (choice == 4) {
        deleteCoach();
      } else if (choice == 5) {
        updatePlayer();
      } else if (choice == 6) {
        updateCoach();
      } else if (choice == 7) {
        if (pptr > 0) {
          for (int i = 0; i < pptr; i++) {
            System.out.print("\n");
            player[i].getPlayerDetails();
          }
        } else {
          System.out.println("Player Database is Empty !!");
        }
      } else if (choice == 8) {
        if (pptr > 0) {
          System.out.print("Enter Player Jersy Number: ");
          int jn = sc.nextInt();
          int is = searchPlayer(jn);
          if (is != -1) {
            player[is].getCoach();
          } else {
            System.out.println("Player does not exist !!");
          }
        } else {
          System.out.println("Player Database is Empty !!");
        }
      } else if (choice == 9) {
        System.out.println("Process Terminating...\n");
        break;
      } else {
        System.out.println("Invalid Choice !!");
      }

    }
    sc.close();
  }

}
