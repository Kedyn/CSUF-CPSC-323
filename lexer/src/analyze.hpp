#include "delimiters.hpp"
#include "keywords.hpp"
#include "operators.hpp"
#include "separators.hpp"
#include "identifiers.hpp"

#include <fstream>
#include <cctype>
#include <string>
#include <iostream>

void checkCharacter(const char &ch)
{
    if (isOperator(ch))
    {
        std::cout << "OPERATOR\t=\t" << ch << "\r\n";
    }
    else if (isSeparator(ch))
    {
        std::cout << "SEPARATOR\t=\t" << ch << "\r\n";
    }
}

void analyze(const char *file)
{
    uint state_table[16][25] = {
        // l   d   $   .   !   *   +   -   =   /   >   <   %   '   (   )   {   }   [   ]   ,   :   ;   D   A
        {2, 7, 6, 16, 12, 15, 15, 15, 15, 15, 15, 15, 15, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 6, 6},      //  1
        {2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6},                          //  2
        {2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6},                          //  3
        {2, 3, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 6},                          //  4
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},                          //  5 Valid identifier/keyword
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},                          //  6 unknown
        {6, 7, 6, 9, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 6},                          //  7
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},                          //  8 integer
        {6, 10, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6},                         //  9
        {6, 10, 6, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 6},    // 10
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},                          // 11 real number
        {13, 13, 13, 13, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13}, // 12
        {13, 13, 13, 13, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13}, // 13
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},                          // 14 comment
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},                          // 15 operator
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}                           // 16 separator
    };

    std::ifstream fin(file);

    std::cout << "TOKENS\t\t\tLexemes\r\n\r\n";

    char ch;

    uint current_state = 0;
    size_t row = 0;
    size_t col = 0;

    std::string current_token = "";

    bool reading = true;

    while (reading)
    {
        if (!fin.get(ch))
        {
            ch = '\r';
            reading = false;
        }

        if (std::isalpha(static_cast<unsigned char>(ch)))
        {
            col = 0;
        }
        else if (std::isdigit(static_cast<unsigned char>(ch)))
        {
            col = 1;
        }
        else if (ch == '$')
        {
            col = 2;
        }
        else if (ch == '.')
        {
            col = 3;
        }
        else if (ch == '!')
        {
            col = 4;
        }
        else if (ch == '*')
        {
            col = 5;
        }
        else if (ch == '+')
        {
            col = 6;
        }
        else if (ch == '-')
        {
            col = 7;
        }
        else if (ch == '=')
        {
            col = 8;
        }
        else if (ch == '/')
        {
            col = 9;
        }
        else if (ch == '>')
        {
            col = 10;
        }
        else if (ch == '<')
        {
            col = 11;
        }
        else if (ch == '%')
        {
            col = 12;
        }
        else if (ch == '\'')
        {
            col = 13;
        }
        else if (ch == '(')
        {
            col = 14;
        }
        else if (ch == ')')
        {
            col = 15;
        }
        else if (ch == '{')
        {
            col = 16;
        }
        else if (ch == '}')
        {
            col = 17;
        }
        else if (ch == '[')
        {
            col = 18;
        }
        else if (ch == ']')
        {
            col = 19;
        }
        else if (ch == ',')
        {
            col = 20;
        }
        else if (ch == ':')
        {
            col = 21;
        }
        else if (ch == ';')
        {
            col = 22;
        }
        else if (isDelimiter(ch))
        {
            col = 23;
        }
        else
        {
            col = 24;
        }

        current_state = state_table[row][col];

        switch (current_state)
        {
        case 2:
        case 3:
        case 4:
            current_token += ch;
            break;
        case 5:
            if (isKeyword(current_token))
            {
                std::cout << "KEYWORD  \t=\t" << current_token << "\r\n";
            }
            else
            {
                std::cout << "IDENTIFIER\t=\t" << current_token << "\r\n";
            }

            checkCharacter(ch);
            current_token = "";
            current_state = 1;
            break;
        case 6:
            //std::cout << "UNKNOWN " << current_token << "\r\n";

            checkCharacter(ch);
            current_token = "";
            current_state = 1;
            break;
        case 7:
            current_token += ch;
            break;
        case 8:
            std::cout << "INTIGER   \t=\t" << current_token << "\r\n";

            checkCharacter(ch);
            current_token = "";
            current_state = 1;
            break;
        case 9:
        case 10:
            current_token += ch;
            break;
        case 11:
            std::cout << "REAL      \t=\t" << current_token << "\r\n";

            checkCharacter(ch);
            current_token = "";
            current_state = 1;
            break;
        case 12:
        case 13:
            current_token += ch;
            break;
        case 14:
            //std::cout << "COMMENT \t=\t" << current_token << "\r\n";

            current_token = "";
            current_state = 1;
            break;
        case 15:
            std::cout << "OPERATOR\t=\t" << ch << "\r\n";

            if (!isOperator(ch))
            {
                checkCharacter(ch);
            }
            current_token = "";
            current_state = 1;
            break;
        case 16:
            std::cout << "SEPARATOR\t=\t" << ch << "\r\n";

            if (!isSeparator(ch))
            {
                checkCharacter(ch);
            }
            current_token = "";
            current_state = 1;
            break;
        default:
            current_token = "";
            current_state = 1;
            break;
        }

        row = current_state - 1;
    }

    fin.close();

    std::cout << std::endl;
}