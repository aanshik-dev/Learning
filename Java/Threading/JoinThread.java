class MyThread11 extends Thread{
	@Override
	public void run() {
		int i=0;
		while(i<15) {
		System.out.println("Thread 11 is running "+i);
		i++;}
	}
}

class MyThread22 extends Thread{
	@Override
	public void run() {
		int i=0;
		while(i<20) {
		System.out.println("Thread 22 is running "+i);
		i++;}
	}
}

public class JoinThread{
	public static void main(String[] args) throws InterruptedException{
		MyThread11 t1=new MyThread11();
		MyThread22 t2=new MyThread22();
			
		t1.start();
		t2.start();
		
		t1.join(); //I(main) will wait till the completion of t1
		t2.join();
		
		for (int i=0; i<3; i++)
		System.out.println("Main thread is running "+i);
			
		
		//while(true)
		
		//t1.run();
		//t2.run();
	}

}
