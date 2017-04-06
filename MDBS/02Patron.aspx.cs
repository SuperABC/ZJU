using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace Book {
    public partial class _02Patron : System.Web.UI.Page {
        protected void Page_Load(object sender, EventArgs e) {

        }

        protected void Button1_Click(object sender, EventArgs e) {
            if (TextBox1.Text == "")
                SqlDataSource2.SelectCommand = "SELECT * FROM [Patron] WHERE (([Name] = '') OR"+ 
               "([Name] IS NULL) OR([Department] = @Department))";
        }
    }
}