package jx_review.java_fun_child.oop2;

// PARENT CLASS 

public class Aircraft {
    
    // variables 
    
    private String fuel;
    private String engine;

    //constructor

    public Aircraft(String fuel, String engine) {
        this.fuel = fuel;
        this.engine = engine;
    }

    // methods  ( setter and getter)

    public String getFuel() {
        return this.fuel;
    }

    public void setFuel(String fuel) {
        this.fuel = fuel;
    }

    public String getEngine() {
        return this.engine;
    }

    public void setEngine (String engine) {
        this.engine = engine ;
    }

    @Override
    public String toString() {
        return "Drone{" +
        "fuel='" + this.getFuel() + "\'; " +
        "engine='" + this.getEngine() + "\'" +
        '}';
    }


}