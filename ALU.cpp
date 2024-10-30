#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <bitset> 

using namespace std;

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

    string Twoscomplement(const string& hexStr1, const string& hexStr2) {
        int decimal1 = hexToDec(hexStr1);
        int decimal2 = hexToDec(hexStr2);
        string binary1 = decimalToBinary(decimal1);
        string binary2 = decimalToBinary(decimal2);
        string result = addBinary(binary1,binary2);
        return binarytohex(result);

    }

    string binarytohex(string result){
        string LHS, RHS;
        for(int i = 0; i<4; i++){
            LHS+=result[i];
        }
        for(int i = 4; i<8;i++){
            RHS+=result[i];
        }
        string LHShex = decToHex(binaryToDecimal4bit(LHS));
        string RHShex = decToHex(binaryToDecimal4bit(RHS));
        string res = LHShex + RHShex;
        return res;
    }

    string decimalToBinary(int n) {
    bitset<8> binary(n);
    return binary.to_string();
    }

    int binaryToDecimal(const string& binary) {
        if (binary[0] == '1') {
            bitset<8> bits(binary);
            int decimal = bits.to_ulong();
            return decimal - (1 << 8);
        } 
        else {
            bitset<8> bits(binary);
            return bits.to_ulong();
        }
    }

    int binaryToDecimal4bit (const string& binary) {
            bitset<4> bits(binary);
            return bits.to_ulong();
    }


    string addBinary(const string& a, const string& b) {
        string result = "";
        int s = 0;
        int i = 7;
        int j = 7;

        for (int k = 0; k < 8; ++k) {
            if (i >= 0) {
                s += a[i] - '0';
            }

            if (j >= 0) {
                s += b[j] - '0';
            }

            result = char(s % 2 + '0') + result;
            s /= 2;

            i--;
            j--;
        }

        if (s == 1) {
            result = '1' + result;
        }

        if (result.length() > 8) {
            result = result.substr(result.length() - 8);
        }
        return result;
    }
};