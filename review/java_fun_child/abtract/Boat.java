package review.java_fun_child.abtract;

// declare abstract class 
abstract class Boat {

    // declare method
    // initially called similar to constructor
    Boat() {
        System.out.println("Boat navigates");
    }

    // declare abstract method
    abstract void navigate();

    void changeOrientation() {
        System.out.println("Orientation changed");
    }

}
