#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <random>
#include <functional>
#include <utility>
#include <ctime>
#include <chrono>
#include <cstdlib>
using namespace std;


bool dentroTablero(int x, int y, int filas, int columnas){
    return x>=0 && y>=0 && x<filas && y<columnas;       
}

// Generador de laberinto DFS
void crearTablero(vector<vector<char>>& laberinto, int filas, int columnas){

    //creamos matriz lleno de #
    for(int i=0; i<filas;i++){
        for(int j=0; j<columnas; j++){
            laberinto[i][j]='#';
        }
    }

    //semilla aleatoria
    // usa el algoritmo Mersenne Twister donde semilla es ruido del hardware
    random_device semilla;
    mt19937 generador(semilla());

    //Dfs
    function<void(int,int)> DFS = [&](int x, int y){ 
        // marcar camino inicial fuera del if
        laberinto[x][y]='*';
        // direcciones arriba, abajo, izquierda, derecha
        //salto de a 2
        vector<pair<int,int>> direcciones = {{-2,0},{2,0},{0,-2},{0,2}};

        //orden random
        shuffle(direcciones.begin(),direcciones.end(),generador);
        

        //recorrer direcciones
        for(pair<int,int>& direccion : direcciones){
            //nuevas coordenadas (nx,ny)
            int nx = x + direccion.first;
            int ny = y + direccion.second;

            //validacion
            if(dentroTablero(nx,ny,filas,columnas) && laberinto[nx][ny]=='#'){
                //marcamos camino (nx,ny)
                laberinto[nx][ny]='*';
                //rompemos pared de en medio
                laberinto[x+direccion.first/2][y+direccion.second/2]='*';

                //llamar a funcion (recursión)
                DFS(nx,ny);
            }

        }
    };

    //Llamamos a DFS con inicio (0,0)
    DFS(0,0);

    //marcamos entrada y salida
    //esquina sup izq
    laberinto[0][0]='E';

    //esquina inf der
    laberinto[filas-1][columnas-1]='S';

}

void reconstruirCamino(vector<vector<char>>& laberinto, vector<vector<pair<int,int>>>& padre){
    int filas=laberinto.size();
    int columnas=laberinto[0].size();

    
    pair<int,int> actual={filas-1,columnas-1};
    
    //variable auxiliar inicio
    pair<int,int> inicio = {0, 0};
    while (!(actual==inicio)){
        int x=actual.first;
        int y=actual.second;

        if (laberinto[x][y]!='E' && laberinto[x][y]!='S'){
            laberinto[x][y]='.';
        }
        actual=padre[x][y];
    }
}

bool resolverBFS(vector<vector<char>>& laberinto, int entrada_x, int entrada_y, int salida_x, int salida_y){
    int filas=laberinto.size();
    int columnas=laberinto[0].size();

    //forma abreviada de llenar de False la matriz
    //matriz visitado
    vector<vector<bool>> visitado(filas,vector<bool>(columnas,false));

    //matriz padre
    vector<vector<pair<int,int>>> padre(filas, vector<pair<int,int>>(columnas,{-1,-1}));

    // vector cola
    queue<pair<int,int>> cola;

    //insertamos entrada
    cola.push({entrada_x,entrada_y});

    //entrada visitada true
    visitado[entrada_x][entrada_y]=true;

    //direcciones
    vector<pair<int,int>> direcciones ={{-1,0},{1,0},{0,-1},{0,1}};

    while (!cola.empty()){
        
        //guardamos el primer elemnto de la cola en actual
        pair<int,int> actual=cola.front();
        //eliminamos dicho elemento
        cola.pop();
        
        //guardamos las coordenasactuales en x, y
        int x =actual.first;
        int y = actual.second;

        if (x==salida_x && y==salida_y){
            reconstruirCamino(laberinto, padre);
            return true;
        }
        
        for( pair<int,int>& direccion : direcciones){
            //nueva coordenada
            int nx = x + direccion.first;
            int ny = y + direccion.second;
            
            if(dentroTablero(nx,ny,filas,columnas) && laberinto[nx][ny]!='#' && visitado[nx][ny]==false){
                //encolar nueva coordenda
                cola.push({nx,ny});
                //visitado true
                visitado[nx][ny]=true;
                //guardamos coordenada padre
                padre[nx][ny]={x,y};

            }
        }
         
    }
    cout << "No hay solución";
    return false;
}

void imprimirTablero(vector<vector<char>>& laberinto, int filas, int columnas){
    for(int i=0; i<filas; i++){
        for(int j=0; j<columnas; j++){
            cout << laberinto[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char* argv[]){
    int filas= 11;
    int columnas= 11;
    int filas_ingresadas,columnas_ingresadas;

    //parametros externos
    if (argc==3){
        filas_ingresadas=atoi(argv[1]);
        columnas_ingresadas=atoi(argv[2]);
        if(filas_ingresadas%2==1 && columnas_ingresadas%2==1){
            filas=filas_ingresadas;
            columnas=columnas_ingresadas;
        }else{
            cout << "Las dimesiones deben ser números impares";
            return 1;
        }
        
    }else if(argc!=1){
        cout << "Uso: ./laberinto filas columnas\n";
        return 1;
    }

    vector<vector<char>> laberinto(filas, vector<char>(columnas));
    auto inicio_total = chrono::high_resolution_clock::now();

    auto inicio_generacion = chrono::high_resolution_clock::now();
    crearTablero(laberinto, filas,columnas);
    imprimirTablero(laberinto,filas,columnas);
    auto fin_generacion = chrono::high_resolution_clock::now();

    auto inicio_resolucion = chrono::high_resolution_clock::now();
    resolverBFS(laberinto,0,0,filas-1,columnas-1);
    cout << "\nLaberinto resuelto\n";
    imprimirTablero(laberinto,filas,columnas);
    auto fin_resolucion = chrono::high_resolution_clock::now();

    auto fin_total = chrono::high_resolution_clock::now();


    //calculos
    chrono::duration<double> tiempo_total = fin_total - inicio_total;
    chrono::duration<double> tiempo_generacion = fin_generacion - inicio_generacion;
    chrono::duration<double> tiempo_resolucion= fin_resolucion - inicio_resolucion;
    
    //mostrar tiempos
    cout << "\n--- TIEMPOS ---\n";
    cout << "\n Generación (DFS): " << tiempo_generacion.count() <<"s";
    cout << "\n Resolución (BFS): " << tiempo_resolucion.count() << "s";
    cout << "\n Total de ejecución: " << tiempo_total.count() << "s";

    return 0;

}

