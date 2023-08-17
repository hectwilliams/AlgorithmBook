package java_fun.java_fun_child.multi_inheritance;

/**
 * 
 * 
 *          Vehicle                 Personal 
 * 
 *              \                   /
 * 
 *                      Bicycle
 * 
 * 
 */ 

public class Bicycle implements Personal, Vehicle {
    
    @Override
    public int numberOfWheels() {
        return 2;
    }

    @Override 
    public int numberOfPassengers() {
        return 1;
    }

    @Override 
    public String move() {
        return "Starting to pedal";
    }
    
}
