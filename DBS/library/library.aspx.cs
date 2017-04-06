using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Data.Sql;
using System.Data.SqlClient;
using System.Data.SqlTypes;
using System.Configuration;
using System.Data;

namespace Book {
    public partial class library : System.Web.UI.Page {
        protected void Page_Load(object sender, EventArgs e) {

        }

        protected void Button1_Click(object sender, EventArgs e) {
            if (TextBox1.Text.Trim() != "") {
                switch (DropDownList1.Text) {
                    case "CallNo":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(CALLNO LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Title":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(TITLE LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Author":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(AUTHOR LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Publisher":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PUBLISHER LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "ISBN":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(ISBN LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "PubDate":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PUBDATE LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Pages":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PAGES LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Price":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PRICE LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Number":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(NUMBER LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "AvailableNumber":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(AVAILABLENUMBER LIKE '%' + @BOOKINPUT + '%')";
                        break;
                }
            }
        }

        protected void FormView1_PageIndexChanging(object sender, FormViewPageEventArgs e) {
            if (TextBox1.Text.Trim() != "") {
                switch (DropDownList1.Text) {
                    case "CallNo":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(CALLNO LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Title":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(TITLE LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Author":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(AUTHOR LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Publisher":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PUBLISHER LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "ISBN":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(ISBN LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "PubDate":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PUBDATE LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Pages":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PAGES LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Price":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(PRICE LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "Number":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(NUMBER LIKE '%' + @BOOKINPUT + '%')";
                        break;
                    case "AvailableNumber":
                        SqlDataSource1.SelectCommand = "SELECT * FROM BOOK WHERE(AVAILABLENUMBER LIKE '%' + @BOOKINPUT + '%')";
                        break;
                }
            }
        }

        protected void Button2_Click(object sender, EventArgs e) {
            if (TextBox2.Text.Trim() != "") {
                switch (DropDownList2.Text) {
                    case "PatronID":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(PATRONID LIKE '%' + @PERSONINPUT + '%')";
                        break;
                    case "Name":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(NAME LIKE '%' + @PERSONINPUT + '%')";
                        break;
                    case "Gender":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(GENDER LIKE '%' + @PERSONINPUT + '%')";
                        break;
                    case "BirthDate":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(BIRTHDATE LIKE '%' + @PERSONINPUT + '%')";
                        break;
                    case "Type":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(TYPE LIKE '%' + @PERSONINPUT + '%')";
                        break;
                    case "Department":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(DEPARTMENT LIKE '%' + @PERSONINPUT + '%')";
                        break;
                }
            }
        }

        protected void FormView2_PageIndexChanging(object sender, FormViewPageEventArgs e) {
            if (TextBox2.Text.Trim() != "") {
                switch (DropDownList2.Text) {
                    case "PatronID":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(PATRONID LIKE '%' + @PERSONINPUT + '%')";
                        break;
                    case "Name":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(NAME LIKE '%' + @PERSONINPUT + '%')";
                        break;
                    case "Gender":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(GENDER LIKE '%' + @PERSONINPUT + '%')";
                        break;
                    case "BirthDate":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(BIRTHDATE LIKE '%' + @PERSONINPUT + '%')";
                        break;
                    case "Type":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(TYPE LIKE '%' + @PERSONINPUT + '%')";
                        break;
                    case "Department":
                        SqlDataSource2.SelectCommand = "SELECT * FROM PATRON WHERE(DEPARTMENT LIKE '%' + @PERSONINPUT + '%')";
                        break;
                }
            }
        }

        protected void Button3_Click(object sender, EventArgs e) {
            if (DropDownList3.Text == "借阅") {
                string strConn = ConfigurationManager.ConnectionStrings["TSGConnectionString1"].ConnectionString;
                SqlConnection conn = new SqlConnection(strConn);
                string bookSql = "SELECT * FROM BOOK WHERE CALLNO = \'" + TextBox3.Text + "\'";
                string patronSql = "SELECT * FROM PATRON WHERE PATRONID = \'" + TextBox4.Text + "\'";
                SqlCommand bookCmd = new SqlCommand(bookSql, conn);
                SqlCommand patronCmd = new SqlCommand(patronSql, conn);
                SqlDataAdapter bookDa = new SqlDataAdapter(bookCmd);
                SqlDataAdapter patronDa = new SqlDataAdapter(patronCmd);
                DataSet ds = new DataSet();

                int bookLeft = 0;
                bookDa.Fill(ds, "BOOK");
                DataTable books = ds.Tables["BOOK"];
                try {
                    bookLeft = int.Parse(books.Rows[0]["AVAILABLENUMBER"].ToString());
                }
                catch {
                    Response.Write("<script>alert('输入有误，请重新输入！')</script>");
                    return;
                }
                patronDa.Fill(ds, "PATRON");
                DataTable patrons = ds.Tables["PATRON"];
                try {
                    patrons.Rows[0]["PATRONID"].ToString();
                }
                catch {
                    Response.Write("<script>alert('输入有误，请重新输入！')</script>");
                    return;
                }
                if (bookLeft == 0) {
                    Response.Write("<script>alert('库存不足，无法借阅！')</script>");
                    return;
                }
                string lendSql = "INSERT LEND VALUES(\'" + TextBox3.Text + "\', \'" + TextBox4.Text + "\', GETDATE(), NULL)";
                conn.Open();
                SqlCommand lendCmd = new SqlCommand(lendSql, conn);
                try {
                    lendCmd.ExecuteReader();
                }
                catch {
                    Response.Write("<script>alert('系统错误，请检查输入！')</script>");
                }
                finally {
                    TextBox3.Text = "";
                    TextBox4.Text = "";
                    SqlDataSource3.Update();
                }
            }
            else {
                string strConn = ConfigurationManager.ConnectionStrings["TSGConnectionString1"].ConnectionString;
                SqlConnection conn = new SqlConnection(strConn);
                DataSet ds = new DataSet();
                string lendSql = "UPDATE LEND SET RETURNTIME = GETDATE() WHERE CALLNO = \'" + TextBox3.Text + "\' AND PATRONID = \'" + TextBox4.Text + "\'";
                conn.Open();
                SqlCommand lendCmd = new SqlCommand(lendSql, conn);
                try {
                    lendCmd.ExecuteReader();
                }
                catch {
                    Response.Write("<script>alert('系统错误，请检查输入！')</script>");
                }
                finally {
                    TextBox3.Text = "";
                    TextBox4.Text = "";
                    SqlDataSource3.Update();
                }
            }
        }

        protected void Button4_Click(object sender, EventArgs e) {
            SqlDataSource3.Update();
        }
    }
}