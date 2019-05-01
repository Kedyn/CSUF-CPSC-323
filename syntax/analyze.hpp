#include <fstream>
#include <cctype>
#include <vector>
#include <string>
#include <iostream>

struct Token
{
    std::string token;
    std::string lexeme;
};

bool isDelimiter(char c)
{
    if (c == '(' || c == ')' || c == '{' || c == '}' ||
        c == '[' || c == ']' || c == ',' || c == '.' ||
        c == ':' || c == ';' || c == '!' || c == ' ' ||
        c == '\t' || c == '\r' || c == '\n')
    {
        return true;
    }
    return false;
}

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

bool isOperator(char c)
{
    if (c == '*' || c == '+' || c == '-' || c == '=' ||
        c == '/' || c == '>' || c == '<' || c == '%')
    {
        return true;
    }
    return false;
}

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


void checkCharacter(const char &ch, std::vector<Token> &tokens)
{
    if (isOperator(ch))
    {
        std::string temp = "" + ch;

        tokens.push_back({"OPERATOR", temp});
    }
    else if (isSeparator(ch))
    {
        std::string temp = "" + ch;

        tokens.push_back({"SEPARATOR", temp});
    }
}

void analyze(const char *file)
{
    int state_table[16][25] = {
        // l   d   $   .   !   O   S   D   A
        {2, 7, 6, 16, 12, 15, 16, 6, 6},      //  1
        {2, 3, 4, 5, 5, 5, 5, 5, 6},          //  2
        {2, 3, 4, 5, 5, 5, 5, 5, 6},          //  3
        {2, 3, 4, 5, 5, 5, 5, 5, 6},          //  4
        {1, 1, 1, 1, 1, 1, 1, 1, 1},          //  5 Valid identifier/keyword
        {1, 1, 1, 1, 1, 1, 1, 1, 1},          //  6 unknown
        {6, 7, 6, 9, 8, 8, 8, 8, 6},          //  7
        {1, 1, 1, 1, 1, 1, 1, 1, 1},          //  8 integer
        {6, 10, 6, 6, 6, 6, 6, 6, 6},         //  9
        {6, 10, 6, 11, 11, 11, 11, 11, 6},    // 10
        {1, 1, 1, 1, 1, 1, 1, 1, 1},          // 11 real number
        {13, 13, 13, 13, 14, 13, 13, 13, 13}, // 12
        {13, 13, 13, 13, 14, 13, 13, 13, 13}, // 13
        {1, 1, 1, 1, 1, 1, 1, 1, 1},          // 14 comment
        {1, 1, 1, 1, 1, 1, 1, 1, 1},          // 15 operator
        {1, 1, 1, 1, 1, 1, 1, 1, 1}           // 16 separator
    };

    std::ifstream fin(file);

    char ch;

    std::vector<Token> tokens;

    int current_state = 0;
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
        else if (isOperator(ch))
        {
            col = 5;
        }
        else if (isSeparator(ch))
        {
            col = 6;
        }
        else if (isDelimiter(ch))
        {
            col = 7;
        }
        else
        {
            col = 8;
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
                tokens.push_back({"KEYWORD", current_token});
            }
            else
            {
                tokens.push_back({"IDENTIFIER", current_token});
            }

            checkCharacter(ch, tokens);
            current_token = "";
            current_state = 1;
            break;
        case 6:
            // UNKOWN
            checkCharacter(ch, tokens);
            current_token = "";
            current_state = 1;
            break;
        case 7:
            current_token += ch;
            break;
        case 8:
            tokens.push_back({"INTEGER", current_token});

            checkCharacter(ch, tokens);
            current_token = "";
            current_state = 1;
            break;
        case 9:
        case 10:
            current_token += ch;
            break;
        case 11:
            tokens.push_back({"REAL", current_token});

            checkCharacter(ch, tokens);
            current_token = "";
            current_state = 1;
            break;
        case 12:
        case 13:
            current_token += ch;
            break;
        case 14:
            // COMMENT;

            current_token = "";
            current_state = 1;
            break;
        case 15:
            tokens.push_back({"OPERATOR", current_token});


            if (!isOperator(ch))
            {
                checkCharacter(ch, tokens);
            }
            current_token = "";
            current_state = 1;
            break;
        case 16:
            tokens.push_back({"SEPARATOR", current_token});

            if (!isSeparator(ch))
            {
                checkCharacter(ch, tokens);
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