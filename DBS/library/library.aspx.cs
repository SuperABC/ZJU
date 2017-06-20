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
using System.IO;
using System.Text;

namespace Book {
    public partial class library : System.Web.UI.Page {
        public static string figure = "普通读者";
        protected void Page_Load(object sender, EventArgs e) {
            LabelFigure.Text = figure;
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
                string decreaseSql = "UPDATE BOOK SET AVAILABLENUMBER = " + (bookLeft - 1) + " WHERE CALLNO = \'" + TextBox3.Text + "\'";
                conn.Open();
                SqlCommand decreaseCmd = new SqlCommand(decreaseSql, conn);
                try {
                    decreaseCmd.ExecuteReader();
                }
                catch {
                    Response.Write("<script>alert('系统错误，请检查输入！')</script>");
                    return;
                }
                conn.Close();
                conn.Open();
                SqlCommand lendCmd = new SqlCommand(lendSql, conn);
                try {
                    lendCmd.ExecuteReader();
                }
                catch {
                    Response.Write("<script>alert('系统错误，请检查输入！')</script>");
                    return;
                }
                finally {
                    TextBox3.Text = "";
                    TextBox4.Text = "";
                    SqlDataSource3.DataBind();
                }
            }
            else {
                string strConn = ConfigurationManager.ConnectionStrings["TSGConnectionString1"].ConnectionString;
                SqlConnection conn = new SqlConnection(strConn);
                string bookSql = "SELECT * FROM BOOK WHERE CALLNO = \'" + TextBox3.Text + "\'";
                SqlCommand bookCmd = new SqlCommand(bookSql, conn);
                SqlDataAdapter bookDa = new SqlDataAdapter(bookCmd);
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

                string lendSql = "UPDATE (SELECT DISTINCT * FROM LEND) SET RETURNTIME = GETDATE() WHERE CALLNO = \'" + TextBox3.Text + "\' AND PATRONID = \'" + TextBox4.Text + "\'";
                string increaseSql = "UPDATE BOOK SET AVAILABLENUMBER = " + (bookLeft + 1) + " WHERE CALLNO = \'" + TextBox3.Text + "\'";
                conn.Open();
                SqlCommand increaseCmd = new SqlCommand(increaseSql, conn);
                try {
                    increaseCmd.ExecuteReader();
                }
                catch {
                    Response.Write("<script>alert('系统错误，请检查输入！')</script>");
                    return;
                }
                conn.Close();
                conn.Open();
                SqlCommand lendCmd = new SqlCommand(lendSql, conn);
                try {
                    lendCmd.ExecuteReader();
                }
                catch {
                    Response.Write("<script>alert('系统错误，请检查输入！')</script>");
                    return;
                }
                finally {
                    TextBox3.Text = "";
                    TextBox4.Text = "";
                    SqlDataSource3.Update();
                }
            }
        }

        protected void Button4_Click(object sender, EventArgs e) {
            SqlDataSource3.DataBind();
        }

        protected void Button5_Click(object sender, EventArgs e) {
            if (figure != "系统管理员" && figure != "图书管理员") {
                Response.Write("<script>alert(\'无此权限！\')</script>");
                return;
            }
            HomePanel.Visible = false;
            BookPanel.Visible = true;
        }

        protected void Button9_Click(object sender, EventArgs e) {
            HomePanel.Visible = true;
            BookPanel.Visible = false;
        }

        protected void Button6_Click(object sender, EventArgs e) {
            if (figure != "系统管理员" && figure != "读者管理员") {
                Response.Write("<script>alert(\'无此权限！\')</script>");
                return;
            }
            HomePanel.Visible = false;
            PatronPanel.Visible = true;
        }

        protected void Button10_Click(object sender, EventArgs e) {
            HomePanel.Visible = true;
            PatronPanel.Visible = false;
        }

        protected void Button7_Click(object sender, EventArgs e) {
            if (figure != "系统管理员" && figure != "借还操作员") {
                Response.Write("<script>alert(\'无此权限！\')</script>");
                return;
            }
            HomePanel.Visible = false;
            OperatePanel.Visible = true;
        }

        protected void Button11_Click(object sender, EventArgs e) {
            HomePanel.Visible = true;
            OperatePanel.Visible = false;
        }

        protected void Button8_Click(object sender, EventArgs e) {
            HomePanel.Visible = false;
            HistoryPanel.Visible = true;
        }

        protected void Button12_Click(object sender, EventArgs e) {
            HomePanel.Visible = true;
            HistoryPanel.Visible = false;
        }

        protected void Button14_Click(object sender, EventArgs e) {
            byte[] byteData;
            char[] charData;
            try {
                FileStream file = new FileStream(TextBox5.Text, FileMode.Open);
                file.Seek(0, SeekOrigin.Begin);
                byteData = new byte[file.Length];
                charData = new char[file.Length];
                file.Read(byteData, 0, (int)file.Length);
                Decoder d = Encoding.Default.GetDecoder();
                d.GetChars(byteData, 0, byteData.Length, charData, 0);

                string data = new string(charData);
                string[] words = data.Trim().Split(' ');
                string strConn = ConfigurationManager.ConnectionStrings["TSGConnectionString1"].ConnectionString;
                SqlConnection conn = new SqlConnection(strConn);
                conn.Open();
                string addSql;
                if (words.Length % 10 != 0) throw new Exception();
                for (int i = 0; i < words.Length; i+=10) {
                    addSql = "INSERT BOOK VALUES(\'" + words[i] + "\', " +
                        "\'" + words[i + 1] + "\'," +
                        "\'" + words[i + 2] + "\'," +
                        "\'" + words[i + 3] + "\'," +
                        "\'" + words[i + 4] + "\'," +
                        words[i + 5] + "," +
                        words[i + 6] + "," +
                        words[i + 7] + "," +
                        words[i + 8] + "," +
                        words[i + 9] + ")";

                    SqlCommand addCmd = new SqlCommand(addSql, conn);
                    try {
                        addCmd.ExecuteReader();
                        Response.Write("<script>alert(\'添加成功！\')</script>");
                        BookPanel.Visible = true;
                        MultiPanel.Visible = false;
                    }
                    catch(IOException) {
                        Response.Write("<script>alert(\'文件错误，请检查输入！\')</script>");
                    }
                    catch(Exception err) {
                        Response.Write("<script>alert(\'内容错误，请检查文件！\')</script>");
                    }
                }
                
                file.Close();
            }
            catch (Exception exp) {
                Console.WriteLine(exp.ToString());
            }
        }

        protected void Button13_Click(object sender, EventArgs e) {
            BookPanel.Visible = false;
            MultiPanel.Visible = true;
        }

        protected void Button15_Click(object sender, EventArgs e) {
            BookPanel.Visible = true;
            MultiPanel.Visible = false;
        }

        protected void Button16_Click(object sender, EventArgs e) {
            login.state = 0;
            Response.Redirect("login.aspx");
        }

        protected void Button17_Click(object sender, EventArgs e) {
            login.state = 1;
            Response.Redirect("login.aspx");
        }

        protected void Button18_Click(object sender, EventArgs e) {
            if (figure != "系统管理员") {
                Response.Write("<script>alert(\'无此权限！\')</script>");
                return;
            }
            HomePanel.Visible = false;
            UserPanel.Visible = true;
        }

        protected void Button19_Click(object sender, EventArgs e) {
            if (DropDownList4.Text != "全部") {
                SqlDataSource4.SelectCommand = "SELECT * FROM USERS";
            }
            else {
                SqlDataSource4.SelectCommand = "SELECT * FROM USERS WHERE ROLE = \'" + DropDownList4.Text + "\')";
            }
        }

        protected void Button20_Click(object sender, EventArgs e) {
            HomePanel.Visible = true;
            UserPanel.Visible = false;
        }

        protected void Button21_Click(object sender, EventArgs e) {
            SqlDataSource5.SelectCommand = "SELECT DISTINCT TITLE, NUMBER, AVAILABLENUMBER, NAME, LENDTIME FROM" +
                "(SELECT BOOK.CALLNO, TITLE, NUMBER, AVAILABLENUMBER, LENDTIME, RETURNTIME, PATRONID FROM BOOK INNER JOIN LEND ON BOOK.CALLNO = LEND.CALLNO)TMP " +
                "INNER JOIN PATRON ON TMP.PATRONID = PATRON.PATRONID " +
                "WHERE CALLNO = \'" + TextBox6.Text + "\' AND TMP.RETURNTIME IS NULL";
        }

        protected void Button22_Click(object sender, EventArgs e) {
            SqlDataSource6.SelectCommand = "SELECT DISTINCT NAME, COUNT(NAME) NUMBER, TITLE, LENDTIME FROM" +
                "(SELECT BOOK.CALLNO, TITLE, LENDTIME, RETURNTIME, PATRONID FROM BOOK INNER JOIN LEND ON BOOK.CALLNO = LEND.CALLNO)TMP " +
                "INNER JOIN PATRON ON TMP.PATRONID = PATRON.PATRONID " +
                "WHERE PATRON.PATRONID = \'" + TextBox7.Text + "\' AND TMP.RETURNTIME IS NULL " +
                "GROUP BY NAME, TITLE, LENDTIME";
        }

        protected void Button25_Click(object sender, EventArgs e) {
            DropDownList7.Visible = true;
            DropDownList8.Visible = true;
            DropDownList9.Visible = true;
            DropDownList10.Visible = true;
            DropDownList11.Visible = true;
            DropDownList12.Visible = true;
            TextBox9.Visible = true;
            TextBox10.Visible = true;
            Button26.Visible = true;
            Button25.Visible = false;
        }

        protected void Button26_Click(object sender, EventArgs e) {
            DropDownList7.Visible = false;
            DropDownList8.Visible = false;
            DropDownList9.Visible = false;
            DropDownList10.Visible = false;
            DropDownList11.Visible = false;
            DropDownList12.Visible = false;
            TextBox9.Visible = false;
            TextBox10.Visible = false;
            Button26.Visible = false;
            Button25.Visible = true;
        }

        protected void Button24_Click(object sender, EventArgs e) {
            TextBox8.Text = "";
            TextBox9.Text = "";
            TextBox10.Text = "";
        }

        private string convertAttrib(string src) {
            switch (src) {
                default:
                    return src;
                case "索书号":
                    return "CALLNO";
                case "标题":
                    return "TITLE";
                case "作者":
                    return "AUTHOR";
                case "出版社":
                    return "PUBLISHER";
                case "国际书号":
                    return "ISBN";
                case "出版日期":
                    return "PUBDATE";
                case "总页数":
                    return "PAGES";
                case "价格":
                    return "PRICE";
                case "总数":
                    return "NUMBER";
                case "库存":
                    return "AVAILABLENUMBER";
            }
        }
        private string convertOp(string src) {
            switch (src) {
                default:
                    return src;
                case "等于":
                    return " = ";
                case "不等于":
                    return " != ";
                case "大于":
                    return " >= ";
                case "小于":
                    return " <= ";
            }
        }
        private string convertCon(string src) {
            switch (src) {
                default:
                    return src;
                case "并且":
                    return " AND ";
                case "或者":
                    return " OR ";
            }
        }
        protected void Button23_Click(object sender, EventArgs e) {
            string cmdSql = "SELECT * FROM BOOK";
            if (DropDownList9.Visible) {
                if (TextBox8.Text != "")
                    cmdSql += " WHERE ";
                cmdSql += convertAttrib(DropDownList6.SelectedValue);
                cmdSql += convertOp(DropDownList5.SelectedValue);
                if (DropDownList6.SelectedIndex < 5)
                    cmdSql += "\'" + TextBox8.Text + "\'";
                else
                    cmdSql += TextBox8.Text;

                if (TextBox9.Text != "")
                    cmdSql += convertCon(DropDownList9.SelectedValue);
                cmdSql += convertAttrib(DropDownList8.SelectedValue);
                cmdSql += convertOp(DropDownList7.SelectedValue);
                if (DropDownList8.SelectedIndex < 5)
                    cmdSql += "\'" + TextBox9.Text + "\'";
                else
                    cmdSql += TextBox9.Text;

                if (TextBox10.Text != "")
                    cmdSql += convertCon(DropDownList12.SelectedValue);
                cmdSql += convertAttrib(DropDownList11.SelectedValue);
                cmdSql += convertOp(DropDownList10.SelectedValue);
                if (DropDownList11.SelectedIndex < 5)
                    cmdSql += "\'" + TextBox10.Text + "\'";
                else
                    cmdSql += TextBox10.Text;
            }
            else {
                if (TextBox8.Text != "")
                    cmdSql += " WHERE ";
                cmdSql += convertAttrib(DropDownList6.SelectedValue);
                cmdSql += convertOp(DropDownList5.SelectedValue);
                if (DropDownList6.SelectedIndex < 5)
                    cmdSql += "\'" + TextBox8.Text + "\'";
                else
                    cmdSql += TextBox8.Text;
            }
            SqlDataSource7.SelectCommand = cmdSql;
        }
    }
}