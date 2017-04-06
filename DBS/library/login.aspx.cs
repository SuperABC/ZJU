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
        protected void Page_Load(object sender, EventArgs e) {

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
            string strConn = ConfigurationManager.ConnectionStrings["TSGConnectionString1"].ConnectionString;
            SqlConnection conn = new SqlConnection(strConn);
            DataSet ds = new DataSet();
            string lendSql = "SELECT * FROM USERS WHERE NAME = \'" + NameText.Text + "\' AND WORD = \'" + WordText.Text + "\'";
            conn.Open();
            SqlCommand lendCmd = new SqlCommand(lendSql, conn);
            try {
                SqlDataReader dr = lendCmd.ExecuteReader();
                if (dr.Read()) Response.Redirect("library.aspx");
                else Response.Write("<script>alert('用户名或密码错误！')</script>");
            }
            catch {
                Response.Write("<script>alert('系统错误，请检查输入！')</script>");
            }
        }
    }
}