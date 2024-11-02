#ifndef VOLE_H
#define VOLE_H
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <bitset> 
#include<cmath>
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
    int Reg[16];
public:
    int getCell(int address);
    void setCell(int address, int value);

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
class CU{
    public:
    void load(int iR, int iM, Register&reg, Memory&mem, ALU al);
    // void load(int iR,int value ,Register&reg);

    

};
//////////////////////////////////////////////////////////////////////////////////

#endif