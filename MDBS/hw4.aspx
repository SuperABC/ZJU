<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="hw4.aspx.cs" Inherits="Book.hw4" %>

<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta http-equiv="Content-Type" content="text/html; charset=utf-8"/>
    <title></title>
</head>
<body>
    <form id="form1" runat="server">
    <div>
    
        输入内容：<asp:TextBox ID="TextBox1" runat="server"></asp:TextBox>
        <asp:DropDownList ID="DropDownList1" runat="server">
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
        <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="查询" />
        <asp:FormView ID="FormView1" runat="server" AllowPaging="True" DataKeyNames="CallNo" DataSourceID="SqlDataSource1" OnPageIndexChanging="FormView1_PageIndexChanging">
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
        </asp:FormView>
        <asp:SqlDataSource ID="SqlDataSource1" runat="server" ConnectionString="<%$ ConnectionStrings:TSGConnectionString1 %>" DeleteCommand="DELETE FROM [Book] WHERE [CallNo] = @CallNo" InsertCommand="INSERT INTO [Book] ([CallNo], [Title], [Author], [Publisher], [ISBN], [PubDate], [Pages], [Price], [Number], [AvailableNumber]) VALUES (@CallNo, @Title, @Author, @Publisher, @ISBN, @PubDate, @Pages, @Price, @Number, @AvailableNumber)" SelectCommand="SELECT * FROM [Book]" UpdateCommand="UPDATE [Book] SET [Title] = @Title, [Author] = @Author, [Publisher] = @Publisher, [ISBN] = @ISBN, [PubDate] = @PubDate, [Pages] = @Pages, [Price] = @Price, [Number] = @Number, [AvailableNumber] = @AvailableNumber WHERE [CallNo] = @CallNo">
            <SelectParameters>
                <asp:ControlParameter ControlID="TextBox1" ConvertEmptyStringToNull="False" Name="Name" PropertyName="Text" Type="String" />
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
    
    </div>
    </form>
</body>
</html>
