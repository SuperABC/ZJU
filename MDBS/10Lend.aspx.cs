using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Book {
    public partial class _10Lend : System.Web.UI.Page {
        protected void Page_Load(object sender, EventArgs e) {

        }

        protected void Button1_Click(object sender, EventArgs e) {
            if (TextBox1.Text.Trim() == "" && TextBox2.Text.Trim() == "" && TextBox3.Text.Trim() == "") {
                SqlDataSource1.SelectParameters["Name"].ConvertEmptyStringToNull = true;
                SqlDataSource1.SelectParameters["Title"].ConvertEmptyStringToNull = true;
                SqlDataSource1.SelectParameters["LendTime"].ConvertEmptyStringToNull = true;
            }
            else {
                SqlDataSource1.SelectParameters["Name"].ConvertEmptyStringToNull = false;
                SqlDataSource1.SelectParameters["Title"].ConvertEmptyStringToNull = false;
                SqlDataSource1.SelectParameters["LendTime"].ConvertEmptyStringToNull = false;
            }
            SqlDataSource1.SelectCommand = "SELECT Patron.Name, Book.Title, Lend.CallNo, Lend.PatronID,"+
                "Lend.LendTime, Lend.ReturnTime FROM Book INNER JOIN Lend ON Book.CallNo = Lend.CallNo INNER" +
                "JOIN Patron ON Lend.PatronID = Patron.PatronID WHERE(Patron.Name LIKE '%' + @Name + '%')" +
                "AND(Book.Title LIKE '%' + @Title + '%')";
            if (TextBox3.Text.Trim() != "")
                SqlDataSource1.SelectCommand += " AND CONVERT(date, LendTime, 23) " +
                DropDownList1.SelectedValue + " @LendTime";
        }
    }
}