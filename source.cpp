#include "task4.h"

class ALU {
public:
    int hexToDec(const string& hexStr) {
        int decimal;
        stringstream ss;
        ss << hex << hexStr;
        ss >> decimal;
        return decimal;
    }

    string decToHex(int decimal) {
        stringstream ss;
        ss << hex << uppercase << decimal;
        return ss.str();
    }

    bool isValid(const string& hexStr) {
        if (hexStr.empty()) return false;
        for (char c : hexStr) {
            if (!isxdigit(c)) return false;
        }
        return true;
    }
};


class Memory{
    private:
    string mem[256];
    public:
    string getCell(int address){
        return mem[address];
    }
    void setCell(int address, string value){
        mem[address] = value;
    }
};

class Register{
    private:
    int Reg[16];
    public:
    int getCell(int address){
        return Reg[address];
    }
    void setCell(int address, int value){
        Reg[address] = value;
    }

};


class CU{
    public:
    void load(int iR, int iM, Register&reg, Memory&mem, ALU al){
        int temp = al.hexToDec((mem.getCell(iM))); 
        reg.setCell(iR, temp);
    }
        void load(int iR,int value ,Register&reg){

        }

    

};