package review.java_fun_child.dbs;

import java.util.List;
import java.util.ArrayList;

public class DatabaseCrud {

    public DatabaseConnection conninstance = null; 

    public DatabaseCrud(DatabaseConnection conn) {
        this.conninstance = conn;
    }

    public void insert() {
        String sql = "INSERT INTO shoplist(item, quantity) VALUES('Orange', 10)";
        int status = this.conninstance.insert(sql);
        if (status == 1) {} 
    }

    // insert to shoplist table 
     public void insert(String dbName, String item, int amount, String img) {
        int status = 0;
        item = item.toLowerCase();
        String sql = "";
        sql = "INSERT INTO" + " " + dbName + "(item, quantity, img)" +  "VALUES"+ '(' + "'"+  item + "'" +  ',' +  amount  +  " "  +  ','  +  "'"+  img + "'"  +   ')' ;
        status = this.conninstance.insert(sql);
        if (status == 1) {} 
    }

    // insert to properties table
    public void insert_p(String dbName, String item, String link) {
        item = item.toLowerCase();
        String sql = "";
        sql = "INSERT INTO" + " " + dbName + "(item_name, img)" +  "VALUES"+ '(' +    "'"+  item + "'"  +     + ')' ;
        this.conninstance.insert(sql);
    }

    public String get(String dbName, String item) {
        // String sql = "SELECT item FROM shoplist" + "WHERE item " + "LIKE " + shopItem + '%';
        String sql = "SELECT item FROM" + " " +  dbName + "  " + "WHERE item = " + "'" + item  + "'" ;
        return this.conninstance.find(sql);
    }

       // read orange from db
    public int db_length(String tableName) {
        String sql = "SELECT *  FROM" + " " +  tableName;
        int result = this.conninstance.size(sql);
        return result;
    }

      // read orange from db
    public List<String> db_items (String tableName) {
        String sql = "SELECT * FROM" + " " +  tableName;
        List<String>  result = this.conninstance.findAll(sql);
        return result;
    }

}
