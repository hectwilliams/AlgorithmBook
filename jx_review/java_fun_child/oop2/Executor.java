package jx_review.java_fun_child.oop2;


public class Executor {
    public static void  main(String [] args) {

        // instantiate base class
        Aircraft aircraftObj = new Aircraft("Gas", "rocket");
        
        // instantiate derived class
        Drone droneObj = new Drone("electric", "propellers", 0);

        System.out.println(aircraftObj.toString());
        System.out.println(droneObj.toString());

    }
}
