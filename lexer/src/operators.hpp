bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '<' || c == '>' ||
        c == '=' || c == '!' || c == '&' || c == '|' || c == '~')
    {
        return true;
    }
    return false;
}