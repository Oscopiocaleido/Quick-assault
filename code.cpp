#include <cmath>
#include <iostream>
#include <fstream>
#include <math.h>
#include <string>

using namespace std;

class vertices{
    int ID = 0;
    double X = 0.0, Y = 0.0, Z = 0.0;
    public:
    vertices(){}
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

        NI -= 1;
        NO -= 1;

        listaVertices = new vertices[CV];
        matrizAdyacencia = new double*[CV];

        for(int i = 0; i < CV; i++){
            matrizAdyacencia[i] = new double[CV];
            for(int j = 0; j < CV; j++){
                matrizAdyacencia[i][j] = -1.0;
            }
        }

        int idTemp = 0;
        double xTemp = 0.0, yTemp = 0.0, zTemp = 0.0;

        for(int i = 0; i < CV; i++){
            arch >> idTemp;
            arch >> xTemp;
            arch >> yTemp;
            arch >> zTemp;

            listaVertices[i] = vertices(idTemp, xTemp, yTemp, zTemp);
        }

        int ID1 = 0, ID2 = 0;
        double U = 0.0;

        for(int i = 0; i < CA; i++){
            arch >> ID1; // nodo 1
            arch >> ID2; // nodo 2 ambos conectados
            arch >> U; // rozamiento


            matrizAdyacencia[ID1 - 1][ID2 - 1] = U;
        }
    }
    double calcularEnergia(int idOrigen, int idDestino, double energiaActual){
        int m = 10; //masa
        double g = 9.81; //gravedad

        if(matrizAdyacencia[idOrigen][idDestino] == -1) return -999999;

        double friccion = 0.0;
        friccion = matrizAdyacencia[idOrigen][idDestino];

        double distanciaEspacial = 0.0;

        distanciaEspacial = pow((listaVertices[idOrigen].getX() - listaVertices[idDestino].getX()), 2) + pow((listaVertices[idOrigen].getY() - listaVertices[idDestino].getY()), 2) + pow((listaVertices[idOrigen].getZ() - listaVertices[idDestino].getZ()), 2);
        distanciaEspacial = sqrt(distanciaEspacial);

        double energiaGravitacional = 0.0;
        energiaGravitacional = m * g * (listaVertices[idOrigen].getZ() - listaVertices[idDestino].getZ());

        double trabajoFriccion = 0.0;
        trabajoFriccion = friccion * m * g * distanciaEspacial;

        return (energiaActual + energiaGravitacional - trabajoFriccion);
    }
};

int main(){
    int N = 0; //N de archivo

    cin >> N;

    grafo Grafo(N);

    return 0;
}
