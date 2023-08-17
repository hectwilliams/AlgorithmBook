package java_fun.java_fun_child.hybrid_inheritance;

public class Execute {
    public static void main (String[] args) {
        Car car = new Car(4);
        car.setMotor("V8");

        System.out.println("Car is initializing: " + '[' + car.move() + ']' );

    }
}
