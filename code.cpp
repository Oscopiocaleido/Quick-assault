#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

struct data_file{
    double E = 0; //energia
    int NI = 0, NO = 0; //inicio y objetivo
    int CV = 0, CA = 0; //vertices y aristas

};

struct vertices{
    int ID = 0;
    double X = 0.0, Y = 0.0, Z = 0.0;
};

struct aristas{
    int ID_1 = 0, ID_2 = 0;
    double U = 0.0;
};

void arch(string file, data_file &data){
    ifstream arch;
    arch.open(file.c_str());
    if(!arch.is_open()) return;

    arch >> data.E;
    arch >> data.NI;
    arch >> data.NO;
    arch >> data.CV;
    arch >> data.CA;

}

void ensamblar(int N, data_file &data){
    string file = "data";
    file = file + to_string(N);
    file = file + ".in";

    arch(file, data);
}

int main(){
    int N = 0; //N de archivo
    data_file data;

    cin >> N;

    ensamblar(N, data);
    return 0;
}
