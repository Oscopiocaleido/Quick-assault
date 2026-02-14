#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

class vertices{
    int ID = 0;
    double X = 0.0, Y = 0.0, Z = 0.0;
    public:
    vertices(int id, double x, double y, double z){
        this -> ID = id;
        this -> X = x;
        this -> Y = y;
        this -> Z = z;
    }
    int getID(){
        return ID;
    }
    double getX(){
        return X;
    }
    double getY(){
        return Y;
    }
    double getZ(){
        return Z;
    }
};

class grafo{
    int CV = 0, CA = 0; // cantidad de vertices y aristas
    double E = 0; // energia inicial
    int NI = 0, NO = 0; // nodo de inicio y nodo objetivo

    vertices* listaVertices = nullptr;
    double** matrizAdyacencia = nullptr;

    public:
    grafo(int n){
        string file = "data";
        file = file + to_string(n);
        file = file + ".in";

        ifstream arch;
        arch.open(file, ios::in); // los videos de Francisco AYP habla sobre el uso de ios::in
        if(!arch.is_open()) return;

        arch >> E;
        arch >> NI;
        arch >> NO;
        arch >> CV;
        arch >> CA;

        listaVertices = new vertices[CV];
        matrizAdyacencia = new double*[CV];

        for(int i = 0; i < CV; i++){
            matrizAdyacencia[i] = new double[CV];

        }
    }
};

int main(){
    int N = 0; //N de archivo
    int m = 10; //masa
    double g = 9.81; //gravedad

    cin >> N;

    grafo Grafo(N);

    return 0;
}
