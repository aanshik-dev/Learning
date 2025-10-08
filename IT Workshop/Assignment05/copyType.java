import java.util.Scanner;

class Coach {
  private String name;
  private String coachId;

  Coach(Coach c) {
    this.name = c.name;
    this.coachId = c.coachId;
  }

  Coach(String name, String coachId) {
    this.name = name;
    this.coachId = coachId;
    System.out.println("Coach Added Successfully !!");
  }

  @Override
  public String toString() {
    return "Coach Name : " + this.name + "\n" + "Coach ID : " + this.coachId;
  }

  public String getId() {
    return this.coachId;
  }

  public void updateName(String name) {
    this.name = name;
  }
}

class Player {
  public static int teamCode;
  static {
    teamCode = 718;
  }
  Scanner sc = new Scanner(System.in);
  private String name;
  private int jersyNo;
  private Coach coach;
  private String role;

  public Player(String name, int jersyNo, Coach coach, String role) {
    this.name = name;
    this.jersyNo = jersyNo;
    this.coach = coach;
    this.role = role;
    System.out.println("Player Added Successfully !!");
  }

  static boolean flag = true;

  public Player(Player p) {
    this.name = p.name;
    this.jersyNo = p.jersyNo;
    this.role = p.role;
    if (flag) {
      this.coach = new Coach(p.coach);
      System.out.println("Player deep copy created !!");
    } else {
      this.coach = p.coach;
      System.out.println("Player shallow copy created !!");
    }
  }

  public void getPlayerDetails() {
    System.out.println("Team Code: " + teamCode);
    System.out.println("Player Name: " + this.name);
    System.out.println("Player Jersy Number: " + this.jersyNo);
    System.out.println("Player Role: " + this.role);
    System.out.println(this.coach.toString());
  }

  public static void toggleType(boolean f) {
    flag = f;
  }

  public int getJN() {
    return this.jersyNo;
  }

  public static void updateTC(int tc) {
    teamCode = tc;
  }

}

// Driver Class //////////////////////////////////////////
public class copyType {
  public static Scanner sc = new Scanner(System.in);
  public static Player player[] = new Player[11];
  public static Coach coach[] = new Coach[5];
  public static int cptr = 0;
  public static int pptr = 0;

  private static int searchCoach(String id) {
    for (int i = 0; i < cptr; i++) {
      if (coach[i].getId().equals(id)) {
        return i;
      }
    }
    return -1;
  }

  private static int searchPlayer(int id) {
    for (int i = 0; i < pptr; i++) {
      if (player[i].getJN() == id) {
        return i;
      }
    }
    return -1;
  }

  public static void addPlayer() {
    if (pptr < 11) {
      System.out.print("Enter Jersy Number: ");
      int jn = sc.nextInt();
      int is = searchPlayer(jn);
      if (is == -1) {
        System.out.print("Enter Coach ID: ");
        String id = sc.next();
        int idx = searchCoach(id);
        if (idx != -1) {
          System.out.print("Enter Player Name: ");
          String name = sc.next();
          System.out.print("Enter Player Role: ");
          String role = sc.next();
          player[pptr] = new Player(name, jn, coach[idx], role);
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

  public static void copy(boolean flag) {
    if (pptr > 0) {
      System.out.print("Enter Jersy Number: ");
      int jn = sc.nextInt();
      int is = searchPlayer(jn);
      if (is != -1) {
        Player.toggleType(flag);
        player[pptr] = new Player(player[is]);
        pptr++;
      } else {
        System.out.println("Player does not exist !!");
      }
    } else {
      System.out.println("Cannot Copy !! Player Database is Empty !!");
    }
  }

  public static void addCoach() {
    if (cptr < 5) {
      System.out.print("Enter the Coach ID: ");
      String id = sc.next();
      int is = searchCoach(id);
      if (is == -1) {
        System.out.print("Enter Coach Name: ");
        String name = sc.next();
        coach[cptr] = new Coach(name, id);
        cptr++;
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

  public static void main(String[] args) {

    while (true) {
      int choice;
      System.out.println(
          "\n======= MENU =======\n1: Add Player\n2: Delete Player\n3: Add Coach\n4: Player Shallow Copy\n5: Player Deep Copy\n6: Update Coach\n7: Update Team Code\n8: Display Player Details\n9: Exit\n");
      System.out.print("Enter your choice: ");
      choice = sc.nextInt();

      if (choice == 1) {
        addPlayer();
      } else if (choice == 2) {
        deletePlayer();
      } else if (choice == 3) {
        addCoach();
      } else if (choice == 4) {
        copy(false);
      } else if (choice == 5) {
        copy(true);
      } else if (choice == 6) {
        updateCoach();
      } else if (choice == 7) {
        if (pptr > 0) {
          System.out.print("Enter New Team Code : ");
          int code = sc.nextInt();
          player[0].updateTC(code);
          System.out.println("Team Code Updated Successfully !!");
        } else {
          System.out.println("Player Database is Empty !!");
        }
      } else if (choice == 8) {
        if (pptr > 0) {
          for (int i = 0; i < pptr; i++) {
            System.out.print("\n");
            player[i].getPlayerDetails();
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