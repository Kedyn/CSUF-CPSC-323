#include <string>

bool isKeyword(std::string word)
{
    // https://www.w3schools.in/cplusplus-tutorial/keywords/
    if (word == "asm" || word == "else" || word == "new" || word == "this" || word == "auto" ||
        word == "enum" || word == "operator" || word == "throw" || word == "bool" ||
        word == "explicit" || word == "private" || word == "true" || word == "break" ||
        word == "export" || word == "protected" || word == "try" || word == "case" ||
        word == "extern" || word == "public" || word == "typedef" || word == "catch" ||
        word == "false" || word == "register" || word == "typeid" || word == "char" ||
        word == "float" || word == "reinterpret_cast" || word == "typename" || word == "class" ||
        word == "for" || word == "return" || word == "union" || word == "const" ||
        word == "friend" || word == "short" || word == "unsigned" || word == "const_cast" ||
        word == "goto" || word == "signed" || word == "using" || word == "continue" ||
        word == "if" || word == "sizeof" || word == "virtual" || word == "default" ||
        word == "inline" || word == "static" || word == "void" || word == "delete" ||
        word == "int" || word == "static_cast" || word == "volatile" || word == "do" ||
        word == "long" || word == "struct" || word == "wchar_t" || word == "double" ||
        word == "mutable" || word == "switch" || word == "while" || word == "dynamic_cast" ||
        word == "namespace" || word == "template" || word == "And" || word == "bitor" ||
        word == "not_eq" || word == "xor" || word == "and_eq" || word == "compl" || word == "or" ||
        word == "xor_eq" || word == "bitand" || word == "not" || word == "or_eq")
    {
        return true;
    }

    return false;
}