package review.java_fun_child.dbs;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Paths;
import java.nio.file.Files;

import java.io.File;
import java.text.ParseException;
import java.util.Iterator;
import java.util.Random;

import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;

public class Execute {

    public static void main ( String[] args) {
        System.getProperty("user.dir");
        DatabaseConnection conndB = new DatabaseConnection();
        String filename = Paths.get(conndB.workingDir, "data.json").toString() ;  
        Random rand = new Random(22);
        // ButtonExample button = new ButtonExample(); 
        JSONObject jsonObject = null;
        String key = null; 
        String imgLocalePath = null;

        try {
            String content = new String(Files.readAllBytes(Paths.get(filename)));
            jsonObject = new JSONObject(content);

            // add fruit and images items to database
            Iterator<String> iterator = jsonObject.keys();
            for (String x: jsonObject.keySet()) {
                System.out.println(x);            
                imgLocalePath = Paths.get(conndB.workingDir, key + ".jpeg").toString();
                // crudMyApi.insert("shoplist", iterator.next(), rand.nextInt(0, 10), imgLocalePath );
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (JSONException e) {
            e.printStackTrace(); 
        } catch(IOException e) {
            e.printStackTrace();
        }



        // add items to 
        // crudMyApi.insert( "shoplist", "Orange", 100);
        // crudMyApi.insert( "shoplist", "Apple", 20) ;

        // // crudMyApi.insert_p( "properties", "Orange", "");
        // // crudMyApi.insert_p( "properties", "Apple", 100);

        // // does orange exist in shoplist table
        // button.updateButtonLabel(
        //      crudMyApi.getRow1("shoplist")
        // );

        // conndB.closeConnection();
    }
}
