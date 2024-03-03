//CALCULADORA DE MATRICES
//Autores: Yerly Zaudí Gómez Contreras & Julian Armando Aros
//Fecha:27 de Agosto de 2023
//Programa académico de Física- Física Computacional
//Programación orientada a objetos

#include <stdio.h>
#include <vector> 
#include <iostream>
#include <cstdlib>


class MatrixCalculator{
    private: // Atributos
    std::vector<std::vector<int>>matrixA;
    std::vector<std::vector<int>>matrixB;
    
    public: // punteros
        MatrixCalculator(){
    //MatrixCalculator (const std::vector<std::vector<int>> & matA, const std::vector<std::vector<int>> & matB){
       //matrixA=matA; 
       //matrixB=matB;
    }
    void Tamano(){
        std::cout<<"El número de filas de A es: "<<matrixA.size()<<std::endl;
        std::cout<<"El número de filas de B es: "<<matrixB.size()<<std::endl;
        std::cout<<"El número de columnas de A es: "<<matrixA[0].size()<<std::endl;
        std::cout<<"El número de columnas de B es: "<<matrixB[0].size()<<std::endl;
    }

    void IngresarMatrices() {
        int rowsA, columnsA, rowsB, columnsB;

        std::cout <<"El número de filas de la matriz A : ";
        std::cin >> rowsA;
        std::cout <<"Ingrese el número de columnas de la matriz A: ";
        std::cin >> columnsA;

        std::cout << "Ingrse el número de filas de la matriz B: ";
        std::cin >> rowsB;
        std::cout << "Ingrese el número de columnas de la matriz B: ";
        std::cin >> columnsB;

        //validar que las matrices sean compatible

        if (rowsA != rowsB || columnsA != columnsB){
            std::cout << "Las matrices deben tener las mismas dimensiones para ser sumandas y restadas: " << std::endl;
            return;
        }
    

    //Valores matriz A
    std::cout << "Ingrese los elementos de la matriz A:\n";
    matrixA.resize(rowsA, std::vector<int>(columnsA));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < columnsA; ++j) {
            std::cout << "Elemento [" << i + 1 << "][" << j + 1 << "]: ";
            std::cin >> matrixA[i][j];
        }
    }

    //Valores matriz B
    std::cout << "Ingrese los elementos de la matriz B:\n";
    matrixB.resize(rowsB, std::vector<int>(columnsB));
    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < columnsB; ++j) {
            std::cout << "Elemento [" << i + 1 << "][" << j + 1 << "]: ";
            std::cin >> matrixB[i][j];
        }
    }
}
    // Sumar matrices: filas iguales u columas 
    std::vector<std::vector<int>>addMatrices(){
        std::vector<std::vector<int>>result;  // Almacenar los resultados
        if (matrixA.size() != matrixB.size() || matrixA[0].size() != matrixB[0].size()){
        std::cout<<"Sus matrices deben tener la misma cantdad de filas y columnas para ser operadas. "<<std ::endl;
        return result;
    }
    else{
        int rows = matrixA.size();
        int column = matrixA[0].size();
        result.resize(rows, std::vector<int>(column,0));
        for (int i=0; i< rows; i++){
            for (int j=0; j<column; j++) {
                result[i][j] = matrixA[i][j] + matrixB[i][j];
                
            }
        }
    }
      return result;  
    }
    void SumarMatrices(){
        std::vector<std::vector<int>> suma = addMatrices(); 
    std::cout<<"La suma de las matrices es: "<<std::endl;
    // Imprimir el resultado de la suma
    for (size_t i = 0; i < suma.size(); ++i) {
        for (size_t j = 0; j < suma[0].size(); ++j) {
            std::cout << suma[i][j] << " ";
        }
        std::cout << std::endl;
    }
    }
    
    //Resta de matrices
     std::vector<std::vector<int>>subtMatrices(){
        std::vector<std::vector<int>>result2;  // Almacenar los resultados
        if (matrixA.size() != matrixB.size() || matrixA[0].size() != matrixB[0].size()){
        std::cout<<"Sus matrices deben tener la misma cantdad de filas y columnas para ser operadas. "<<std ::endl;
        return result2;
    }
    else{
        int rows = matrixA.size();
        int column = matrixA[0].size();
        result2.resize(rows, std::vector<int>(column,0));
        for (int i=0; i< rows; i++){
            for (int j=0; j<column; j++) {
                result2[i][j] = matrixA[i][j] - matrixB[i][j];
                
            }
        }
    }
      return result2;  
    }
    
    void RestarMatrices() {
    std::vector<std::vector<int>> resta = subtMatrices(); // Obtener la resta
    std::cout << "La resta de las matrices es: " << std::endl;
    for (size_t i = 0; i < resta.size(); ++i) {
        for (size_t j = 0; j < resta[0].size(); ++j) {
            std::cout << resta[i][j] << " ";
        }
        std::cout << std::endl;
    }
    }
    //multiplicación por escalar 
    std::vector<std::vector<int>> scalarMultiply(int scalar) {
    std::vector<std::vector<int>> result;
    int rows = matrixA.size();
    int columns = matrixA[0].size();

    result.resize(rows, std::vector<int>(columns, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            result[i][j] = matrixA[i][j] * scalar;
        }
    }

    return result;
    }
    
    void MultiplicarPorEscalar(int scalar){
    //imprimir multiplicación por escalar
    std::vector<std::vector<int>> result = scalarMultiply(scalar);

    std::cout << "Matriz A multiplicada por escalar: " << std::endl;
    for (size_t i = 0; i < result.size(); ++i) {
        for (size_t j = 0; j < result[0].size(); ++j) {
            std::cout << result[i][j] << " ";
        }
    std::cout << std::endl;
}
    }
    //multiplicación de matrices
    std::vector<std::vector<int>>mulMatrices(){
        std::vector<std::vector<int>>result;  // Almacenar los resultados
        
        if (matrixA[0].size() != matrixB.size() || matrixA.size() != matrixB[0].size()){
        std::cout<<"El número de columnas de la matriz A debe ser igual número de filas de la matriz B y viceversa, o ser cuadradas. "<<std ::endl;
        return result; 
    }
    else{
        int rows = matrixA.size();
        int column = matrixB[0].size();
        int commonDim = matrixA[0].size();
        
        result.resize(rows, std::vector<int>(column,0));
        
        for (int i=0; i< rows; i++){
            for (int j=0; j<column; j++) {
                for (int k = 0; k < commonDim; ++k) {
                    result[i][j] += matrixA[i][k] * matrixB[k][j];
                }
                
            }
        }
    }
      return result;  
    }
    
    void MultiplicarMatrices(){
             //imprimir multiplicación de matrices
    std::vector<std::vector<int>>multiplicacion = mulMatrices();
    std::cout << "El producto de las matrices es: " << std::endl;
    for (size_t i = 0; i < multiplicacion.size(); ++i) {
        for (size_t j = 0; j < multiplicacion[0].size(); ++j) {
            std::cout << multiplicacion[i][j] << " ";
        }
    std::cout << std::endl;
}

    }
};

int main(){  // Definición de los objetos
    
    //std::vector<std::vector<int>>matrixA={{1,2},{3,4}};
    //std::vector<std::vector<int>>matrixB={{5,6},{7,8}};
    //std::cout<<"Matriz A"<<std::endl;
    
    // Creando un objeto tipo MatrixCalculator
    
    //MatrixCalculator Calculator(matrixA,matrixB); // Construcción del objeto
    MatrixCalculator Calculator;

    Calculator.IngresarMatrices();
    //Calculator.Tamano();

    //menu de opciones
    int choice;

    do{
        std::cout << "\n\n\t\t\tMenú de opciones" << std::endl;
        std::cout << "\t\t\t-----------------" << std::endl;
        std::cout << "\n\t1. Ingresar matrices" << std::endl;
        std::cout << "\t2. Sumar matrices" << std::endl;
        std::cout << "\t3. Restar matrices" << std::endl;
        std::cout << "\t4. Multiplicación por escalar" << std::endl;
        std::cout << "\t5. Multiplicar matrices" << std::endl;
        std::cout << "\t6. Mostrar tamaño" << std::endl;
        std::cout << "\t7. SALIR" << std::endl;
        std::cout << "\n Seleccione una opción" << std::endl;
        std::cin >> choice; 

        switch (choice)
        {
        case 1:
            Calculator.IngresarMatrices();
            break;
        
        case 2://sumar
            Calculator.SumarMatrices();
            break;

        case 3: 
            Calculator.RestarMatrices();
            break;

        case 4:
            int scalar;
            std::cout << "Ingrese el escalar:";
            std::cin >> scalar;
            Calculator.MultiplicarPorEscalar(scalar);
            break;

        case 5:
            Calculator.MultiplicarMatrices();
            break;
        
        case 6:
            Calculator.Tamano();
            break;
        
        case 7:
            std::cout << "Saliendo del programa.\n";
            break;
            
        default:
            std::cout << "Opnción no válida. Intente de nuevo.\n";
            break;
        }
    
    } while (choice != 7);

    return 0;
}
