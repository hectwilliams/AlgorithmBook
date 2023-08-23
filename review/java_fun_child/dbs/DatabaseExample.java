/*
 * Install MySQL JDBC driver 
 *  Dowbload MySQL Native Interface here -> https://dev.mysql.com/downloads/connector/cpp/8.0.html
 *  Select shift + command + P
 *  Search: Classpath configuration 
    *  Update reference libraries path at the bottom to mysql-connector-j-x.x.x.jar
 *  Run example program 
 * 
 */
package review.java_fun_child.dbs;

import java.sql.*;
import java.lang.ClassNotFoundException;

public class DatabaseExample {

    public static void main (String[] args) throws ClassNotFoundException {

        // check for database
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
        } catch ( ClassNotFoundException ex) {
            System.out.println("Error: MYSQL JDBC driver not found.");
        }

        Connection conn = null;

        Statement stmt = null; 

        try {

            // Connect to the H2 in-memory database using the default URL
            conn = DriverManager.getConnection(
                "jdbc:h2:~/test", 
                "sa",
                ""
            );
            
            // akin to messenger, purpose is to send statements to database 
            stmt = conn.createStatement(); 

            // create db table 
            String sql = "CREATE TABLE" + " "
            + "shoplist (id INTEGER NOT NULL, item VARCHAR(255), quantity INTEGER, PRIMARY KEY(id) )";

            // send command (i.e. messege) to db 
            stmt.executeUpdate(sql);

            System.out.println("Table created successfully");

        } catch (SQLException se) {
            
            // error handle error 
            se.printStackTrace();

        } finally {

            try {
                
                // close statement (i.e. messenger)
                if (stmt != null) {
                    stmt.close();
                } 
                
            } catch (SQLException se) {
                // already closed NOOP
            }

             try {
                
                // close connection to db 
                if (conn != null) {
                    conn.close();
                } 
                
            } catch (SQLException se) {
                // conn error handle
                se.printStackTrace();
            }

        }
    }

}
