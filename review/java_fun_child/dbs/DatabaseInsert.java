package review.java_fun_child.dbs;

public class DatabaseInsert {

    public DatabaseConnection conninstance = null; 

    public DatabaseInsert(DatabaseConnection connInstance) {
        this.conninstance = connInstance;
    }

    public void insert() {
        String sql = "INSERT INTO shoplist(item, quantity) VALUES('Orange', 10)";
        this.conninstance.insert(sql);
    }

     public void insert(String dbName, String item, int amount) {
        item = item.toLowerCase();
        String sql = "";
        
        if (dbName.contains( "shop") ) {
            sql = "INSERT INTO" + " " + dbName + "(item, quantity)" +  "VALUES"+ '(' + "'"+  item + "'" +  ',' +  amount + ')' ;
        } 

        if (dbName.contains( "prop") ) {
            sql = "INSERT INTO" + " " + dbName + "(item_name)" +  "VALUES"+ '(' + "'"+  item + "'"  + ')' ;
        } 

        this.conninstance.insert(sql);
    }

    public void check(String dbName, String item) {
        // String sql = "SELECT item FROM shoplist" + "WHERE item " + "LIKE " + shopItem + '%';
        String sql = "SELECT item FROM" + " " +  dbName + "  " + "WHERE item = " + "'" + item  + "'" ;
        boolean found_item = this.conninstance.find(sql);
        System.out.println(found_item);
    }


}
