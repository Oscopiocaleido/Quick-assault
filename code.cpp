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

    bool* visitados = nullptr;
    int* caminoActual = nullptr;
    int pasoActual = 0;

    double mejorEnergia = -1.0;
    int* mejorCamino = nullptr;
    int longitudMejorCamino = 0;
    int mejorCambiosAltura = 99999;

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

        if(matrizAdyacencia[idOrigen][idDestino] == -1) return -999999; // retornar un numero exagerado para marcar un error

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
    void internetExplorer(int nodoActual, double energiaActual, int cambiosAltura){
        caminoActual[pasoActual] = nodoActual;
        pasoActual++;
        visitados[nodoActual] = true;

        if(nodoActual == NO){
            bool mejorCombinacion = false;

            if(energiaActual > mejorEnergia){
                mejorCombinacion = true;
            }
            else if(abs(energiaActual - mejorEnergia) < 0.0001){
                if(pasoActual < longitudMejorCamino){
                    mejorCombinacion = true;
                }
                else if(pasoActual == longitudMejorCamino){
                    if(cambiosAltura < mejorCambiosAltura) mejorCombinacion = true;
                }
            }

            if(mejorCombinacion){
                mejorEnergia = energiaActual;
                longitudMejorCamino = pasoActual;
                mejorCambiosAltura = cambiosAltura;

                for(int i = 0; i < pasoActual; i++){
                    mejorCamino [i] = caminoActual [i];
                }
            }

            visitados[nodoActual] = false;
            pasoActual --;
            return;
        }

        for(int i = 0; i < CV; i++){
            if(matrizAdyacencia[nodoActual][i] != -1){
                if(!visitados[i]){
                    double energiaFutura = calcularEnergia(nodoActual, i, energiaActual);

                    if(energiaFutura >= 0){
                        int nuevosCambios = cambiosAltura;
                        if(listaVertices[nodoActual].getZ() != listaVertices[i].getZ()){
                            nuevosCambios++;
                        }
                        internetExplorer(i, energiaFutura, nuevosCambios);
                    }
                }
            }
        }
        visitados[nodoActual] = false;
        pasoActual --;
    }
    void buscarCaminos(int N){
        visitados = new bool [CV];
        caminoActual = new int [CV];
        mejorCamino = new int [CV];

        for(int i = 0; i < CV; i++){
            visitados[i] = false;
            caminoActual[i] = 0;
        }

        pasoActual = 0;
        mejorEnergia = -1.0;

        internetExplorer(NI, E, 0);

        if(mejorEnergia == -1.0){
            generarReporte(N);
        }else{
            generarReporte(N);
        }
    }
    void generarReporte(int n){
        string fileOut = "path" + to_string(n) + ".out";
        ofstream out(fileOut);

        if(!out.is_open()) return;
        out.setf(ios::fixed);
        out.precision(2);

        if(mejorEnergia == -1.0){
            out<< "-1\n";
        }else{
            out<< mejorEnergia << "\n";

            double energiaPaso = E;

            for(int i = 0; i < longitudMejorCamino - 1; i++){
                int origen = mejorCamino[i];
                int destino = mejorCamino[i + 1];

                double energiaSiguiente = calcularEnergia(origen, destino, energiaPaso);

                out<< origen + 1 << " " << destino + 1 << " " << energiaPaso << " " << energiaSiguiente << "\n";

                energiaPaso = energiaSiguiente;
            }
        }
        out.close();
    }
};

int main(){
    int N = 0; //N de archivo

    cin >> N;

    grafo Grafo(N);
    Grafo.buscarCaminos(N);

    return 0;
}
