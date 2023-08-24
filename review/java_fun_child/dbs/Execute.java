package review.java_fun_child.dbs;

public class Execute {
    public static void main ( String[] args) {
        DatabaseConnection conndB = new DatabaseConnection();
        DatabaseInsert insertdb = new DatabaseInsert(conndB);
        
        // add items to 
        insertdb.insert( "shoplist", "Orange", 100);
        insertdb.insert( "properties", "Orange", 100);

        // does orange exist in shoplist table
        insertdb.check("shoplist", "orange");

        conndB.closeConnection();
    }
}
