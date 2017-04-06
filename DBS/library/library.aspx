<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="library.aspx.cs" Inherits="Book.library" %>

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
        <br />
        馆藏查询<br />
    
        <br />
    
        输入内容：<asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
        <asp:DropDownList ID="DropDownList1" runat="server" Height="16px" Width="130px">
            <asp:ListItem>CallNo</asp:ListItem>
            <asp:ListItem>Title</asp:ListItem>
            <asp:ListItem>Author</asp:ListItem>
            <asp:ListItem>Publisher</asp:ListItem>
            <asp:ListItem>ISBN</asp:ListItem>
            <asp:ListItem>PubDate</asp:ListItem>
            <asp:ListItem>Pages</asp:ListItem>
            <asp:ListItem>Price</asp:ListItem>
            <asp:ListItem>Number</asp:ListItem>
            <asp:ListItem>AvailableNumber</asp:ListItem>
        </asp:DropDownList>
        <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="查询" Width="40px" />
        <br />
        <br />
        <asp:FormView ID="FormView1" runat="server" AllowPaging="True" DataKeyNames="CallNo" DataSourceID="SqlDataSource1" OnPageIndexChanging="FormView1_PageIndexChanging" BackColor="LightGoldenrodYellow" BorderColor="Tan" BorderWidth="1px" CellPadding="2" ForeColor="Black" Width="400px">
            <EditItemTemplate>
                CallNo:
                <asp:Label ID="CallNoLabel1" runat="server" Text='<%# Eval("CallNo") %>' />
                <br />
                Title:
                <asp:TextBox ID="TitleTextBox" runat="server" Text='<%# Bind("Title") %>' />
                <br />
                Author:
                <asp:TextBox ID="AuthorTextBox" runat="server" Text='<%# Bind("Author") %>' />
                <br />
                Publisher:
                <asp:TextBox ID="PublisherTextBox" runat="server" Text='<%# Bind("Publisher") %>' />
                <br />
                ISBN:
                <asp:TextBox ID="ISBNTextBox" runat="server" Text='<%# Bind("ISBN") %>' />
                <br />
                PubDate:
                <asp:TextBox ID="PubDateTextBox" runat="server" Text='<%# Bind("PubDate") %>' />
                <br />
                Pages:
                <asp:TextBox ID="PagesTextBox" runat="server" Text='<%# Bind("Pages") %>' />
                <br />
                Price:
                <asp:TextBox ID="PriceTextBox" runat="server" Text='<%# Bind("Price") %>' />
                <br />
                Number:
                <asp:TextBox ID="NumberTextBox" runat="server" Text='<%# Bind("Number") %>' />
                <br />
                AvailableNumber:
                <asp:TextBox ID="AvailableNumberTextBox" runat="server" Text='<%# Bind("AvailableNumber") %>' />
                <br />
                <asp:LinkButton ID="UpdateButton" runat="server" CausesValidation="True" CommandName="Update" Text="更新" />
                &nbsp;<asp:LinkButton ID="UpdateCancelButton" runat="server" CausesValidation="False" CommandName="Cancel" Text="取消" />
            </EditItemTemplate>
            <EditRowStyle BackColor="DarkSlateBlue" ForeColor="GhostWhite" />
            <FooterStyle BackColor="Tan" />
            <HeaderStyle BackColor="Tan" Font-Bold="True" />
            <InsertItemTemplate>
                CallNo:
                <asp:TextBox ID="CallNoTextBox" runat="server" Text='<%# Bind("CallNo") %>' />
                <br />
                Title:
                <asp:TextBox ID="TitleTextBox" runat="server" Text='<%# Bind("Title") %>' />
                <br />
                Author:
                <asp:TextBox ID="AuthorTextBox" runat="server" Text='<%# Bind("Author") %>' />
                <br />
                Publisher:
                <asp:TextBox ID="PublisherTextBox" runat="server" Text='<%# Bind("Publisher") %>' />
                <br />
                ISBN:
                <asp:TextBox ID="ISBNTextBox" runat="server" Text='<%# Bind("ISBN") %>' />
                <br />
                PubDate:
                <asp:TextBox ID="PubDateTextBox" runat="server" Text='<%# Bind("PubDate") %>' />
                <br />
                Pages:
                <asp:TextBox ID="PagesTextBox" runat="server" Text='<%# Bind("Pages") %>' />
                <br />
                Price:
                <asp:TextBox ID="PriceTextBox" runat="server" Text='<%# Bind("Price") %>' />
                <br />
                Number:
                <asp:TextBox ID="NumberTextBox" runat="server" Text='<%# Bind("Number") %>' />
                <br />
                AvailableNumber:
                <asp:TextBox ID="AvailableNumberTextBox" runat="server" Text='<%# Bind("AvailableNumber") %>' />
                <br />
                <asp:LinkButton ID="InsertButton" runat="server" CausesValidation="True" CommandName="Insert" Text="插入" />
                &nbsp;<asp:LinkButton ID="InsertCancelButton" runat="server" CausesValidation="False" CommandName="Cancel" Text="取消" />
            </InsertItemTemplate>
            <ItemTemplate>
                CallNo:
                <asp:Label ID="CallNoLabel" runat="server" Text='<%# Eval("CallNo") %>' />
                <br />
                Title:
                <asp:Label ID="TitleLabel" runat="server" Text='<%# Bind("Title") %>' />
                <br />
                Author:
                <asp:Label ID="AuthorLabel" runat="server" Text='<%# Bind("Author") %>' />
                <br />
                Publisher:
                <asp:Label ID="PublisherLabel" runat="server" Text='<%# Bind("Publisher") %>' />
                <br />
                ISBN:
                <asp:Label ID="ISBNLabel" runat="server" Text='<%# Bind("ISBN") %>' />
                <br />
                PubDate:
                <asp:Label ID="PubDateLabel" runat="server" Text='<%# Bind("PubDate") %>' />
                <br />
                Pages:
                <asp:Label ID="PagesLabel" runat="server" Text='<%# Bind("Pages") %>' />
                <br />
                Price:
                <asp:Label ID="PriceLabel" runat="server" Text='<%# Bind("Price") %>' />
                <br />
                Number:
                <asp:Label ID="NumberLabel" runat="server" Text='<%# Bind("Number") %>' />
                <br />
                AvailableNumber:
                <asp:Label ID="AvailableNumberLabel" runat="server" Text='<%# Bind("AvailableNumber") %>' />
                <br />
                <asp:LinkButton ID="EditButton" runat="server" CausesValidation="False" CommandName="Edit" Text="编辑" />
                &nbsp;<asp:LinkButton ID="DeleteButton" runat="server" CausesValidation="False" CommandName="Delete" Text="删除" />
                &nbsp;<asp:LinkButton ID="NewButton" runat="server" CausesValidation="False" CommandName="New" Text="新建" />
            </ItemTemplate>
            <PagerStyle BackColor="PaleGoldenrod" ForeColor="DarkSlateBlue" HorizontalAlign="Center" />
        </asp:FormView>
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" DeleteCommand="DELETE FROM [Book] WHERE [CallNo] = @CallNo" InsertCommand="INSERT INTO [Book] ([CallNo], [Title], [Author], [Publisher], [ISBN], [PubDate], [Pages], [Price], [Number], [AvailableNumber]) VALUES (@CallNo, @Title, @Author, @Publisher, @ISBN, @PubDate, @Pages, @Price, @Number, @AvailableNumber)" SelectCommand="SELECT * FROM [Book]" UpdateCommand="UPDATE [Book] SET [Title] = @Title, [Author] = @Author, [Publisher] = @Publisher, [ISBN] = @ISBN, [PubDate] = @PubDate, [Pages] = @Pages, [Price] = @Price, [Number] = @Number, [AvailableNumber] = @AvailableNumber WHERE [CallNo] = @CallNo">
            <SelectParameters>
                <asp:ControlParameter ControlID="TextBox1" ConvertEmptyStringToNull="False" Name="BookInput" PropertyName="Text" Type="String" />
            </SelectParameters>
            <DeleteParameters>
                <asp:Parameter Name="CallNo" Type="String" />
            </DeleteParameters>
            <InsertParameters>
                <asp:Parameter Name="CallNo" Type="String" />
                <asp:Parameter Name="Title" Type="String" />
                <asp:Parameter Name="Author" Type="String" />
                <asp:Parameter Name="Publisher" Type="String" />
                <asp:Parameter Name="ISBN" Type="String" />
                <asp:Parameter Name="PubDate" Type="Int16" />
                <asp:Parameter Name="Pages" Type="Int32" />
                <asp:Parameter Name="Price" Type="Decimal" />
                <asp:Parameter Name="Number" Type="Int32" />
                <asp:Parameter Name="AvailableNumber" Type="Int32" />
            </InsertParameters>
            <UpdateParameters>
                <asp:Parameter Name="Title" Type="String" />
                <asp:Parameter Name="Author" Type="String" />
                <asp:Parameter Name="Publisher" Type="String" />
                <asp:Parameter Name="ISBN" Type="String" />
                <asp:Parameter Name="PubDate" Type="Int16" />
                <asp:Parameter Name="Pages" Type="Int32" />
                <asp:Parameter Name="Price" Type="Decimal" />
                <asp:Parameter Name="Number" Type="Int32" />
                <asp:Parameter Name="AvailableNumber" Type="Int32" />
                <asp:Parameter Name="CallNo" Type="String" />
            </UpdateParameters>
        </asp:SqlDataSource>
    
        <br />
        ==================================================<br />
        <br />
        读者查询<br />
    
        <br />
    
        输入内容：<asp:TextBox ID="TextBox2" runat="server"></asp:TextBox>
        <asp:DropDownList ID="DropDownList2" runat="server" Height="17px" Width="130px">
            <asp:ListItem>PatronID</asp:ListItem>
            <asp:ListItem>Name</asp:ListItem>
            <asp:ListItem>Gender</asp:ListItem>
            <asp:ListItem>BirthDate</asp:ListItem>
            <asp:ListItem>Type</asp:ListItem>
            <asp:ListItem>Department</asp:ListItem>
        </asp:DropDownList>
        <asp:Button ID="Button2" runat="server" OnClick="Button2_Click" Text="查询" />
        <br />
        <br />
        <asp:FormView ID="FormView2" runat="server" AllowPaging="True" DataKeyNames="PatronID" DataSourceID="SqlDataSource2" BackColor="LightGoldenrodYellow" BorderColor="Tan" BorderWidth="1px" CellPadding="2" ForeColor="Black" Width="400px">
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
            <EditRowStyle BackColor="DarkSlateBlue" ForeColor="GhostWhite" />
            <FooterStyle BackColor="Tan" />
            <HeaderStyle BackColor="Tan" Font-Bold="True" />
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
            <PagerStyle BackColor="PaleGoldenrod" ForeColor="DarkSlateBlue" HorizontalAlign="Center" />
        </asp:FormView>
        <asp:SqlDataSource ID="SqlDataSource2" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" DeleteCommand="DELETE FROM [Patron] WHERE [PatronID] = @PatronID" InsertCommand="INSERT INTO [Patron] ([PatronID], [Name], [Gender], [BirthDate], [Type], [Department]) VALUES (@PatronID, @Name, @Gender, @BirthDate, @Type, @Department)" SelectCommand="SELECT * FROM [Patron]" UpdateCommand="UPDATE [Patron] SET [Name] = @Name, [Gender] = @Gender, [BirthDate] = @BirthDate, [Type] = @Type, [Department] = @Department WHERE [PatronID] = @PatronID">
            <SelectParameters>
                <asp:ControlParameter ControlID="TextBox2" ConvertEmptyStringToNull="False" Name="PersonInput" PropertyName="Text" Type="String" />
            </SelectParameters>
            <DeleteParameters>
                <asp:Parameter Name="PatronID" Type="String" />
            </DeleteParameters>
            <InsertParameters>
                <asp:Parameter Name="PatronID" Type="String" />
                <asp:Parameter Name="Name" Type="String" />
                <asp:Parameter Name="Gender" Type="String" />
                <asp:Parameter Name="BirthDate" DbType="Date" />
                <asp:Parameter Name="Type" Type="String" />
                <asp:Parameter Name="Department" Type="String" />
            </InsertParameters>
            <UpdateParameters>
                <asp:Parameter Name="Name" Type="String" />
                <asp:Parameter Name="Gender" Type="String" />
                <asp:Parameter Name="BirthDate" DbType="Date" />
                <asp:Parameter Name="Type" Type="String" />
                <asp:Parameter Name="Department" Type="String" />
                <asp:Parameter Name="PatronID" Type="String" />
            </UpdateParameters>
        </asp:SqlDataSource>
    
        <br />
        ==================================================<br />
    
        <br />
        图书借阅与归还<br />
        <br />
        CallNo:&nbsp;&nbsp;
        <asp:TextBox ID="TextBox3" runat="server" Width="120px"></asp:TextBox>
        <br />
        <br />
        PatronID:&nbsp;
        <asp:TextBox ID="TextBox4" runat="server" Width="120px"></asp:TextBox>
        <br />
        <br />
        <asp:DropDownList ID="DropDownList3" runat="server" Width="60px">
            <asp:ListItem>借阅</asp:ListItem>
            <asp:ListItem>归还</asp:ListItem>
        </asp:DropDownList>
        <asp:Button ID="Button3" runat="server" OnClick="Button3_Click" Text="确定" />
        <br />
        <br />
        =============================================================<br />
        <br />
        历史记录 
        <asp:Button ID="Button4" runat="server" OnClick="Button4_Click" Text="刷新" />
        <br />
        <br />
        <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" DataKeyNames="CallNo,PatronID,LendTime" DataSourceID="SqlDataSource3">
            <Columns>
                <asp:BoundField DataField="CallNo" HeaderText="CallNo" ReadOnly="True" SortExpression="CallNo" />
                <asp:BoundField DataField="PatronID" HeaderText="PatronID" ReadOnly="True" SortExpression="PatronID" />
                <asp:BoundField DataField="LendTime" HeaderText="LendTime" ReadOnly="True" SortExpression="LendTime" />
                <asp:BoundField DataField="ReturnTime" HeaderText="ReturnTime" SortExpression="ReturnTime" />
            </Columns>
        </asp:GridView>
        <asp:SqlDataSource ID="SqlDataSource3" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" SelectCommand="SELECT * FROM [Lend]" UpdateCommand="SELECT * FROM [Lend]"></asp:SqlDataSource>
    
    </div>
    </form>
</body>
</html>
