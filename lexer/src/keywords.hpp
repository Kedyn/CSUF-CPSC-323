#include <string>

bool isKeyword(std::string word)
{
    if (word == "int" || word == "float" || word == "bool" ||
        word == "if" || word == "else" || word == "then" ||
        word == "do" || word == "while" || word == "whileend" ||
        word == "do" || word == "doend" || word == "for" ||
        word == "and" || word == "or" || word == "function")
    {
        return true;
    }

    return false;
}