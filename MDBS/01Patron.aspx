<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="01Patron.aspx.cs" Inherits="Book._01Patron" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
        查询条件：<asp:TextBox ID="txtKey" runat="server"></asp:TextBox>
        <asp:Button ID="Button1" runat="server" Text="查询" />
        <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" DataKeyNames="PatronID" DataSourceID="SqlDataSource1" EmptyDataText="没有可显示的数据记录。">
            <Columns>
                <asp:BoundField DataField="PatronID" HeaderText="PatronID" ReadOnly="True" SortExpression="PatronID" />
                <asp:BoundField DataField="Name" HeaderText="Name" SortExpression="Name" />
                <asp:BoundField DataField="Gender" HeaderText="Gender" SortExpression="Gender" />
                <asp:BoundField DataField="BirthDate" HeaderText="BirthDate" SortExpression="BirthDate" />
                <asp:BoundField DataField="Type" HeaderText="Type" SortExpression="Type" />
                <asp:BoundField DataField="Department" HeaderText="Department" SortExpression="Department" />
            </Columns>
        </asp:GridView>
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" DeleteCommand="DELETE FROM [Patron] WHERE [PatronID] = @PatronID" InsertCommand="INSERT INTO [Patron] ([PatronID], [Name], [Gender], [BirthDate], [Type], [Department]) VALUES (@PatronID, @Name, @Gender, @BirthDate, @Type, @Department)" SelectCommand="SELECT * FROM [Patron] WHERE (([Name] LIKE '%' + @Name + '%') OR ([PatronID] LIKE '%' + @PatronID + '%') OR([Gender] LIKE '%' + @Gender + '%') OR([Department] LIKE '%' + @Department + '%'))" UpdateCommand="UPDATE [Patron] SET [Name] = @Name, [Gender] = @Gender, [BirthDate] = @BirthDate, [Type] = @Type, [Department] = @Department WHERE [PatronID] = @PatronID">
            <DeleteParameters>
                <asp:Parameter Name="PatronID" Type="String" />
            </DeleteParameters>
            <InsertParameters>
                <asp:Parameter Name="PatronID" Type="String" />
                <asp:Parameter Name="Name" Type="String" />
                <asp:Parameter Name="Gender" Type="String" />
                <asp:Parameter DbType="Date" Name="BirthDate" />
                <asp:Parameter Name="Type" Type="String" />
                <asp:Parameter Name="Department" Type="String" />
            </InsertParameters>
            <SelectParameters>
                <asp:ControlParameter ControlID="txtKey" ConvertEmptyStringToNull="False" Name="Name" PropertyName="Text" Type="String" />
                <asp:ControlParameter ControlID="txtKey" Name="PatronID" PropertyName="Text" Type="String" />
                <asp:ControlParameter ControlID="txtKey" Name="Gender" PropertyName="Text" Type="String" />
                <asp:ControlParameter ControlID="txtKey" Name="Department" PropertyName="Text" Type="String" />
            </SelectParameters>
            <UpdateParameters>
                <asp:Parameter Name="Name" Type="String" />
                <asp:Parameter Name="Gender" Type="String" />
                <asp:Parameter DbType="Date" Name="BirthDate" />
                <asp:Parameter Name="Type" Type="String" />
                <asp:Parameter Name="Department" Type="String" />
                <asp:Parameter Name="PatronID" Type="String" />
            </UpdateParameters>
        </asp:SqlDataSource>
    </form>
</body>
</html>
