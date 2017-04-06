using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Book {
    public partial class hw3 : System.Web.UI.Page {
        protected void Page_Load(object sender, EventArgs e) {

        }

        protected void Button1_Click(object sender, EventArgs e) {
            if (TextBox1.Text.Trim() == "" && TextBox2.Text.Trim() == "") {
                SqlDataSource1.SelectParameters["Title"].ConvertEmptyStringToNull = true;
                SqlDataSource1.SelectParameters["Author"].ConvertEmptyStringToNull = true;
            }
            else {
                SqlDataSource1.SelectParameters["Title"].ConvertEmptyStringToNull = false;
                SqlDataSource1.SelectParameters["Author"].ConvertEmptyStringToNull = false;
            }
        }
    }
}