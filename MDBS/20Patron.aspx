<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="20Patron.aspx.cs" Inherits="Book._20Patron" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <asp:FormView ID="FormView1" runat="server" AllowPaging="True" DataKeyNames="PatronID" DataSourceID="SqlDataSource1">
            <EditItemTemplate>
                PatronID:
                <asp:Label ID="PatronIDLabel1" runat="server" Text='<%# Eval("PatronID") %>' />
                <br />
                Name:
                <asp:TextBox ID="NameTextBox" runat="server" Text='<%# Bind("Name") %>' />
                <br />
                Gender:
                <asp:TextBox ID="GenderTextBox" runat="server" Text='<%# Bind("Gender") %>' />
                <br />
                BirthDate:
                <asp:TextBox ID="BirthDateTextBox" runat="server" Text='<%# Bind("BirthDate") %>' />
                <br />
                Type:
                <asp:TextBox ID="TypeTextBox" runat="server" Text='<%# Bind("Type") %>' />
                <br />
                Department:
                <asp:TextBox ID="DepartmentTextBox" runat="server" Text='<%# Bind("Department") %>' />
                <br />
                <asp:LinkButton ID="UpdateButton" runat="server" CausesValidation="True" CommandName="Update" Text="更新" />
                &nbsp;<asp:LinkButton ID="UpdateCancelButton" runat="server" CausesValidation="False" CommandName="Cancel" Text="取消" />
            </EditItemTemplate>
            <InsertItemTemplate>
                PatronID:
                <asp:TextBox ID="PatronIDTextBox" runat="server" Text='<%# Bind("PatronID") %>' />
                <br />
                Name:
                <asp:TextBox ID="NameTextBox" runat="server" Text='<%# Bind("Name") %>' />
                <br />
                Gender:
                <asp:TextBox ID="GenderTextBox" runat="server" Text='<%# Bind("Gender") %>' />
                <br />
                BirthDate:
                <asp:TextBox ID="BirthDateTextBox" runat="server" Text='<%# Bind("BirthDate") %>' />
                <br />
                Type:
                <asp:TextBox ID="TypeTextBox" runat="server" Text='<%# Bind("Type") %>' />
                <br />
                Department:
                <asp:TextBox ID="DepartmentTextBox" runat="server" Text='<%# Bind("Department") %>' />
                <br />
                <asp:LinkButton ID="InsertButton" runat="server" CausesValidation="True" CommandName="Insert" Text="插入" />
                &nbsp;<asp:LinkButton ID="InsertCancelButton" runat="server" CausesValidation="False" CommandName="Cancel" Text="取消" />
            </InsertItemTemplate>
            <ItemTemplate>
                PatronID:
                <asp:Label ID="PatronIDLabel" runat="server" Text='<%# Eval("PatronID") %>' />
                <br />
                Name:
                <asp:Label ID="NameLabel" runat="server" Text='<%# Bind("Name") %>' />
                <br />
                Gender:
                <asp:Label ID="GenderLabel" runat="server" Text='<%# Bind("Gender") %>' />
                <br />
                BirthDate:
                <asp:Label ID="BirthDateLabel" runat="server" Text='<%# Bind("BirthDate") %>' />
                <br />
                Type:
                <asp:Label ID="TypeLabel" runat="server" Text='<%# Bind("Type") %>' />
                <br />
                Department:
                <asp:Label ID="DepartmentLabel" runat="server" Text='<%# Bind("Department") %>' />
                <br />
                <asp:LinkButton ID="EditButton" runat="server" CausesValidation="False" CommandName="Edit" Text="编辑" />
                &nbsp;<asp:LinkButton ID="DeleteButton" runat="server" CausesValidation="False" CommandName="Delete" Text="删除" />
                &nbsp;<asp:LinkButton ID="NewButton" runat="server" CausesValidation="False" CommandName="New" Text="新建" />
            </ItemTemplate>
        </asp:FormView>
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" DeleteCommand="DELETE FROM [Patron] WHERE [PatronID] = @PatronID" InsertCommand="INSERT INTO [Patron] ([PatronID], [Name], [Gender], [BirthDate], [Type], [Department]) VALUES (@PatronID, @Name, @Gender, @BirthDate, @Type, @Department)" SelectCommand="SELECT * FROM [Patron]" UpdateCommand="UPDATE [Patron] SET [Name] = @Name, [Gender] = @Gender, [BirthDate] = @BirthDate, [Type] = @Type, [Department] = @Department WHERE [PatronID] = @PatronID">
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
            <UpdateParameters>
                <asp:Parameter Name="Name" Type="String" />
                <asp:Parameter Name="Gender" Type="String" />
                <asp:Parameter DbType="Date" Name="BirthDate" />
                <asp:Parameter Name="Type" Type="String" />
                <asp:Parameter Name="Department" Type="String" />
                <asp:Parameter Name="PatronID" Type="String" />
            </UpdateParameters>
        </asp:SqlDataSource>
    
    </div>
    </form>
</body>
</html>
