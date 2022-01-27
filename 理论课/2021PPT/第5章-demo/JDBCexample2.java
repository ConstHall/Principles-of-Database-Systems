/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jdbcexample;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.sql.ResultSet;
/**
 *
 * @author SangYingpeng
 */
public class JDBCexample2{

    /**
     * @param args the command line arguments
     */
    public static void main(String[] argv) {
        try
        {
            Class.forName ("com.mysql.jdbc.Driver");
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/sysu","root", "1234");
            Statement stmt = conn.createStatement();
            try {
                stmt.executeUpdate(
                "insert into instructor values('77987', 'Kim', 'Physics', 98000)");
            } catch (SQLException sqle)
            {
                System.out.println("Could not insert tuple." + sqle);
            }
            ResultSet rset = stmt.executeQuery(
                "select dept_name, avg (salary) "+
                " from instructor "+
                " group by dept_name");
            while (rset.next()) {
                System.out.println(rset.getString("dept_name") + " " +
                rset.getFloat(2));
            }
            stmt.close();
            conn.close();
        }
        catch (Exception sqle)
        {
            System.out.println("Exception : " + sqle);
        }
    }
    
}
