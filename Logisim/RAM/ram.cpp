#include <iostream>
#include <fstream>
#include <bitset>
using namespace std;

string input;
string output;

string ram[16];

void initialize(){
    string s0 = "00000000";
    for(int i=0; i<16; i++)   // fix: 16 not 15
        ram[i] = s0;
}

int address(string line){
    char c1 = line[0];
    char c2 = line[1];
    int a = (c1 - '0') * 10;
    int b = (c2 - '0');
    return a+b;
}

string operation(string line){
    return line.substr(5,3);
}

int secondAddress(string line){
    char c1 = line[9];
    char c2 = line[10];
    int a = (c1 - '0') * 10;
    int b = (c2 - '0');
    return a+b;
}

string toBinary4(int num) {
    string result = "";
    for (int i = 3; i >= 0; i--)
        result += ((num >> i) & 1) ? '1' : '0';
    return result;
}

string toBinary8(int num) {
    string result = "";
    for (int i = 7; i >= 0; i--)
        result += ((num >> i) & 1) ? '1' : '0';
    return result;
}

string binaryToHex(string bin) {
    int value = bitset<8>(bin).to_ulong();
    const char* hexDigits = "0123456789ABCDEF";
    string result;
    result += hexDigits[value / 16];
    result += hexDigits[value % 16];
    return result;
}

void ramHex(){
    for(int i=0; i<16; i++)
        ram[i] = binaryToHex(ram[i]);
}

void fillRam(string line){
    string first = "0000";
    string second = "0000";
    int adr = address(line);
    string op = operation(line);

    if(op == "lda") { first = "0001"; second = toBinary4(secondAddress(line)); }
    else if(op == "add") { first = "0010"; second = toBinary4(secondAddress(line)); }
    else if(op == "sub") { first = "0011"; second = toBinary4(secondAddress(line)); }
    else if(op == "sta") { first = "0100"; second = toBinary4(secondAddress(line)); }
    else if(op == "ldi") { first = "0101"; second = toBinary4(secondAddress(line)); }
    else if(op == "jmp") { first = "0110"; second = toBinary4(secondAddress(line)); }
    else if(op == "jmc") { first = "0111"; second = toBinary4(secondAddress(line)); }
    else if(op == "jmz") { first = "1000"; second = toBinary4(secondAddress(line)); }
    else if(op == "out") { first = "1110"; second = "0000"; }
    else if(op == "hlt") { first = "1111"; second = "0000"; }
    else if(op == "num") { ram[adr] = toBinary8(secondAddress(line)); return; }
    else { first = "0000"; second = "0000"; } // nop/default

    ram[adr] = first + second;
}

void readFile(){
    ifstream file(input);
    if (!file) {
        cerr << "Error: Could not open input file " << input << endl;
        exit(1);
    }
    string line;
    while (getline(file, line)) {
        if(!line.empty())
            fillRam(line);
    }
    file.close();
}

string ramToStr(){
    string s = "";
    for(int i=0; i<15; i++){
        s += ram[i];
        s += " ";
    }
    s += ram[15];
    return s;
}

void writeFile(string line){
    ofstream outFile(output);
    if (!outFile) {
        cerr << "Error: Could not open output file " << output << endl;
        exit(1);
    }
    outFile << "v3.0 hex words addressed\n";
    outFile << "0: " << line;
    outFile.close();
}

int main(int argc, char* argv[]) {
    if(argc != 3){
        cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    input = argv[1];
    output = argv[2];
    
    input = "/Users/saba/Desktop/University/8-Bit-Computer/Logisim/RAM/" + input;
    output = "/Users/saba/Desktop/University/8-Bit-Computer/Logisim/RAM/" + output;
    
    initialize();
    readFile();
    ramHex();
    writeFile(ramToStr());
    
    return 0;
}

