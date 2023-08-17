package java_fun.java_fun_child.abtract;

// inheritance from an abstract class 
public class Yacht extends Boat {
    
    void navigate() {
        System.out.println("Navigating on course");
    }

    // changeOrientation() - visible to developer

    // Boat() - (similar to constructor) hidden from developer 
}

