class MyTable {
  void print(int n, long id) {
    System.out.println("Message 1 : " + id);
    synchronized (this) {
      System.out.println("Message 2 : " + id);

      for (int i = 0; i < 3; i++) {
        System.out.println(n * i + " Id = " + id);
        try {
          Thread.sleep(2);
        } catch (InterruptedException e) {
          e.printStackTrace();
        }
      }
      System.out.println("Message 3 : " + id);

    }
    System.out.println("Message 4 : " + id);
  }
}

class MyThread3 extends Thread {
  MyTable t;

  MyThread3(MyTable t) {
    this.t = t;
  }

  public void run() {
    t.print(5, getId());
  }
}

class MyThread4 extends Thread {
  MyTable t;

  MyThread4(MyTable t) {
    this.t = t;
  }

  public void run() {
    t.print(10, getId());
  }
}

public class BlockSync {
  public static void main(String[] args) {
    MyTable ble = new MyTable();
    MyThread3 th1 = new MyThread3(ble);
    MyThread4 th2 = new MyThread4(ble);

    th1.start();
    th2.start();

  }

}
