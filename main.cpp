#include "Vole.h"
#include "source.cpp"

string input(string ms) // function that takes input from user so that i can use it inside function's argument like this: [funcName(input("write here what will appear to the user"))]
{
    string d;
    cout << ms;
    getline(cin >> ws, d); 
    return d;
}

string isValidChoice2(string Msg){ // function to ensure user only enterd 1 or 2 or 3 or 4
    while (true)
    {
        if(Msg == "1" || Msg == "2")
            return Msg;
        else{
            cout << "Please choose a valid choice: ";
            getline(cin >> ws, Msg); // enter the message again
        }
    }
    
}


int main(){

    cout << "------Welcome to Our Vole Machine Simulator------" << endl;
    while(true){
        cout << "\nChoose What you want to do"<< endl;
        cout << "1- Load Instructions From File\n2- End\n"<< endl;
        string choice = isValidChoice2(input("Please choose a number from the menu: "));

        if(choice == "1"){ // Load File
            Machine mach;
            mach.ReadFile();
            mach.runInstruction();

        }else if(choice == "2"){
            exit(0);
        }
    }
    

    // Machine ma;
    // ma.ReadFile();
    // ma.displayMemory();
    
    

}


