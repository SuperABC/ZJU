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
    
        <asp:Panel ID="LoginPanel" runat="server" Visible="true">
        <br />
        <br />
        用户名:&nbsp; <asp:TextBox ID="NameText" runat="server"></asp:TextBox>
        <br />
        <br />
        密码:&nbsp;&nbsp; <asp:TextBox ID="WordText" runat="server"></asp:TextBox>
            <br />
            <br />
            验证码:&nbsp;
            <asp:TextBox ID="CheckText" runat="server"></asp:TextBox>
            <asp:Image ID="Image2" runat="server" Width="20px" />
            <asp:Image ID="Image3" runat="server" Width="16px" />
            <asp:Image ID="Image4" runat="server" Width="22px" />
            <asp:Image ID="Image5" runat="server" />
        <br />
        <br />
        身份:&nbsp;&nbsp;
        <asp:DropDownList ID="DropDownList1" runat="server">
            <asp:ListItem>普通读者</asp:ListItem>
            <asp:ListItem>系统管理员</asp:ListItem>
            <asp:ListItem>图书管理员</asp:ListItem>
            <asp:ListItem>读者管理员</asp:ListItem>
            <asp:ListItem>借还操作员</asp:ListItem>
        </asp:DropDownList>
        <br />
        <br />
        <asp:Button ID="Confirm" runat="server" OnClick="Confirm_Click" Text="登录" />
        </asp:Panel>

        <asp:Panel ID="ChangePanel" runat="server" Visible ="false">
            <br />
            <br />
            用户名:&nbsp;
            <asp:TextBox ID="ChangeUserText" runat="server"></asp:TextBox>
            <br />
            <br />
            旧密码:&nbsp;
            <asp:TextBox ID="ChangePwText" runat="server"></asp:TextBox>
            <br />
            <br />
            新密码:&nbsp;
            <asp:TextBox ID="NewPwText" runat="server"></asp:TextBox>
            <br />
            <br />
            重复:&nbsp;&nbsp;
            <asp:TextBox ID="AgainPwText" runat="server"></asp:TextBox>
            <br />
            <br />
            身份:&nbsp;&nbsp;
            <asp:DropDownList ID="DropDownList2" runat="server">
                <asp:ListItem>普通读者</asp:ListItem>
                <asp:ListItem>系统管理员</asp:ListItem>
                <asp:ListItem>图书管理员</asp:ListItem>
                <asp:ListItem>读者管理员</asp:ListItem>
                <asp:ListItem>借还操作员</asp:ListItem>
            </asp:DropDownList>
            <br />
            <br />
            <asp:Button ID="ChangeButton" runat="server" Text="更改" OnClick="ChangeButton_Click" />
            <asp:Button ID="BackLogin" runat="server" OnClick="BackLogin_Click" Text="返回" />
        </asp:Panel>
    </div>
    </form>
</body>
</html>
