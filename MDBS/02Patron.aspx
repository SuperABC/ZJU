<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="02Patron.aspx.cs" Inherits="Book._02Patron" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        <p>
            姓名：<asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
&nbsp;部门：<asp:DropDownList ID="DropDownList1" runat="server" DataSourceID="SqlDataSource1" DataTextField="Department" DataValueField="Department">
            </asp:DropDownList>
            <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="查询" />
            <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" SelectCommand="SELECT DISTINCT [Department] FROM [Patron]"></asp:SqlDataSource>
            <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" DataKeyNames="PatronID" DataSourceID="SqlDataSource2">
                <Columns>
                    <asp:BoundField DataField="PatronID" HeaderText="PatronID" ReadOnly="True" SortExpression="PatronID" />
                    <asp:BoundField DataField="Name" HeaderText="Name" SortExpression="Name" />
                    <asp:BoundField DataField="Gender" HeaderText="Gender" SortExpression="Gender" />
                    <asp:BoundField DataField="BirthDate" HeaderText="BirthDate" SortExpression="BirthDate" />
                    <asp:BoundField DataField="Type" HeaderText="Type" SortExpression="Type" />
                    <asp:BoundField DataField="Department" HeaderText="Department" SortExpression="Department" />
                </Columns>
            </asp:GridView>
            <asp:SqlDataSource ID="SqlDataSource2" runat="server" CancelSelectOnNullParameter="False" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" SelectCommand="SELECT * FROM [Patron] WHERE (([Department] = @Department) OR([Name] LIKE '%' + @Name + '%'))">
                <SelectParameters>
                    <asp:ControlParameter ControlID="DropDownList1" ConvertEmptyStringToNull="False" Name="Department" PropertyName="SelectedValue" Type="String" />
                    <asp:ControlParameter ControlID="TextBox1" Name="Name" PropertyName="Text" Type="String" />
                </SelectParameters>
            </asp:SqlDataSource>
        </p>
    </form>
</body>
</html>
