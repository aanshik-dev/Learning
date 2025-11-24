package MyPackage;

import java.io.*;
import java.util.Properties;

public class fileProperties {
    public static void main(String[] args) {
    	
        File configFile = new File("C:\\FilesList\\config.properties");
        try {
			configFile.createNewFile();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
        Properties props = new Properties();

        props.setProperty("username", "admin");
        props.setProperty("password", "12345");
        props.setProperty("server", "localhost");

        try {
            FileOutputStream out = new FileOutputStream("C:\\FilesList\\config.properties");
            props.store(out, "App Configuration");
            out.close();
            System.out.println("Properties file created!");

            FileInputStream in = new FileInputStream("C:\\FilesList\\config.properties");
            Properties readProps = new Properties();
            readProps.load(in);
            in.close();

            System.out.println("Username: " + readProps.getProperty("username"));
            System.out.println("Server: " + readProps.getProperty("server"));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
