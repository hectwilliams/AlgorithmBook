package jx_review.java_fun_child.hybrid_inheritance;

/*
 * 
 *   Motorized              
 *      \
 *      Car         -->  Vehicle
 *        
 *         
 *            
 * 
 */

// CAR
public class Car extends Motorized implements Vehicle{
    // traits ( or fields)
    private int tireCount;

    public Car (int tireCount) {
        super();
        this.tireCount = tireCount;
    }

    public void setTireCount(int tireCount) {
        this.tireCount = tireCount;
    }

    public int getTireCount() {
        return tireCount;
    }

    // implement abtract methods
    @Override
    public String move() {
        return "Starting motor type: " + '[' +  getMotor() + ']'  ;
    }

}
