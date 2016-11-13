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
        void secondRun();
        int input();
        int endIt();
        int print();
        int gotoIt(int,int);
        int ifIt();
        int next();
        int let(std::string);
        std::vector<char> infixRet(std::string);
    private:
        std::array<int,100> mLangI;//machine language instructions
        int miIndex;//machine instruction index
        int siIndex;//simple instruction index
        int dIndex;//data index
        std::vector<std::string> errors;//errors
        //std::vector<std::tuple<int,std::string,std::string,int>;
        std::vector<int> lineNums;//this is the line numbers for the simple instructions
        std::vector<std::string> instructions;//these are the simple instructions
        std::vector<std::string> deets;//these are the important bits the simple instructions are done on
        std::map<char,int> variables;//this is map of variables (x,y,l) to data index they are stored in the machine lang
        std::map<int,int> lineComp;//map of slang line numbers to mlang index
        std::map<int,int> reCheck;//slang index,mlangindex of lines that need to gone over twice
};
#endif

