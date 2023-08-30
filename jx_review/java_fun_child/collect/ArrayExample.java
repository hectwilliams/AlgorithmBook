package jx_review.java_fun_child.collect;

//import interface 
import java.util.List;

// import arraylist class 
import java.util.ArrayList;

public class ArrayExample {

    public static void main (String[] args) {

        List<String> fruits = new ArrayList<>();

        fruits.add("Green Apple");

        fruits.add("Banana");

        fruits.add("Mango");

        for (int i = 0; i < fruits.size(); i++) {
            System.out.println(fruits.get(i));
        }
    }
}
