import java.net.*;

public class Example1 {
    public static void main(String[] args) {
        try {
            InetAddress address = InetAddress.getByName("www.iiitg.ac.in");

            System.out.println("Host Name: " + address.getHostName());
            System.out.println("IP Address: " + address.getHostAddress());
        } catch (UnknownHostException e) {
            System.out.println("Host not found: " + e.getMessage());
        }
    }
}