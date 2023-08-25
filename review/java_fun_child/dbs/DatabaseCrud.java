package review.java_fun_child.dbs;

public class DatabaseCrud {

    public DatabaseConnection conninstance = null; 

    public DatabaseCrud(DatabaseConnection connInstance) {
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

    public String get(String dbName, String item) {
        // String sql = "SELECT item FROM shoplist" + "WHERE item " + "LIKE " + shopItem + '%';
        String sql = "SELECT item FROM" + " " +  dbName + "  " + "WHERE item = " + "'" + item  + "'" ;
        return this.conninstance.find(sql);
    }

    // read orange from db
     public String getRow1(String tableName) {
        int row = 1;
        String sql = "SELECT item  FROM" + " " +  tableName +   " WHERE id = "  + "'" +  row + "'"    ;
        return this.conninstance.find(sql);
    }

}
