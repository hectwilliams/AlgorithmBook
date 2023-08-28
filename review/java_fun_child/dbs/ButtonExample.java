package review.java_fun_child.dbs;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

// inherit Frame class 

public class ButtonExample extends Frame {

    public final String[] labels= {"Click Me", "I'm Melting"};
    public Button b = null; 
    boolean bool = false ;

    public ButtonExample() {
        
        /* WINDOW/ COMPONENTS */

        // create button component 
        b = new Button(this.labels[0]);
        
        // set button size and location
        b.setBounds(30, 30, 80, 40);
        
        // add(method) button to frame
        add(b);

        // setTitle (method)
        setTitle("Click me to read Database");

        // no layout manager 
        setLayout(null);

        // visible frame 
        setVisible(true);

        // frame size 
         GraphicsDevice gd = this.getGraphicsConfiguration().getDevice();
         int height = gd.getDisplayMode().getHeight();
         int width = gd.getDisplayMode().getWidth();
         this.setSize(width, height);

        
        
        /* ACTIONS */

        b.addActionListener( (event) -> {       
            this.updateButtonLabel();
        });

        this.addWindowListener(
            new WindowAdapter() {
                public void windowClosing(WindowEvent we_event) {
                    we_event.getWindow().dispose();
                }
            }
        );
    }

    // call by event listener of button 
    public void updateButtonLabel() { 
        if (this.b.getLabel().contains("Click")) {
            // value from database 
            b.setLabel(this.labels[1]);
        } else {
            b.setLabel(this.labels[0]);
        }
    }

    // call by public Class Execute  to update array label storage
    public void updateButtonLabel(String  str) {
        this.labels[1] = str;
    }

    public static void main(String args[]) {
        ButtonExample f = new ButtonExample();
        GraphicsDevice gd = MouseInfo.getPointerInfo().getDevice();
        System.out.println(gd.getDisplayMode().getWidth());
        System.out.println(gd.getDisplayMode().getHeight());
        
        GraphicsDevice ggd = f.getGraphicsConfiguration().getDevice();
        System.out.println ( ggd.getDisplayMode().getWidth());
        System.out.println ( ggd.getDisplayMode().getHeight());

    } 

}
