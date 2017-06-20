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
    public partial class login : System.Web.UI.Page {
        public static int state = 0;
        Random rd = new Random();
        static int checkNum = 0;
        static bool reload = true;
        protected void Page_Load(object sender, EventArgs e) {
            if (reload) {
                checkNum = rd.Next() % 10000;
                reload = false;
            }
            Image2.ImageUrl = "src//0" + checkNum / 1000 + ".bmp";
            Image3.ImageUrl = "src//0" + checkNum / 100 % 10 + ".bmp";
            Image4.ImageUrl = "src//0" + checkNum / 10 % 10 + ".bmp";
            Image5.ImageUrl = "src//0" + checkNum % 10 + ".bmp";
            if (state == 0) {
                LoginPanel.Visible = true;
                ChangePanel.Visible = false;
            }
            else {
                LoginPanel.Visible = false;
                ChangePanel.Visible = true;
            }
        }

        protected void Confirm_Click(object sender, EventArgs e) {
            if (NameText.Text == "") {
                Response.Write("<script>alert('用户名不能为空！')</script>");
                NameText.Focus();
                return;
            }
            else if (WordText.Text == "") {
                Response.Write("<script>alert('密码不能为空！')</script>");
                WordText.Focus();
                return;
            }
            else if (CheckText.Text != checkNum.ToString()) {
                Response.Write("<script>alert('验证码错误！')</script>");
                CheckText.Focus();
                return;
            }
            string strConn = ConfigurationManager.ConnectionStrings["TSGConnectionString1"].ConnectionString;
            SqlConnection conn = new SqlConnection(strConn);
            DataSet ds = new DataSet();
            conn.Open();
            if (DropDownList1.SelectedValue == "普通读者") {
                string lendSql = "SELECT * FROM PATRON WHERE PATRONID = \'" + NameText.Text + "\' AND PASSWORD = \'" + WordText.Text + "\'";
                SqlCommand lendCmd = new SqlCommand(lendSql, conn);
                try {
                    SqlDataReader dr = lendCmd.ExecuteReader();
                    if (dr.Read()) Response.Redirect("library.aspx");
                    else Response.Write("<script>alert('用户名或密码错误！')</script>");
                }
                catch {
                    Response.Write("<script>alert('系统错误，请检查输入！')</script>");
                }
                finally {
                    library.figure = "普通读者";
                }
            }
            else {
                string lendSql = "SELECT * FROM USERS WHERE USERID = \'" + NameText.Text + 
                    "\' AND PASSWORD = \'" + WordText.Text +
                    "\' AND ROLE = \'" + DropDownList1.SelectedValue + "\'";
                SqlCommand lendCmd = new SqlCommand(lendSql, conn);
                try {
                    SqlDataReader dr = lendCmd.ExecuteReader();
                    if (dr.Read()) {
                        library.figure = DropDownList1.SelectedValue;
                        Response.Redirect("library.aspx");
                    }
                    else Response.Write("<script>alert('用户名或密码错误！')</script>");
                }
                catch (Exception err) {
                    Response.Write("<script>alert('系统错误，请检查输入！')</script>");
                }
                finally {
                    library.figure = DropDownList1.SelectedValue;
                }
            }
        }

        protected void ChangeButton_Click(object sender, EventArgs e) {
            string strConn = ConfigurationManager.ConnectionStrings["TSGConnectionString1"].ConnectionString;
            SqlConnection conn = new SqlConnection(strConn);
            DataSet ds = new DataSet();
            string checkSql, changeSql;
            if (DropDownList2.SelectedValue == "普通读者") {
                checkSql = "SELECT PATRONID, PASSWORD FROM PATRON WHERE PATRONID = \'" + ChangeUserText.Text + "\' AND PASSWORD = \'" + ChangePwText.Text + "\'";
                changeSql = "UPDATE PATRON SET PASSWORD = \'" + NewPwText.Text + "\' WHERE PATRONID = \'" + ChangeUserText.Text + "\'";
            }
            else {
                checkSql = "SELECT * FROM USERS WHERE USERID = \'" + ChangeUserText.Text + "\' AND PASSWORD = \'" + ChangePwText.Text + "\' AND ROLE = \'" + DropDownList2.SelectedValue + "\'";
                changeSql = "UPDATE USERS SET PASSWORD = \'" + NewPwText.Text + "\' WHERE USERID = \'" + ChangeUserText.Text + "\'";
            }
            conn.Open();
            SqlCommand checkCmd = new SqlCommand(checkSql, conn);
            try {
                SqlDataReader checkReader = checkCmd.ExecuteReader();
                if (!checkReader.Read()) {
                    Response.Write("<script>alert('用户名或密码错误！')</script>");
                    return;
                }
                else {
                    if (NewPwText.Text != AgainPwText.Text) {
                        Response.Write("<script>alert('两次密码输入不一样！')</script>");
                        return;
                    }
                    int bit = 0, hard = 0;
                    for (int i = 0; i < NewPwText.Text.Length; i++) {
                        if (NewPwText.Text[i] >= 48 && NewPwText.Text[i] <= 57) {
                            bit |= 1;
                        }
                        else if (NewPwText.Text[i] >= 65 && NewPwText.Text[i] <= 90) {
                            bit |= 2;
                        }
                        else if (NewPwText.Text[i] >= 97 && NewPwText.Text[i] <= 122) {
                            bit |= 4;
                        }
                        else {
                            bit |= 8;
                        }
                    }
                    for (int i = 0; i < 4; i++) {
                        if (bit % 2 == 1) hard++;
                        bit >>= 1;
                    }
                    if (NewPwText.Text.Length < 6 || hard < 2) {
                        Response.Write("<script>alert('密码强度不够！')</script>");
                        return;
                    }
                    conn.Close();
                    conn.Open();
                    SqlCommand changeCmd = new SqlCommand(changeSql, conn);
                    SqlDataReader changeReader = changeCmd.ExecuteReader();
                    Response.Write("<script>alert('成功更改密码！')</script>");
                    ChangePanel.Visible = false;
                    LoginPanel.Visible = true;
                    NameText.Text = ChangeUserText.Text;
                    WordText.Text = NewPwText.Text;
                }
            }
            catch (Exception excp) {
                string err = excp.Message;
                Response.Write("<script>alert('系统错误，请检查输入！')</script>");
            }
        }

        protected void BackLogin_Click(object sender, EventArgs e) {
            Response.Redirect("library.aspx");
        }
    }
}