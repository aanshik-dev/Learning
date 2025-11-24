import java.util.ArrayList;

class MyThread extends Thread {

  public void run() {
    for (int i = 0; i < 10; i++) {
      System.out.println(Thread.currentThread().getName() + " : " + i);
    }

    try {
      Thread.sleep(1000);
    } catch (InterruptedException e) {
      System.err.println(e);
    }

  }
}

public class NumThread {

  public static void main(String[] args) {
    ArrayList<MyThread> th = new ArrayList<MyThread>(4);
    for (int i = 0; i < 4; i++) {
      th.add(new MyThread());
    }

    for (int i = 0; i < 4; i++) {
      th.get(i).start();
    }

  }
}
