/*
Nikki Bregman
I did this
Header for the SLang class
*/

#ifndef SLang_H
#define SLang_H
#include <string>
#include <array>
#include <vector>
#include <tuple>
#include <map>

class SLang{
    public:
        explicit SLang(std::vector<std::string> commands);
        std::vector<std::string> splitIt(std::string);
        std::vector<int> returnFinal();
        int next();

    private:
        std::array<int,100> mLangI;//machine language instructions
        int miIndex;//machine instruction index
        int siIndex;//instruction index
        int dIndex;//data index
        std::vector<std::string> errors;//errors
        //std::vector<std::tuple<int,std::string,std::string,int>;
        std::vector<std::string> instructions;
        std::vector<std::string> rest;
        std::map<char,int> variables;
};
#endif
