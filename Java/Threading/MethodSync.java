class Table {
  synchronized void print(int n, long id) {
    System.out.println("Message 1 " + id);
    System.out.println("Message 2 " + id);

    for (int i = 0; i < 6; i++) {
      System.out.println(n * i + "Id " + id);
    }
  }
}

class MyThread1 extends Thread {
  Table t;

  MyThread1(Table t) {
    this.t = t;
  }

  @Override
  public void run() {
    t.print(5, this.getId());
  }
}

class MyThread2 extends Thread {
  Table t;

  MyThread2(Table t) {
    this.t = t;
  }

  @Override
  public void run() {
    t.print(10, getId());
  }
}

public class MethodSync {
  public static void main(String[] args) {
    Table tble = new Table();
    MyThread1 th1 = new MyThread1(tble);
    MyThread2 th2 = new MyThread2(tble);

    th1.start();

    th2.start();

  }

}
