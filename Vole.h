#ifndef VOLE_H
#define VOLE_H
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <bitset> 
#include<cmath>
#include<fstream>
using namespace std;

class ALU {
public:
    int hexToDec(const string& hexStr);
    string decToHex(int decimal);
    int binaryToDecimal(const string& binary);
    int binaryToDecimal4bit (const string& binary);
    string decimalToBinary(int n);
    string binarytohex(string result);
    string Twoscomplement(const string& hexStr1, const string& hexStr2);
    string addBinary(const string& a, const string& b);
    bool isValid(const string& hexStr);
    double hexToDouble(const string& hexStr);
    string moveDotRight(string& str);
    string moveDotLeft(string& str);
    string addZeroToMant(string& str);
    double binaryWithDot_to_Decimal(const string& str);
    string doubleToHex(double d);
    string add2_IEEE_Float(string hex1, string hex2);

};

//////////////////////////////////////////////////////////////////////////////////
class Register{
private:
    string Reg[16] = {"00","00","00","00","00","00","00","00","00","00","00","00","00","00","00","00"};
public:
    string getCell(int address);
    void setCell(int address, string value);

};
//////////////////////////////////////////////////////////////////////////////////
class Memory{
    private:
    string mem[256];
    public:
    string getCell(int address);
    void setCell(int address, string value);
};
//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
class Instructions{
    protected:
    Memory memInstructions;
    Register regInstructions;
    public:
    // Register reg;    
    void ReadFile();
    
}; 
/////////////////////////////////////////////////////////////////////////////////////
class CU: public Instructions, public ALU{
    public:
    void load(string iR, string iM, Register&reg, Memory&mem);
    void load(string iR,string value ,Register&reg);
    void store(string iR, string iM , Register&reg, Memory&mem,string& screen);
    void move(string iR1, string iR2, Register&reg);
    void jump(string iR, string iM, Register& reg, Memory& mem, int& programCounter);
    void halt();
};

//////////////////////////////////////////////////////////////////////////////////
class Machine: public Register, public CU{
    public:
    int ProgramCounter = 10;
    void displayMemory();
    void displayRegister();
    void runInstruction(bool checkstep);

};
//////////////////////////////////////////////////////////////////////////////////

#endif