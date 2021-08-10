#ifndef _TOKENIZER_
#define _TOKENIZER_
#include "Instructions.hpp"
#include <vector>
#include <iostream>

/**
 * Classe responsável por tokenizar um linha de instrução
*/
class Tokenizer
{

  private:
    std::string aux;
    std::vector<std::string> token;

  public:
    Tokenizer(std::string &instruction) : aux("")
    {
        for (auto i(0u); i < instruction.length(); ++i){
            if (instruction[i] == ' ' or instruction[i] == ',')
                continue;
            else
            {
                while (instruction[i] != ' ' and instruction[i] != ',' and i < instruction.length())
                {
                    aux += instruction[i++];
                }
                token.push_back(aux);
                aux = "";
            }
        }
    }

    std::vector<std::string> getToken()
    {
        return token;
    }
};
#endif