bool isDelimiter(char c)
{
    if (c == ',' || c == ' ' || c == '(' || c == ')' || c == ';' || c == '{' || c == '}' ||
        c == '\t' || c == '\r' || c == '\n')
    {
        return true;
    }
    return false;
}