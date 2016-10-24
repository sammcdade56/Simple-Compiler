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

class SLang{
    public:
        explicit SLang();

    private:
        std::vector<int> mLangI;//machine language instructions
        int iIndex;//instruction index
        int dIndex;//data index
        std::vector<std::string> errors;//errors
        std:vector<std::tuple<int,std::string,std::string,int>
};
#endif

