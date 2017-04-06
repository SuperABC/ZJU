<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="hw3.aspx.cs" Inherits="Book.hw3" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        书名：<asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
&nbsp;作者：<asp:TextBox ID="TextBox2" runat="server"></asp:TextBox>
        <asp:Button ID="Button1" runat="server" Text="查询" OnClick="Button1_Click" />
        <br />
        <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" DataSourceID="SqlDataSource1">
            <Columns>
                <asp:BoundField DataField="CallNo" HeaderText="CallNo" SortExpression="CallNo" />
                <asp:BoundField DataField="Title" HeaderText="Title" SortExpression="Title" />
                <asp:BoundField DataField="Author" HeaderText="Author" SortExpression="Author" />
                <asp:BoundField DataField="Publisher" HeaderText="Publisher" SortExpression="Publisher" />
                <asp:BoundField DataField="ISBN" HeaderText="ISBN" SortExpression="ISBN" />
                <asp:BoundField DataField="PubDate" HeaderText="PubDate" SortExpression="PubDate" />
                <asp:BoundField DataField="Pages" HeaderText="Pages" SortExpression="Pages" />
                <asp:BoundField DataField="Price" HeaderText="Price" SortExpression="Price" />
                <asp:BoundField DataField="PatronID" HeaderText="PatronID" SortExpression="PatronID" />
                <asp:BoundField DataField="LendTime" HeaderText="LendTime" SortExpression="LendTime" />
                <asp:BoundField DataField="ReturnTime" HeaderText="ReturnTime" SortExpression="ReturnTime" />
            </Columns>
        </asp:GridView>
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>"
            SelectCommand="SELECT Book.CallNo, Book.Title, Book.Author, Book.Publisher, Book.ISBN, Book.PubDate, Book.Pages, Book.Price, Lend.PatronID, Lend.LendTime, Lend.ReturnTime FROM Book INNER JOIN Lend ON Book.CallNo = Lend.CallNo WHERE (Book.Title LIKE '%' + @Title + '%') AND (Book.Author LIKE '%' + @Author + '%')">
            <SelectParameters>
                <asp:ControlParameter ControlID="textBox1" ConvertEmptyStringToNull="True" Name="Title" PropertyName="Text" Type="String" />
                <asp:ControlParameter ControlID="textBox2" ConvertEmptyStringToNull="True" Name="Author" PropertyName="Text" Type="String" />
            </SelectParameters>
        </asp:SqlDataSource>
    
    </div>
    </form>
</body>
</html>
