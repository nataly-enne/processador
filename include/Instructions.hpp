#ifndef _INSTRUCTIONS_
#define _INSTRUCTIONS_

#include <string>
#include "Tokenizer.hpp"

/**
 * Classe que representa o esqueleto de uma instrução
*/
class Instructions
{
  private:
    std::string name;
    std::string dest;
    std::string op1;
    std::string op2;

  public:
    /**
     * Através de uma linhha de instrução um objeto é construido com os campos nome, destino,, operando 1 e operando 2
     * @param String linha de instrução
    */
    Instructions(std::string instruction) : name(""), dest(""), op1(""), op2("") {
        Tokenizer tokenizer(instruction);
        std::vector<std::string> token = tokenizer.getToken();

        if (token[0] == "lw" or token[0] == "ld")
        {
            if (token.size() != 3)
            {
                std::cout << "Formato não suportado: " << token[0] << std::endl;
            }
            else
            {
                name = token[0];
                dest = token[1];
                op1 = token[2];
                op2 = "";
            }
        }
        else if (token[0] == "sw" or token[0] == "st")
        {
            if (token.size() < 3)
            {
                std::cout << "Formato inválido: " << token[0] << std::endl;
            }
            else
            {
                name = token[0];
                dest = token[2];
                op1 = token[1];
                op2 = "";
            }
        }
        else if (token[0] == "add" or token[0] == "sub")
        {
            if (token.size() < 4)
            {
                std::cout << "Formato inválido: " << token[0] << std::endl;
            }
            else
            {
                name = token[0];
                dest = token[1];
                op1 = token[2];
                op2 = token[3];
            }
        }
        else if (token[0] == "j" or token[0] == "jz" or token[0] == "jn")
        {
            if (token.size() < 2)
            {
                std::cout << "Formato inválido: " << token.size() << std::endl;
            }
            else
            {
                name = token[0];
                op1 = "";
                op2 = "";
                dest = token[1];
            }
        }
       
        else if (token[0] == "and" or token[0] == "or" or token[0] == "xor")
        {
            if (token.size() < 4)
            {
                std::cout << "Formato inválido: " << token[0] << std::endl;
            }
            else
            {
                name = token[0];
                dest = token[1];
                op1 = token[2];
                op2 = token[3];
            }
        }
        else if (token[0] == "cmp")
        {
            name = token[0];
            op1 = token[2];
            op2 = token[3];
        }

        else if (token[0] == "not")
        {
            name = token[0];
            op1 = token[1];
            op2 = "";
            dest = token[2];
        }
    }

    std::string getName(){
        return name;
    }

    std::string getDest(){
        return dest;
    }

    std::string getOp1(){
        return op1;
    }

    std::string getOp2(){
        return op2;
    }
};

#endif