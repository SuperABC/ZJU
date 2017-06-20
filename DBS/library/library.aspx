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
        已登录：<asp:Label ID="LabelFigure" runat="server" Text="登录身份"></asp:Label>
        <asp:Button ID="Button16" runat="server" Text="退出登录" OnClick="Button16_Click" />
        <asp:Button ID="Button17" runat="server" Text="修改密码" OnClick="Button17_Click" />
        <asp:Button ID="Button18" runat="server" Text="用户管理" OnClick="Button18_Click" />
        <br />
        <br />
        
        <asp:Panel ID="HomePanel" runat="server" Visible="true">
            <asp:Button ID="Button5" runat="server" Text="馆 藏 查 询" Font-Names="微软雅黑" Font-Size="XX-Large" Height="80px" OnClick="Button5_Click" Width="240px" />
            &nbsp;<asp:Button ID="Button6" runat="server" Font-Names="微软雅黑" Font-Size="XX-Large" Height="80px" OnClick="Button6_Click" Text="读 者 查 询" Width="240px" />
            <br />
            <br />
            <asp:Button ID="Button7" runat="server" Font-Names="微软雅黑" Font-Size="XX-Large" Height="80px" OnClick="Button7_Click" Text="图 书 借 还" Width="240px" />
            &nbsp;<asp:Button ID="Button8" runat="server" Font-Names="微软雅黑" Font-Size="XX-Large" Height="80px" OnClick="Button8_Click" Text="历 史 记 录" Width="240px" />

            <br />
            <br />
            <asp:TextBox ID="TextBox8" runat="server"></asp:TextBox>
            <asp:DropDownList ID="DropDownList5" runat="server">
                <asp:ListItem>等于</asp:ListItem>
                <asp:ListItem>不等于</asp:ListItem>
                <asp:ListItem>大于</asp:ListItem>
                <asp:ListItem>小于</asp:ListItem>
            </asp:DropDownList>
            <asp:DropDownList ID="DropDownList6" runat="server">
                <asp:ListItem>索书号</asp:ListItem>
                <asp:ListItem>标题</asp:ListItem>
                <asp:ListItem>作者</asp:ListItem>
                <asp:ListItem>出版社</asp:ListItem>
                <asp:ListItem>国际书号</asp:ListItem>
                <asp:ListItem>出版日期</asp:ListItem>
                <asp:ListItem>总页数</asp:ListItem>
                <asp:ListItem>价格</asp:ListItem>
                <asp:ListItem>库存</asp:ListItem>
                <asp:ListItem>总数</asp:ListItem>
            </asp:DropDownList>
            <asp:DropDownList ID="DropDownList9" runat="server" Visible="False">
                <asp:ListItem>或者</asp:ListItem>
                <asp:ListItem>并且</asp:ListItem>
            </asp:DropDownList>
            <asp:Button ID="Button25" runat="server" OnClick="Button25_Click" Text="高级" />
            <br />
            <asp:TextBox ID="TextBox9" runat="server" Visible="False"></asp:TextBox>
            <asp:DropDownList ID="DropDownList7" runat="server" Visible="False">
                <asp:ListItem>等于</asp:ListItem>
                <asp:ListItem>不等于</asp:ListItem>
                <asp:ListItem>大于</asp:ListItem>
                <asp:ListItem>小于</asp:ListItem>
            </asp:DropDownList>
            <asp:DropDownList ID="DropDownList8" runat="server" Visible="False">
                <asp:ListItem>索书号</asp:ListItem>
                <asp:ListItem>标题</asp:ListItem>
                <asp:ListItem>作者</asp:ListItem>
                <asp:ListItem>出版社</asp:ListItem>
                <asp:ListItem>国际书号</asp:ListItem>
                <asp:ListItem>出版日期</asp:ListItem>
                <asp:ListItem>总页数</asp:ListItem>
                <asp:ListItem>价格</asp:ListItem>
                <asp:ListItem>库存</asp:ListItem>
                <asp:ListItem>总数</asp:ListItem>
            </asp:DropDownList>
            <asp:DropDownList ID="DropDownList12" runat="server" Visible="False">
                <asp:ListItem>或者</asp:ListItem>
                <asp:ListItem>并且</asp:ListItem>
            </asp:DropDownList>
            <br />
            <asp:TextBox ID="TextBox10" runat="server" Visible="False"></asp:TextBox>
            <asp:DropDownList ID="DropDownList10" runat="server" Visible="False">
                <asp:ListItem>等于</asp:ListItem>
                <asp:ListItem>不等于</asp:ListItem>
                <asp:ListItem>大于</asp:ListItem>
                <asp:ListItem>小于</asp:ListItem>
            </asp:DropDownList>
            <asp:DropDownList ID="DropDownList11" runat="server" Visible="False">
                <asp:ListItem>索书号</asp:ListItem>
                <asp:ListItem>标题</asp:ListItem>
                <asp:ListItem>作者</asp:ListItem>
                <asp:ListItem>出版社</asp:ListItem>
                <asp:ListItem>国际书号</asp:ListItem>
                <asp:ListItem>出版日期</asp:ListItem>
                <asp:ListItem>总页数</asp:ListItem>
                <asp:ListItem>价格</asp:ListItem>
                <asp:ListItem>库存</asp:ListItem>
                <asp:ListItem>总数</asp:ListItem>
            </asp:DropDownList>
            <br />
            <asp:Button ID="Button23" runat="server" OnClick="Button23_Click" Text="查询" />
            <asp:Button ID="Button24" runat="server" OnClick="Button24_Click" Text="清空" />
            <asp:Button ID="Button26" runat="server" OnClick="Button26_Click" Text="简易" Visible="False" />
            <br />
            <br />
            <asp:GridView ID="GridView4" runat="server" AllowPaging="True" AllowSorting="True" AutoGenerateColumns="False" DataKeyNames="CallNo" DataSourceID="SqlDataSource7">
                <Columns>
                    <asp:BoundField DataField="CallNo" HeaderText="CallNo" ReadOnly="True" SortExpression="CallNo" />
                    <asp:BoundField DataField="Title" HeaderText="Title" SortExpression="Title" />
                    <asp:BoundField DataField="Author" HeaderText="Author" SortExpression="Author" />
                    <asp:BoundField DataField="Publisher" HeaderText="Publisher" SortExpression="Publisher" />
                    <asp:BoundField DataField="ISBN" HeaderText="ISBN" SortExpression="ISBN" />
                    <asp:BoundField DataField="PubDate" HeaderText="PubDate" SortExpression="PubDate" />
                    <asp:BoundField DataField="Pages" HeaderText="Pages" SortExpression="Pages" />
                    <asp:BoundField DataField="Price" HeaderText="Price" SortExpression="Price" />
                    <asp:BoundField DataField="Number" HeaderText="Number" SortExpression="Number" />
                    <asp:BoundField DataField="AvailableNumber" HeaderText="AvailableNumber" SortExpression="AvailableNumber" />
                </Columns>
            </asp:GridView>
            <asp:SqlDataSource ID="SqlDataSource7" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" DeleteCommand="DELETE FROM [Book] WHERE [CallNo] = @CallNo" InsertCommand="INSERT INTO [Book] ([CallNo], [Title], [Author], [Publisher], [ISBN], [PubDate], [Pages], [Price], [Number], [AvailableNumber]) VALUES (@CallNo, @Title, @Author, @Publisher, @ISBN, @PubDate, @Pages, @Price, @Number, @AvailableNumber)" SelectCommand="SELECT * FROM [Book]" UpdateCommand="UPDATE [Book] SET [Title] = @Title, [Author] = @Author, [Publisher] = @Publisher, [ISBN] = @ISBN, [PubDate] = @PubDate, [Pages] = @Pages, [Price] = @Price, [Number] = @Number, [AvailableNumber] = @AvailableNumber WHERE [CallNo] = @CallNo">
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

        </asp:Panel>

        <asp:Panel ID="BookPanel" runat="server" Visible="false">
            
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
            <asp:Button ID="Button13" runat="server" Text="批量录入" OnClick="Button13_Click" />
            <asp:Button ID="Button9" runat="server" OnClick="Button9_Click" Text="返回" />
            <br />
            <br />
            <asp:FormView ID="FormView1" runat="server" AllowPaging="True" BackColor="LightGoldenrodYellow" BorderColor="Tan" BorderWidth="1px" CellPadding="2" DataKeyNames="CallNo" DataSourceID="SqlDataSource1" ForeColor="Black" OnPageIndexChanging="FormView1_PageIndexChanging" Width="400px">
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
        </asp:Panel>
        
        <asp:Panel ID="PatronPanel" runat="server" Visible="false">
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
            <asp:Button ID="Button10" runat="server" OnClick="Button10_Click" Text="返回" />
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
        </asp:Panel>
        
        <asp:Panel ID="OperatePanel" runat="server" Visible="false">
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
            <asp:Button ID="Button11" runat="server" OnClick="Button11_Click" Text="返回" />
            <br />
            <br />
            ==================================================<br />
        </asp:Panel>
        
        <asp:Panel ID="HistoryPanel" runat="server" Visible="false">
            <br />
            历史记录 
            <asp:Button ID="Button4" runat="server" OnClick="Button4_Click" Text="刷新" />
            <asp:Button ID="Button12" runat="server" OnClick="Button12_Click" Text="返回" />
            <br />
            <br />
            <asp:GridView ID="GridView1" runat="server" AutoGenerateColumns="False" DataKeyNames="CallNo,PatronID,LendTime" DataSourceID="SqlDataSource3" AllowPaging="True" AllowSorting="True">
                <Columns>
                    <asp:BoundField DataField="CallNo" HeaderText="CallNo" ReadOnly="True" SortExpression="CallNo" />
                    <asp:BoundField DataField="PatronID" HeaderText="PatronID" ReadOnly="True" SortExpression="PatronID" />
                    <asp:BoundField DataField="LendTime" HeaderText="LendTime" ReadOnly="True" SortExpression="LendTime" />
                    <asp:BoundField DataField="ReturnTime" HeaderText="ReturnTime" SortExpression="ReturnTime" />
                </Columns>
            </asp:GridView>
            <asp:SqlDataSource ID="SqlDataSource3" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" SelectCommand="SELECT * FROM [Lend]" UpdateCommand="SELECT * FROM [Lend]"></asp:SqlDataSource>
            <br />
            图书查询:&nbsp;
            <asp:TextBox ID="TextBox6" runat="server"></asp:TextBox>
            <asp:Button ID="Button21" runat="server" OnClick="Button21_Click" Text="查询" />
            <br />
            <asp:GridView ID="GridView2" runat="server" AllowPaging="True" AllowSorting="True" AutoGenerateColumns="False" DataSourceID="SqlDataSource5">
                <Columns>
                    <asp:BoundField DataField="TITLE" HeaderText="TITLE" SortExpression="TITLE" />
                    <asp:BoundField DataField="NUMBER" HeaderText="NUMBER" SortExpression="NUMBER" />
                    <asp:BoundField DataField="AVAILABLENUMBER" HeaderText="AVAILABLENUMBER" SortExpression="AVAILABLENUMBER" />
                    <asp:BoundField DataField="NAME" HeaderText="NAME" SortExpression="NAME" />
                    <asp:BoundField DataField="LENDTIME" HeaderText="LENDTIME" SortExpression="LENDTIME" />
                </Columns>
            </asp:GridView>
            <asp:SqlDataSource ID="SqlDataSource5" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" SelectCommand="SELECT TITLE, NUMBER, AVAILABLENUMBER, NAME, LENDTIME FROM (BOOK JOIN LEND ON BOOK.CALLNO = LEND.CALLNO) JOIN PATRON ON PATRON.PATRONID = LEND.PATRONID"></asp:SqlDataSource>
            <br />
            读者查询:&nbsp;
            <asp:TextBox ID="TextBox7" runat="server"></asp:TextBox>
            <asp:Button ID="Button22" runat="server" OnClick="Button22_Click" Text="查询" />
            <br />
            <asp:GridView ID="GridView3" runat="server" AllowPaging="True" AllowSorting="True" AutoGenerateColumns="False" datasourceid="SqlDataSource6">
                <Columns>
                    <asp:BoundField DataField="NAME" HeaderText="NAME" SortExpression="NAME" />
                    <asp:BoundField DataField="NUMBER" HeaderText="NUMBER" ReadOnly="True" SortExpression="NUMBER" />
                    <asp:BoundField DataField="TITLE" HeaderText="TITLE" SortExpression="TITLE" />
                    <asp:BoundField DataField="LENDTIME" HeaderText="LENDTIME" SortExpression="LENDTIME" />
                </Columns>
            </asp:GridView>
            <asp:SqlDataSource ID="SqlDataSource6" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" SelectCommand="SELECT DISTINCT NAME, COUNT(NAME) NUMBER, TITLE, LENDTIME FROM
(SELECT BOOK.CALLNO, TITLE, LENDTIME, RETURNTIME, PATRONID FROM BOOK INNER JOIN LEND ON BOOK.CALLNO = LEND.CALLNO)TMP
INNER JOIN PATRON ON TMP.PATRONID = PATRON.PATRONID
GROUP BY NAME, TITLE, LENDTIME"></asp:SqlDataSource>
        </asp:Panel>

        <asp:Panel ID="MultiPanel" runat="server" Visible="false">
            选择文件：<asp:TextBox ID="TextBox5" runat="server"></asp:TextBox>
            <asp:Button ID="Button14" runat="server" OnClick="Button14_Click" Text="确认" />
            <asp:Button ID="Button15" runat="server" OnClick="Button15_Click" Text="返回" />
            
        </asp:Panel>
        
        <asp:Panel ID="UserPanel" runat="server" Visible="false">
            <br />
            用户查询<br /> 
            <br />
            <asp:DropDownList ID="DropDownList4" runat="server" Height="17px" Width="130px">
                <asp:ListItem>全部用户</asp:ListItem>
                <asp:ListItem>系统管理员</asp:ListItem>
                <asp:ListItem>图书管理员</asp:ListItem>
                <asp:ListItem>读者管理员</asp:ListItem>
                <asp:ListItem>借还操作员</asp:ListItem>
            </asp:DropDownList>
            <asp:Button ID="Button19" runat="server" OnClick="Button19_Click" Text="查询" />
            <asp:Button ID="Button20" runat="server" OnClick="Button20_Click" Text="返回" />
            <br />
            <br />
            <asp:FormView ID="FormView3" runat="server" AllowPaging="True" DataKeyNames="UserID" DataSourceID="SqlDataSource4" BackColor="LightGoldenrodYellow" BorderColor="Tan" BorderWidth="1px" CellPadding="2" ForeColor="Black" Width="400px">
                <EditItemTemplate>
                    UserID:
                    <asp:Label ID="UserIDLabel1" runat="server" Text='<%# Eval("UserID") %>' />
                    <br />
                    Name:
                    <asp:TextBox ID="NameTextBox" runat="server" Text='<%# Bind("Name") %>' />
                    <br />
                    Email:
                    <asp:TextBox ID="EmailTextBox" runat="server" Text='<%# Bind("Email") %>' />
                    <br />
                    Role:
                    <asp:TextBox ID="RoleTextBox" runat="server" Text='<%# Bind("Role") %>' />
                    <br />
                    <asp:LinkButton ID="UpdateButton" runat="server" CausesValidation="True" CommandName="Update" Text="更新" />
&nbsp;<asp:LinkButton ID="UpdateCancelButton" runat="server" CausesValidation="False" CommandName="Cancel" Text="取消" />
                </EditItemTemplate>
                <EditRowStyle BackColor="DarkSlateBlue" ForeColor="GhostWhite" />
                <FooterStyle BackColor="Tan" />
                <HeaderStyle BackColor="Tan" Font-Bold="True" />
                <InsertItemTemplate>
                    UserID:
                    <asp:TextBox ID="UserIDTextBox" runat="server" Text='<%# Bind("UserID") %>' />
                    <br />
                    Name:
                    <asp:TextBox ID="NameTextBox" runat="server" Text='<%# Bind("Name") %>' />
                    <br />
                    Email:
                    <asp:TextBox ID="EmailTextBox" runat="server" Text='<%# Bind("Email") %>' />
                    <br />
                    Role:
                    <asp:TextBox ID="RoleTextBox" runat="server" Text='<%# Bind("Role") %>' />
                    <br />
                    <asp:LinkButton ID="InsertButton" runat="server" CausesValidation="True" CommandName="Insert" Text="插入" />
&nbsp;<asp:LinkButton ID="InsertCancelButton" runat="server" CausesValidation="False" CommandName="Cancel" Text="取消" />
                </InsertItemTemplate>
                <ItemTemplate>
                    UserID:
                    <asp:Label ID="UserIDLabel" runat="server" Text='<%# Eval("UserID") %>' />
                    <br />
                    Name:
                    <asp:Label ID="NameLabel" runat="server" Text='<%# Bind("Name") %>' />
                    <br />
                    Email:
                    <asp:Label ID="EmailLabel" runat="server" Text='<%# Bind("Email") %>' />
                    <br />
                    Role:
                    <asp:Label ID="RoleLabel" runat="server" Text='<%# Bind("Role") %>' />
                    <br />
                    <asp:LinkButton ID="EditButton" runat="server" CausesValidation="False" CommandName="Edit" Text="编辑" />
                    &nbsp;<asp:LinkButton ID="DeleteButton" runat="server" CausesValidation="False" CommandName="Delete" Text="删除" />
                    &nbsp;<asp:LinkButton ID="NewButton" runat="server" CausesValidation="False" CommandName="New" Text="新建" />
                </ItemTemplate>
                <PagerStyle BackColor="PaleGoldenrod" ForeColor="DarkSlateBlue" HorizontalAlign="Center" />
            </asp:FormView>
            <asp:SqlDataSource ID="SqlDataSource4" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" DeleteCommand="DELETE FROM [Users] WHERE [UserID] = @original_UserID" InsertCommand="INSERT INTO [Users] ([UserID], [Name], [Email], [Role]) VALUES (@UserID, @Name, @Email, @Role)" SelectCommand="SELECT [UserID], [Name], [Email], [Role] FROM [Users]" UpdateCommand="UPDATE [Users] SET [Name] = @Name, [Email] = @Email, [Role] = @Role WHERE [UserID] = @original_UserID" OldValuesParameterFormatString="original_{0}">
                <DeleteParameters>
                    <asp:Parameter Name="original_UserID" Type="String" />
                </DeleteParameters>
                <InsertParameters>
                    <asp:Parameter Name="UserID" Type="String" />
                    <asp:Parameter Name="Name" Type="String" />
                    <asp:Parameter Name="Email" Type="String" />
                    <asp:Parameter Name="Role" Type="String" />
                </InsertParameters>
                <UpdateParameters>
                    <asp:Parameter Name="Name" Type="String" />
                    <asp:Parameter Name="Email" Type="String" />
                    <asp:Parameter Name="Role" Type="String" />
                    <asp:Parameter Name="original_UserID" Type="String" />
                </UpdateParameters>
            </asp:SqlDataSource>
            <br />
            ==================================================</asp:Panel>
    </div>
    </form>
</body>
</html>
