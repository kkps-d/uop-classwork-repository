<%@ Page Language="C#" %>

<!DOCTYPE html>
<script runat="server">
    
    protected void Page_Load(object sender, EventArgs e)
    {

    }

    protected void Button1_Click(object sender, EventArgs e)
    {

    }
</script>

<html lang="en" xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
<meta charset="utf-8" />
    <title></title>    
</head>
<body>
    <form id="form1" runat="server">
        <p>
            PIZZA
        </p>
        <p style="height: 282px; width: 394px">
            <img src="https://www.cicis.com/wp-content/uploads/2019/04/pizza_categoryheader.png" style="-webkit-user-select: none; margin: auto; cursor: zoom-in; height: 279px; width: 356px;" /></p>
        <p style="height: 26px; width: 394px">
            Select the size of the pizza</p>
        <asp:RadioButtonList ID="RadioButtonList1" runat="server">
            <asp:ListItem Value="7.5">Personal - $7.50</asp:ListItem>
            <asp:ListItem Value="12">Medium - $12.00</asp:ListItem>
            <asp:ListItem Value="15">Large - $15.00</asp:ListItem>
            <asp:ListItem Value="18">Jumbo - $18.00</asp:ListItem>
        </asp:RadioButtonList>
        <p>
            Select toppings</p>
        <asp:CheckBoxList ID="CheckBoxList1" runat="server">
            <asp:ListItem Value="1.0">Pepperoni</asp:ListItem>
            <asp:ListItem Value="1.0">Mushroom</asp:ListItem>
            <asp:ListItem Value="1.0">Onions</asp:ListItem>
            <asp:ListItem Value="1.0">Sausage</asp:ListItem>
            <asp:ListItem Value="1.0">Bacon</asp:ListItem>
            <asp:ListItem Value="1.0">Cheese</asp:ListItem>
            <asp:ListItem Value="1.0">Olive</asp:ListItem>
        </asp:CheckBoxList>
        <asp:Button ID="Button1" runat="server" OnClick="Button1_Click" Text="Button" />
    </form>
</body>
</html>
