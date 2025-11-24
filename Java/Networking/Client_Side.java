package MyPackage;

import java.io.*;
import java.net.*;

public class Client_Side {
    public static void main(String[] args) {
        try {
        	 Socket socket = new Socket("127.0.0.1", 5000);
             DataOutputStream out = new DataOutputStream(socket.getOutputStream());
             
             BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
            
            System.out.println("Connected to Server");
            String line;
            while (!(line = br.readLine()).equals("End")) {
                out.writeUTF(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
