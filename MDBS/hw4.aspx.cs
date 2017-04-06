using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Book {
    public partial class hw4 : System.Web.UI.Page {
        protected void Page_Load(object sender, EventArgs e) {

        }

        protected void Button1_Click(object sender, EventArgs e) {
            if (TextBox1.Text.Trim() != "") {
                switch (DropDownList1.Text) {
                    case "CallNo":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(CALLNO LIKE '%' + @NAME + '%')";
                        break;
                    case "Title":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(TITLE LIKE '%' + @NAME + '%')";
                        break;
                    case "Author":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(AUTHOR LIKE '%' + @NAME + '%')";
                        break;
                    case "Publisher":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PUBLISHER LIKE '%' + @NAME + '%')";
                        break;
                    case "ISBN":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(ISBN LIKE '%' + @NAME + '%')";
                        break;
                    case "PubDate":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PUBDATE LIKE '%' + @NAME + '%')";
                        break;
                    case "Pages":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PAGES LIKE '%' + @NAME + '%')";
                        break;
                    case "Price":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PRICE LIKE '%' + @NAME + '%')";
                        break;
                    case "Number":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(NUMBER LIKE '%' + @NAME + '%')";
                        break;
                    case "AvailableNumber":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(AVAILABLENUMBER LIKE '%' + @NAME + '%')";
                        break;
                }
            }
        }

        protected void FormView1_PageIndexChanging(object sender, FormViewPageEventArgs e) {
            if (TextBox1.Text.Trim() != "") {
                switch (DropDownList1.Text) {
                    case "CallNo":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(CALLNO LIKE '%' + @NAME + '%')";
                        break;
                    case "Title":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(TITLE LIKE '%' + @NAME + '%')";
                        break;
                    case "Author":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(AUTHOR LIKE '%' + @NAME + '%')";
                        break;
                    case "Publisher":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PUBLISHER LIKE '%' + @NAME + '%')";
                        break;
                    case "ISBN":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(ISBN LIKE '%' + @NAME + '%')";
                        break;
                    case "PubDate":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PUBDATE LIKE '%' + @NAME + '%')";
                        break;
                    case "Pages":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PAGES LIKE '%' + @NAME + '%')";
                        break;
                    case "Price":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PRICE LIKE '%' + @NAME + '%')";
                        break;
                    case "Number":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(NUMBER LIKE '%' + @NAME + '%')";
                        break;
                    case "AvailableNumber":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(AVAILABLENUMBER LIKE '%' + @NAME + '%')";
                        break;
                }
            }
        }
    }
}