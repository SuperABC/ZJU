<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="10Lend.aspx.cs" Inherits="Book._10Lend" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        姓名：<asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
&nbsp;书名：<asp:TextBox ID="TextBox2" runat="server"></asp:TextBox>
        &nbsp;借书日期：<asp:DropDownList ID="DropDownList1" runat="server">
            <asp:ListItem>&gt;</asp:ListItem>
            <asp:ListItem>=</asp:ListItem>
            <asp:ListItem>&lt;</asp:ListItem>
        </asp:DropDownList>
        <asp:TextBox ID="TextBox3" runat="server"></asp:TextBox>
        <asp:Button ID="Button1" runat="server" style="margin-bottom: 0px" Text="查询" OnClick="Button1_Click" />
        <br />
        <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" DataKeyNames="CallNo,PatronID,LendTime" DataSourceID="SqlDataSource1">
            <Columns>
                <asp:BoundField DataField="Name" HeaderText="Name" SortExpression="Name" />
                <asp:BoundField DataField="Title" HeaderText="Title" SortExpression="Title" />
                <asp:BoundField DataField="CallNo" HeaderText="CallNo" ReadOnly="True" SortExpression="CallNo" />
                <asp:BoundField DataField="PatronID" HeaderText="PatronID" ReadOnly="True" SortExpression="PatronID" />
                <asp:BoundField DataField="LendTime" HeaderText="LendTime" ReadOnly="True" SortExpression="LendTime" />
                <asp:BoundField DataField="ReturnTime" HeaderText="ReturnTime" SortExpression="ReturnTime" />
            </Columns>
        </asp:GridView>
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>"
            SelectCommand="SELECT Patron.Name, Book.Title, Lend.CallNo, Lend.PatronID, Lend.LendTime, Lend.ReturnTime FROM Book INNER JOIN Lend ON Book.CallNo = Lend.CallNo INNER JOIN Patron ON Lend.PatronID = Patron.PatronID WHERE (Patron.Name LIKE '%' + @Name + '%') AND (Book.Title LIKE '%' + @Title + '%')">
            <SelectParameters>
                <asp:ControlParameter ControlID="textBox1" ConvertEmptyStringToNull="True" Name="Name" PropertyName="Text" Type="String" />
                <asp:ControlParameter ControlID="textBox2" ConvertEmptyStringToNull="True" Name="Title" PropertyName="Text" Type="String" />
                <asp:ControlParameter ControlID="DropDownList1" ConvertEmptyStringToNull="True" Name="LendTime" PropertyName="Text" Type="String" />
            </SelectParameters>
        </asp:SqlDataSource>
    </form>
</body>
</html>
