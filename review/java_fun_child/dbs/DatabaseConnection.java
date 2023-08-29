/*
 * 
 * Install MySQL on macOS prior to java driver installer 
 *  
 * Create Database File (i.e. .sql file)
 * 
 * Using Terminal sign into mysql server ( sudo mysql -u root -p  )
 * 
 * 
 Install MySQL JDBC driver 
 *  Dowbload MySQL Native Interface here -> https://dev.mysql.com/downloads/connector/cpp/8.0.html
 *  Select shift + command + P
 *  Search: Classpath configuration 
    *  Update reference libraries path at the bottom to mysql-connector-j-x.x.x.jar
 * 
 *  Run example program 
 *
 * 
 */

package review.java_fun_child.dbs;

import java.sql.*;
import java.lang.ClassNotFoundException;
import java.nio.file.Paths;

public class DatabaseConnection {

    static String JDBC_DRIVER =  "com.mysql.cj.jdbc.Driver";
    
    // Connection URL format protocol//[hosts][/database][?properties]
    // protocol = jdbc:mysql
    // hosts = host:port (default port 3306 for MySQL connection)

    /* variables  */

    static final String DB_NAME = "shop";
    static final String DB_TABLENAME = "shoplist";
    static final String DB_NAME_TABLENAME = "shop.shoplist";

    static final String DB_URL =  "jdbc:mysql://localhost/" + DB_NAME;               
    static final String USERNAME = xx_xx_config.USERNAME;
    static final String PASSWORD = xx_xx_config.PASSWORD;
    final String TB_NAME = "shoplist";
    public Connection conn = null; 
    public Statement stmt = null;

    public final String workingDir = Paths.get("review", "java_fun_child", "dbs").toAbsolutePath().normalize().toString();

    /* constructor */
    public DatabaseConnection() {
      this.initdb();
      this.connectdb();
    //   this.closeConndb();
    }

    private void initdb() {
          // initialize/register database
        try {
            Class.forName(JDBC_DRIVER);
        } catch ( ClassNotFoundException ex) {
            System.out.println("Error: MYSQL JDBC driver not found.");
        }
    }

    private void connectdb() {

        try {
            conn = DriverManager.getConnection(
                DB_URL, 
                USERNAME,
                PASSWORD
            );

            // akin to messenger, purpose is to send statements to database 
            stmt = conn.createStatement(); 

            System.out.println("connected to database");

        } catch (SQLException se) {
            
            // error handle error 
            se.printStackTrace();

        }

    }

    public int insert(String sql) {
        int ret = 0;
        try {
            ret = this.stmt.executeUpdate(sql);
        } catch (SQLException se) {
            se.printStackTrace();
        }
        return ret;
    }

    public String find(String sql) {

        String rcvdString = "";

        try {
            ResultSet rs = this.stmt.executeQuery(sql);
            ResultSetMetaData rcvData = rs.getMetaData();
            int count = rcvData.getColumnCount();

            while (rs.next()) {
                rcvdString = rs.getString(count);
            }

        } catch (SQLException se) {
            se.printStackTrace();
        }

        return rcvdString; 
    }

    public String[] findAll(String sql) { 
        String [] rcvdStrings = {};

        try {
            ResultSet rs = this.stmt.executeQuery(sql);
            ResultSetMetaData rcvData = rs.getMetaData();
            System.out.println(rcvData);
        } catch(SQLException se) {
            se.printStackTrace();
        } 

        return rcvdStrings;
    }


    public int size(String sql) {

        int count = 0;

        try {
            ResultSet rs = this.stmt.executeQuery(sql);
            ResultSetMetaData rcvData = rs.getMetaData();
            count = rcvData.getColumnCount();
        } catch (SQLException se) {
            se.printStackTrace();
        }

        return count; 
    }


    public void closeConnection () {
        try {
            if (stmt != null) {
                stmt.close();
            } 
        } catch (SQLException se) {
        
        } try {
            if (conn != null) {
                conn.close();
            } 
        } catch (SQLException se) {
            se.printStackTrace();
        }
    }

    // public static void main (String[] args) throws ClassNotFoundException {}

}
