package review.java_fun_child.dbs;

public class Execute {
    public static void main ( String[] args) {
        DatabaseConnection conndB = new DatabaseConnection();
        DatabaseCrud crudMyApi = new DatabaseCrud(conndB);
        ButtonExample button = new ButtonExample(); 
        // add items to 
        crudMyApi.insert( "shoplist", "Orange", 100);
        crudMyApi.insert( "shoplist", "Apple", 20) ;
        crudMyApi.insert( "properties", "Orange", 100);
        crudMyApi.insert( "properties", "Apple", 100);

        // does orange exist in shoplist table
        button.updateButtonLabel(
             crudMyApi.getRow1("shoplist")
        );

        conndB.closeConnection();
    }
}
