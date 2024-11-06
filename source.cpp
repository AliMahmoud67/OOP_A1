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
    string LHS = doubleString.substr(0, doubleString.find('.')); //1.5
    string RHS = "0." + doubleString.substr(doubleString.find('.') + 1); //0.5

    string LHS_Bin = decimalToBinary(abs(stoi(LHS))); 
    double RHS_Double = stod(RHS);
    string RHS_Bin = doubletoBinary(RHS_Double);
    // cout << RHS_Bin << endl;
    // cout << LHS_Bin << endl;
    string binResult = LHS_Bin + '.' +RHS_Bin; // 0.01 101.1

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
        movesNeeded *= -1;
    }

    // Generating Mantisa
    string mantisa = binResult.substr(binResult.find('.') + 1);
    if (mantisa.length() > 4){
        mantisa = mantisa.substr(0, 4); //0.01010101010
    }

    // Filling the mantisa with zeros if needed
    for (int i = 0; i < 4; i++){
        if (mantisa.length() < 4){
            mantisa += '0';
        }
    }

    string expo = decimalToBinary(movesNeeded + 4); 
    // cout << sign*movesNeeded << endl;
    expo = expo.substr(expo.length() - 3);

    string IEEE_Memory = signChar + expo + mantisa;
    // cout << IEEE_Memory << endl;
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

void CU::load(string iR, string iM, Register&reg, Memory&mem){ //OP-1
    int R = hexToDec(iR);
    int M = hexToDec(iM);
    reg.setCell(R, mem.getCell(M));
    
}
void CU::load(string iR, string value ,Register&reg){ //OP-2
    int R = hexToDec(iR);
    reg.setCell(R, value);
}

void CU::store(string iR, string iM , Register&reg, Memory&mem,string& screen){ //OP-3
    int R = hexToDec(iR);
    int M = hexToDec(iM);
    if(iM == "00"){
        mem.setCell(M, reg.getCell(R));
        screen+=reg.getCell(R)+' ';
    }else{
        mem.setCell(M, reg.getCell(R));
    }
}

void CU::move(string iR1, string iR2, Register&reg){ //OP-4
    int R1 = hexToDec(iR1);
    int R2 = hexToDec(iR2);
    reg.setCell(R2, reg.getCell(R1));
}

void CU::jump(string iR, string iM, Register& reg, Memory& mem, int& programCounter) { //OP-B
    int R = hexToDec(iR);
    int M = hexToDec(iM);
    if (reg.getCell(R) == reg.getCell(0)) {
        programCounter = M;
    }
}

void CU::halt(){ // C000
    exit(0);
}

/////////////////////////////////////////////////////////////////////////////////
string Register::getCell(int address){
    return Reg[address];
}
void Register::setCell(int address, string value){
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

void Instructions::ReadFile(){
    string filename;
    ifstream instructFile;
    // validation of filename
    cout << "Enter Keywords' Filename: ";
    while (true){
        getline(cin, filename);
        instructFile.open(filename, ios::in);
        if (instructFile.is_open()){
            break;
        }else{
            cout << "Error Filename is Invalid: ";
        }
    }
    
    string line,firstnumber,secondnumber;
    int j=0;
    
    
    while(getline(instructFile, line) && j < 256){ // 0000
        firstnumber = line.substr(0,2);
        memInstructions.setCell(j, firstnumber);
        j++;
        secondnumber = line.substr(2);
        memInstructions.setCell(j, secondnumber);
        j++;
    }
    instructFile.close();
}

/////////////////////////////////////////////////////////////////////////////////
void Machine::displayMemory(){
    // Print the array in a 2D format
    for (int row = 0; row < 16; ++row) {
        for (int col = 0; col < 16; ++col) {
            // Calculate the index in the 1D array
            int adress = row * 16 + col;
            // Print the element with leading zeros
            cout << memInstructions.getCell(adress) << " "; // Print in hex format
        }
        cout << endl; // Move to the next line after each row
    }
}
void Machine::displayRegister(){
    for (int i = 0; i < 16; i++){
        cout << "Register " << decToHex(i) << ": " << regInstructions.getCell(i) << endl; 
    }
}

void Machine::runInstruction(bool checkstep){
    string screen;
    while (!((memInstructions.getCell(ProgramCounter)) == "C0"&& (memInstructions.getCell(ProgramCounter + 1)) == "00")){ // != C000
        string LHS = memInstructions.getCell(ProgramCounter);
        string RHS = memInstructions.getCell(ProgramCounter + 1);

        if(LHS[0] == '1'){
            string temp = "";
            temp += LHS[1];
            load(temp,RHS,regInstructions, memInstructions);
        }
        else if(LHS[0] == '2'){
            string temp = "";
            temp += LHS[1];
            load(temp,RHS,regInstructions);
        }
        else if(LHS[0] == '3'){
            string temp = "";
            temp += LHS[1];
            store(temp,RHS,regInstructions, memInstructions,screen);
        }
        else if(LHS[0] == '4'){
            string temp = "";
            string temp2 = "";
            temp += RHS[0];
            temp2 += RHS[1];
            move(temp,temp2,regInstructions);
        }
        else if(LHS[0] == '5'){
            string temp = "";
            string temp2 = "";
            string temp3 = "";
            temp += RHS[0];
            temp2 += RHS[1];
            string result = Twoscomplement(regInstructions.getCell(hexToDec(temp)),regInstructions.getCell(hexToDec(temp2)));
            temp3 += LHS[1];
            int R = hexToDec(temp3);
            regInstructions.setCell(R, result);
        }
        else if(LHS[0] == '6'){
            string temp = "";
            string temp2 = "";
            string temp3 = "";
            temp += RHS[0];
            temp2 += RHS[1];
            string result = add2_IEEE_Float(regInstructions.getCell(hexToDec(temp)),regInstructions.getCell(hexToDec(temp2)));
            temp3 += LHS[1];
            int R = hexToDec(temp3);
            regInstructions.setCell(R, result);
        }
        else if(LHS[0] == 'B'){
            string temp = "";
            temp += LHS[1];
            jump(temp,RHS,regInstructions, memInstructions,ProgramCounter);
            if (checkstep == 1){
                displayMemory();
                displayRegister();
                cout << "Screen: " << screen <<"\n";
            }
        }
        ProgramCounter += 2;

        if (checkstep){
            displayMemory();
            displayRegister();
            cout << "Screen: " << screen <<"\n";
        }
    }
    if(!checkstep){
    cout << "Screen: "<< screen <<"\n";
    }
}
/////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////