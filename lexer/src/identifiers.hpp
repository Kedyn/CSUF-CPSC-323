#include <string>
#include <cctype>

std::string typeOfIdentifier(std::string word)
{
    enum State
    {
        start,
        identifier,
        number,
        real_one,
        real_two,
        invalid
    };

    if (word.length())
    {
        State current_state = start;

        bool looping = true;

        size_t i = 0;

        while (looping)
        {
            switch (current_state)
            {
            case start:
                if (std::isalpha(static_cast<unsigned char>(word[i])) || word[i] == '_')
                {
                    current_state = identifier;
                }
                else if (std::isdigit(static_cast<unsigned char>(word[i])))
                {
                    current_state = number;
                }
                else
                {
                    current_state = invalid;
                }
                break;
            case identifier:
                if (!std::isalpha(static_cast<unsigned char>(word[i])) && word[i] != '_' && !std::isdigit(static_cast<unsigned char>(word[i])))
                {
                    current_state = invalid;
                }
                break;
            case number:
                if (word[i] == '.')
                {
                    current_state = real_one;
                }
                break;
            case real_one:
                if (std::isdigit(static_cast<unsigned char>(word[i])))
                {
                    current_state = real_two;
                }
                break;
            case real_two:
                if (!std::isdigit(static_cast<unsigned char>(word[i])))
                {
                    current_state = invalid;
                }
                break;
            case invalid:
                break;
            }

            if (i == word.length() - 1 || current_state == invalid)
            {
                looping = false;
            }

            i++;
        }

        switch (current_state)
        {
        case identifier:
            return "IDENTIFIER";
        case number:
            return "INTIGER   ";
        case real_two:
            return "REAL      ";
        case start:
        case real_one:
        case invalid:
            return "";
            break;
        }
    }

    return "";
}