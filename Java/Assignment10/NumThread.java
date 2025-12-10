class MyThread extends Thread {
  public static int count = 1;
  public static int MAX = 20;
  public static Object lock = new Object();

  int remainder;

  MyThread(int remainder, String name) {
    this.remainder = remainder;
    this.setName(name);
  }

  public void run() {
    synchronized (lock) {
      while (true) {
        if (count > MAX)
          break;
        if (count % 3 == remainder) {
          System.out.println(this.getName() + " : " + count);
          count++;
          lock.notifyAll();
        } else {
          try {
            lock.wait();
          } catch (InterruptedException e) {
            e.printStackTrace();
          }
        }
      }
    }
  }
}

public class NumThread {
  public static void main(String[] args) {
    MyThread t1 = new MyThread(1, "A");
    MyThread t2 = new MyThread(2, "B");
    MyThread t3 = new MyThread(0, "C");
    t1.start();
    t2.start();
    t3.start();
  }

}
