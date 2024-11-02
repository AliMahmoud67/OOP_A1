#include"Vole.h"



int ALU::hexToDec(const string& hexStr) {
        int decimal;
        stringstream ss;
        ss << hex << hexStr;
        ss >> decimal;
        return decimal;
    }

string ALU::decToHex(int decimal) {
        stringstream ss;
        ss << hex << uppercase << decimal;
        return ss.str();
    }

bool ALU::isValid(const string& hexStr) {
        if (hexStr.empty()) return false;
        for (char c : hexStr) {
            if (!isxdigit(c)) return false;
        }
        return true;
    }

string ALU::Twoscomplement(const string& hexStr1, const string& hexStr2) {
        int decimal1 = hexToDec(hexStr1);
        int decimal2 = hexToDec(hexStr2);
        string binary1 = decimalToBinary(decimal1);
        string binary2 = decimalToBinary(decimal2);
        string result = addBinary(binary1,binary2);
        return binarytohex(result);

    }

string ALU::binarytohex(string result){
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

string ALU::decimalToBinary(int n) {
        bitset<8> binary(n);
        return binary.to_string();
    }

int ALU::binaryToDecimal(const string& binary) {
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

int ALU::binaryToDecimal4bit (const string& binary) {
        bitset<4> bits(binary);
        return bits.to_ulong();
    }


string ALU::addBinary(const string& a, const string& b) {
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

string ALU::moveDotRight(string& str){//0.1111 
    int ind = str.find('.');
    str = str.substr(0, ind) + str.substr(ind + 1);
    str = str.substr(0, ind + 1) + '.' + str.substr(ind + 1);
    return str;
}
string ALU::moveDotLeft(string& str){ //100111
    int ind = str.find('.');
    str = str.substr(0, ind) + str.substr(ind + 1);
    str = str.substr(0, ind-1) + '.' + str.substr(ind-1);
    return str;
}

string ALU::addZeroToMant(string& str){//1111 0.01111
    string result = "0" + str;
    str = result; 
    return str;
}

double ALU::binaryWithDot_to_Decimal(const string& str){
    double result = 0;
    for (int i = 1; i < str.length() + 1; i++){
        result += (str[i-1] - '0')*(pow(2, (-1*i)));
    }
    return result;
}

double ALU::hexToDouble(const string& hexStr){ 
    string binStr = decimalToBinary(hexToDec(hexStr));

    char signChar = binStr[0];
    string expoStr = binStr.substr(1, 3);
    string mantisaStr = binStr.substr(4);

    int sign = signChar == '1' ? -1 : 1;
    int expo = binaryToDecimal4bit(expoStr);
    int E_B = expo - 4;

    string tempMant="";
    if (E_B > 0){
        tempMant = "0." + mantisaStr;
        for (int i = 1; i < E_B+1; i++){
            moveDotRight(tempMant);
        }
    }else{
        for (int i = 0; i < abs(E_B); i++){
            addZeroToMant(mantisaStr);
        }
        tempMant = "0." + mantisaStr;
    }
    // separating the bianry into 2 parts
    // cout << tempMant<< endl;
    string LHS = tempMant.substr(0, tempMant.find('.'));
    string RHS = tempMant.substr(tempMant.find('.') + 1);
    int LHS_Value = binaryToDecimal4bit(LHS);
    double RHS_Value = binaryWithDot_to_Decimal(RHS);
    // cout << RHS;

    double result = sign*(LHS_Value + RHS_Value);
    return result;
}

string doubletoBinary(double d){ //0.5
    string result = "";
    double counter = d;
    while(true){
        counter = counter * 2;
        if (counter == 0.0){
            return result;
        }else{
            if (counter >= 1){
                counter -= 1;
                result += "1";
            }else if (counter < 1){
                result += "0";
            }
        }
        
    }
}

string ALU::doubleToHex(double d){

    string doubleString = to_string(d);
    int sign = doubleString[0] == '-'? -1: 1;
    char signChar = sign == -1 ?'1' : '0';
    // separate into 2 parts
    string LHS = doubleString.substr(0, doubleString.find('.'));
    string RHS = "0." + doubleString.substr(doubleString.find('.') + 1);

    string LHS_Bin = decimalToBinary(abs(stoi(LHS)));
    double RHS_Double = stod(RHS);
    string RHS_Bin = doubletoBinary(RHS_Double);
    // cout << RHS_Bin << endl;
    // cout << LHS_Bin << endl;
    string binResult = LHS_Bin + '.' +RHS_Bin;

    // Get the most significant '1'
    int indexOfMostSigni1;
    for (int i =0 ;i < binResult.length();i++){
        if (binResult[i] == '1'){
            indexOfMostSigni1 = i;
            break;
        }
    }

    // Calculate moves of the floating point
    int te = ((binResult.find('.') - indexOfMostSigni1));
    int movesNeeded = abs(te);

    // Moving the point
    if (binResult.find('.') > indexOfMostSigni1){
        for (int i = 0; i < movesNeeded; i++){
            moveDotLeft(binResult);
        }
    }else{
        movesNeeded -= 1;
        for (int i = 0; i < movesNeeded; i++){
            moveDotRight(binResult);
        }
    }

    // Generating Mantisa
    string mantisa = binResult.substr(binResult.find('.') + 1);
    if (mantisa.length() > 4){
        mantisa = mantisa.substr(0, 4);
    }

    // Filling the mantisa with zeros if needed
    for (int i = 0; i < 4; i++){
        if (mantisa.length() < 4){
            mantisa += '0';
        }
    }

    string expo = decimalToBinary(sign*movesNeeded + 4);
    expo = expo.substr(expo.length() - 3);

    string IEEE_Memory = signChar + expo + mantisa;
    string HexaResult = binarytohex(IEEE_Memory);

    return HexaResult; 
}

string ALU::add2_IEEE_Float(string hex1, string hex2){
    double d1= hexToDouble(hex1);
    double d2= hexToDouble(hex2);

    double add = d1 + d2;

    string result = doubleToHex(add);
    return result; 

}

/////////////////////////////////////////////////////////////////////////////////

void CU::load(int iR, int iM, Register&reg, Memory&mem, ALU al){
    int temp = al.hexToDec((mem.getCell(iM))); 
    reg.setCell(iR, temp);
}
// void CU::load(int iR,int value ,Register&reg){

// }




/////////////////////////////////////////////////////////////////////////////////
int Register::getCell(int address){
    return Reg[address];
}
void Register::setCell(int address, int value){
    Reg[address] = value;
}
/////////////////////////////////////////////////////////////////////////////////
string Memory::getCell(int address){
    return mem[address];
}
void Memory::setCell(int address, string value){
    mem[address] = value;
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////