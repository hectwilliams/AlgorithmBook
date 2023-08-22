package review.java_fun_child.collect;

// import class HashMap
import java.util.HashMap;

// import interface Map 
import java.util.Map;

//import interface Iterator
import java.util.Iterator;

public class HashMapExample {

    public static void main (String [] args) {

        Map<String, Integer> map = new HashMap<>();

        // add key-pair to map list 
        map.put("Apple", 5);

        Map<String, Integer> map2 = new HashMap<>();
        
        map.put("Orange", 2);

        map.put("Banana", 19);

        map.putAll(map2);

        if ( map.putIfAbsent("Mango", 4 ) == null ) {
            System.out.println("added mango into map");
        }

        map.computeIfAbsent("Pineapple", k-> 6);

        // print map
        System.out.println(map);
        
        // print keys 
        Iterator<String> iterator = map.keySet().iterator();
        
        //   (next)  (null)   
        // ->  []  - null 

        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }
        
        map.forEach( 
            (key, value) -> System.out.println("key:" + " " + key) 
        );

    }
}
