package jx_review.java_fun_child.multi_inheritance;

public class Executor {
    public static void main(String[] args) {
        Bicycle bicycle = new Bicycle();
        System.out.println("To move a Bicycle you should " + '[' + bicycle.move() + ']');
        System.out.println("Bicycle has space for" + '[' + bicycle.numberOfPassengers() + ']' + " passengers");
        System.out.println("Bicycle has " + '[' + bicycle.numberOfWheels() + ']' + " wheels");

    }
}
