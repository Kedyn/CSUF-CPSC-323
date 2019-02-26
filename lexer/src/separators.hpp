bool isSeparator(char c)
{
    // REMOVED ! and space because they should not be printed
    if (c == '\'' || c == '(' || c == ')' || c == '{' || c == '}' ||
        c == '[' || c == ']' || c == ',' || c == '.' ||
        c == ':' || c == ';')
    {
        return true;
    }

    return false;
}
