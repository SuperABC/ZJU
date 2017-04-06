<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="login.aspx.cs" Inherits="Book.login" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <asp:Image ID="Image1" runat="server" Height="80px" Width="720px" ImageUrl="Title.jpg" AlternateText="Picture not found!"/>
    
        <br />
        <br />
        用户名:&nbsp; <asp:TextBox ID="NameText" runat="server"></asp:TextBox>
        <br />
        <br />
        密码:&nbsp;&nbsp; <asp:TextBox ID="WordText" runat="server"></asp:TextBox>
        <br />
        <br />
        <asp:Button ID="Confirm" runat="server" OnClick="Confirm_Click" Text="登录" />
    
    </div>
    </form>
</body>
</html>
