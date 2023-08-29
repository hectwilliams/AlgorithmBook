package review.java_fun_child.abtract;

public class Test {
    public static void main (String[] args)    {
        Boat obj = new Yacht();
        obj.navigate();
        obj.changeOrientation();
    }
}
