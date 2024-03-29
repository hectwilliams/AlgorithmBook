package jx_review.java_fun_child.io.wr;

// import output stream package 
import java.io.FileOutputStream; 

// import exception package
import java.io.IOException;

import java.nio.file.Paths;

import java.util.regex.Matcher;
import java.util.regex.Pattern;


public class FileWritingExample {
    public static void main(String[] args) {

        String currDir = Paths.get("review", "java_fun_child", "io", "wr").toAbsolutePath().normalize().toString();
        String filename = Paths.get(currDir, "example.txt").toString() ;  
        String message = "Hey Tarzan, my number is 676-313-9383";   
        
        try {
            
            // create a new file 
            FileOutputStream fos = new FileOutputStream(filename);
            
            // write the content to the file 
            fos.write(message.getBytes());
            
            // close the file stream 
            fos.close(); 
            
            System.out.println("file printed and written");
            System.out.println(Paths.get("").toAbsolutePath().toString());
            System.out.println(filename);

        } catch (IOException e) {
            System.out.println("An error occurred while writing the file");
            e.printStackTrace();
        } finally {
            Pattern pattern = Pattern.compile("\\d\\d\\d-\\d\\d\\d-\\d\\d\\d\\d", Pattern.CASE_INSENSITIVE);
            Matcher matcher = pattern.matcher(message);
            if (matcher.find()) {
                // print telephone number 
                System.out.println(  message.substring( matcher.start(), matcher.end() - 1 ) );
            }
        }
    }
}
