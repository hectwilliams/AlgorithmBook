package java_fun.java_fun_child.oop;

// parent class 
public class UnitedStates {

    // variables 
    public int population;
    public int area; 

    // constructor
    public UnitedStates(int population, int area) {
        this.population = population;
        this.area = area ;
    }

    // methods 
    
    public void numberBirths(int increment) {
        this.population += increment;
    }

    public String toString() {
        return "this population is: " + this.population  + "\n area is: " + this.area + "\n";
    }
    

}

