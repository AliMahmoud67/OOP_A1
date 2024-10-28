#ifndef TASK4
#define TASK4

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

class ALU {
public:
    int hexToDec(const string& hexStr);

    string decToHex(int decimal);

    bool isValid(const string& hexStr);
};


class Memory{
    private:
    string mem[256];
    public:
    string getCell(int address);
    void setCell(int address, string value);
};

class Register{
    private:
    int Reg[16];
    public:
    int getCell(int address);
    void setCell(int address, int value);

};


class CU{
    public:
    void load(int iR, int iM, Register&reg, Memory&mem);
    void load(int iR,int value ,Register&reg);
    
};

#endif