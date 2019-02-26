#include "delimiters.hpp"
#include "keywords.hpp"
#include "operators.hpp"
#include "separators.hpp"
#include "identifiers.hpp"

#include <fstream>
#include <string>
#include <iostream>

std::string identify(std::string token)
{
    if (isKeyword(token))
    {
        return "KEYWORD  ";
    }
    else if (token.length() == 1)
    {
        if (isOperator(token[0]))
        {
            return "OPERATOR";
        }
        else if (isSeparator(token[0]))
        {
            return "SEPARATOR";
        }
        else
        {
            std::string type = typeOfIdentifier(token);
            if (type != "")
            {
                return type;
            }
        }
    }
    else
    {
        std::string type = typeOfIdentifier(token);
        if (type != "")
        {
            return type;
        }
    }

    return "UNKNOWN/INVALID";
}

void analyze(const char *file)
{
    std::ifstream fin(file);

    std::cout << "TOKENS\t\t\tLexemes\r\n\r\n";

    char ch;

    std::string current_token = "";

    while (fin.get(ch))
    {
        if (isDelimiter(ch))
        {
            if (current_token != "")
            {
                std::cout << identify(current_token) << "\t=\t" << current_token << "\r\n";
            }

            if (isSeparator(ch))
            {
                current_token = ch;
                std::cout << identify(current_token) << "\t=\t" << ch << "\r\n";
            }

            current_token = "";
        }
        else
        {
            current_token += ch;
        }
    }

    fin.close();

    std::cout << std::endl;
}