import java.io.*;
import java.net.*;

public class Server_Side {
  public static void main(String[] args) {
    int port = 5020;
    ServerSocket serverSocket = null;
    Socket socket = null;

    try {
      ServerSocket server = new ServerSocket(port);
      socket = server.accept();

      DataInputStream in = new DataInputStream(socket.getInputStream());
      System.out.println("Server started. Waiting for client...");

      String line;
      while (!(line = in.readUTF()).equals("End")) {
        System.out.println("Client: " + line);
      }
    } catch (IOException e) {
      e.printStackTrace();
    }
  }
}