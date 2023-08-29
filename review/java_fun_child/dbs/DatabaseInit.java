package review.java_fun_child.dbs;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.Random;
import org.json.JSONException;
import org.json.JSONObject;

public class DatabaseInit {

    DatabaseInit(DatabaseCrud apiCrud, String workdir)  {
        String jsonPath = Paths.get(workdir, "data.json").toString() ;  
        Random rand = new Random(22);
        JSONObject jsonObject = null;
        String imgLocalePath = null;
        
        try {
            String content = new String(Files.readAllBytes(Paths.get(jsonPath)));
            jsonObject = new JSONObject(content);

            // add fruit and images items to database
            // Iterator<String> iterator = jsonObject.keys();
            
            for (String key: jsonObject.keySet()) {
                imgLocalePath = Paths.get( workdir , "assets", key + ".jpeg").toString();
                apiCrud.insert("shoplist", key, rand.nextInt(0, 10), imgLocalePath );
            }

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (JSONException e) {
            e.printStackTrace(); 
        } catch(IOException e) {
            e.printStackTrace();
        }
    }
        
}
