package jx_review.java_fun_child.interfaces;

public class Cat implements Animal {

    //Cat class must implement age

    public void age() {
        System.out.println("Age is");
    }

    //Cat class must implement weight
    
    public void weight() {
        System.out.println("The weight is");
    }


    public static void main(String [] args) {
        Cat catInstance = new Cat();
        catInstance.meow();
        catInstance.weight();
        catInstance.age();

    }
}
