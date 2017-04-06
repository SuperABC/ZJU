<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="22Patron.aspx.cs" Inherits="Book._22Patron" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        <asp:DetailsView ID="DetailsView1" runat="server" AutoGenerateRows="False" DataKeyNames="PatronID" DataSourceID="SqlDataSource1" Height="50px" OnPageIndexChanging="DetailsView1_PageIndexChanging" Width="280px" AllowPaging="True">
            <Fields>
                <asp:BoundField DataField="PatronID" HeaderText="借书证号" ReadOnly="True" SortExpression="PatronID">
                <HeaderStyle BackColor="#CCCCCC" Width="80px" />
                </asp:BoundField>
                <asp:BoundField DataField="Name" HeaderText="读者姓名" SortExpression="Name">
                <HeaderStyle BackColor="#CCCCCC" Width="80px" />
                </asp:BoundField>
                <asp:TemplateField HeaderText="性别" SortExpression="Gender">
                    <EditItemTemplate>
                        <asp:RadioButtonList ID="RadioButtonList1" runat="server" RepeatDirection="Horizontal" SelectedValue='<%# Bind("Gender") %>'>
                            <asp:ListItem>男</asp:ListItem>
                            <asp:ListItem>女</asp:ListItem>
                        </asp:RadioButtonList>
                    </EditItemTemplate>
                    <InsertItemTemplate>
                        <asp:TextBox ID="TextBox1" runat="server" Text='<%# Bind("Gender") %>'></asp:TextBox>
                    </InsertItemTemplate>
                    <ItemTemplate>
                        <asp:Label ID="Label1" runat="server" Text='<%# Bind("Gender") %>'></asp:Label>
                    </ItemTemplate>
                    <HeaderStyle BackColor="#CCCCCC" Width="80px" />
                </asp:TemplateField>
                <asp:TemplateField HeaderText="出生日期" SortExpression="BirthDate">
                    <EditItemTemplate>
                        <asp:Calendar ID="Calendar1" runat="server" SelectedDate='<%# Bind("BirthDate") %>'></asp:Calendar>
                    </EditItemTemplate>
                    <InsertItemTemplate>
                        <asp:TextBox ID="TextBox4" runat="server" Text='<%# Bind("BirthDate") %>'></asp:TextBox>
                    </InsertItemTemplate>
                    <ItemTemplate>
                        <asp:Label ID="Label4" runat="server" Text='<%# Bind("BirthDate") %>'></asp:Label>
                    </ItemTemplate>
                    <HeaderStyle BackColor="#CCCCCC" Width="80px" />
                </asp:TemplateField>
                <asp:TemplateField HeaderText="类型" SortExpression="Type">
                    <EditItemTemplate>
                        <asp:RadioButtonList ID="RadioButtonList2" runat="server" RepeatDirection="Horizontal" SelectedValue='<%# Bind("Type") %>'>
                            <asp:ListItem>教师</asp:ListItem>
                            <asp:ListItem>学生</asp:ListItem>
                        </asp:RadioButtonList>
                    </EditItemTemplate>
                    <InsertItemTemplate>
                        <asp:TextBox ID="TextBox2" runat="server" Text='<%# Bind("Type") %>'></asp:TextBox>
                    </InsertItemTemplate>
                    <ItemTemplate>
                        <asp:Label ID="Label2" runat="server" Text='<%# Bind("Type") %>'></asp:Label>
                    </ItemTemplate>
                    <HeaderStyle BackColor="#CCCCCC" Width="80px" />
                </asp:TemplateField>
                <asp:TemplateField HeaderText="院系" SortExpression="Department">
                    <EditItemTemplate>
                        <asp:DropDownList ID="DropDownList1" runat="server" SelectedValue='<%# Bind("Department") %>'>
                            <asp:ListItem>电信学院</asp:ListItem>
                            <asp:ListItem>工商学院</asp:ListItem>
                            <asp:ListItem>计算机学院</asp:ListItem>
                            <asp:ListItem>数学学院</asp:ListItem>
                        </asp:DropDownList>
                    </EditItemTemplate>
                    <InsertItemTemplate>
                        <asp:TextBox ID="TextBox3" runat="server" Text='<%# Bind("Department") %>'></asp:TextBox>
                    </InsertItemTemplate>
                    <ItemTemplate>
                        <asp:Label ID="Label3" runat="server" Text='<%# Bind("Department") %>'></asp:Label>
                    </ItemTemplate>
                    <HeaderStyle BackColor="#CCCCCC" Width="80px" />
                </asp:TemplateField>
                <asp:CommandField ShowDeleteButton="True" ShowEditButton="True" ShowInsertButton="True" />
            </Fields>
        </asp:DetailsView>
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
