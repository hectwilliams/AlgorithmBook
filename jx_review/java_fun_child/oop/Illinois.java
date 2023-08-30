package jx_review.java_fun_child.oop;

// inheritance
public class Illinois extends UnitedStates {
    
    // new variables
    public int cities;

    // constructor
    public Illinois(int population, int area, int cities) {
        
        // invoke UnitedStates constructor 
            // this.population = population;
            // this.area = area ;
        super(population, area);

        this.cities = cities; 
    }

    // methods 
    public void setDiscticts (int newDistribution) {
        this.cities = newDistribution;
    }

    @Override 
    public String toString() {
        return (super.toString() + "cities: " + this.cities);
    }

}
