package jx_review.java_fun_child.dbs;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import java.util.ArrayList;
import java.util.List; 

import java.util.Random;

import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.nio.file.Paths;
import java.nio.file.Files;

import java.io.File;
import java.text.ParseException;
import java.util.Iterator;

import org.json.JSONObject;
import org.json.JSONArray;
import org.json.JSONException;

import java.lang.Math; 

// inherit Frame class 

public class App extends Frame {

    public Button b = null; 
    public GridLayout grid = null ; 
    List<Button> buttons = new ArrayList<>();  // buffe of buttons 
    Random rand = new Random();
    public String workingDir = Paths.get("review", "java_fun_child", "dbs").toAbsolutePath().normalize().toString();
    DatabaseConnection conninstance = new DatabaseConnection();
    DatabaseCrud crudMyApi = new DatabaseCrud(conninstance);

    public App() {

        new DatabaseInit(crudMyApi, workingDir);
        
        setTitle("Button - Database Chat");
        
        List<String>  items = crudMyApi.db_items("shoplist");
        int r = (int) Math.ceil(items.size() / 2.0);   
        int c = 2;
        GridLayout grid = new GridLayout( r ,  c); 
        
        setLayout(grid);
        setVisible(true);
        
        // // frame size 
         GraphicsDevice gd = this.getGraphicsConfiguration().getDevice();
         int height = gd.getDisplayMode().getHeight();
         int width = gd.getDisplayMode().getWidth();
         this.setSize(width, height);
         
        // // create button(s), not connected to database 
        for (int i = 0; i < items.size(); i++) {
            b = new Button( items.get(i));
            
            Color color = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat());
            b.setBackground(  color);
            color = new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat() ) ;
            b.setForeground(color);
            
            Font font = new Font(Font.SANS_SERIF, Font.BOLD, 12);
            b.setFont(font);
            buttons.add ( b ) ;
        }
        
        // // append buttons to grid
        for (Button button_ele: buttons) {
            add(button_ele);
        }

        // close window 
        this.addWindowListener(
            new WindowAdapter() {
                public void windowClosing(WindowEvent we_event) {
                    we_event.getWindow().dispose();
                }
            }
        );

        // add button listener event 
        // change button color when clicked 
        for (Button button: buttons) {
            button.addActionListener(event -> {  // lambda 
                button.setBackground( new Color(rand.nextFloat(), rand.nextFloat(), rand.nextFloat()) );
            });
        }
    }

    public static void main(String args[]) {
        App app = new App();

    } 

}
