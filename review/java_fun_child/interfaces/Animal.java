package java_fun.java_fun_child.interfaces;

public interface Animal {
    
    // fields 

    public String Name = "";

    // methods 

    public void age();

    public void weight();

    // default method 
    default void meow() {  
        System.out.println("Cat meows");
    }

}
