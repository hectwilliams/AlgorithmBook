package java_fun.java_fun_child.oop2;

// CHILD CLASS 
public class Drone extends Aircraft {
    
    // fields 

    private int pilots;

    // constructor 

    public Drone(String fuel, String engine, int pilots) {
        super(fuel, engine);
        this.pilots = pilots; 
    }

    // methods  ( setter and getter)

    public int getPilots() {
        return this.pilots;
    }

    public void setPilots (int pilots) {
        this.pilots = pilots;
    }

    // overridden methods 
    @Override
    public String toString() {
        return "Drone{" +
        "fuel='" + super.getFuel() + "\'; " +
        "engine='" + super.getEngine() + "\'; " +
        "pilots='" + this.getPilots() + "\'" +
        '}';
    }
}
