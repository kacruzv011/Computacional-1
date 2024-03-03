//Calculadora de operaciones con vectores
//Autores: 
//Fecha:Febrero 2024
//Programa académico de Física- Física Computacional
#include <iostream>
#include <cmath>

using namespace std;

struct Vector3D {
  double x;
  double y;
  double z;
};

void leerVector(Vector3D &vector) {
  cout << "Ingrese las componentes del vector (x, y, z): ";
  cin >> vector.x >> vector.y >> vector.z;
}

void imprimirVector(const Vector3D &vector) {
  cout << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")" << endl;
}

Vector3D sumarVectores(const Vector3D &vector1, const Vector3D &vector2) {
  Vector3D vectorSuma;
  vectorSuma.x = vector1.x + vector2.x;
  vectorSuma.y = vector1.y + vector2.y;
  vectorSuma.z = vector1.z + vector2.z;
  return vectorSuma;
}

Vector3D restarVectores(const Vector3D &vector1, const Vector3D &vector2) {
  Vector3D vectorResta;
  vectorResta.x = vector1.x - vector2.x;
  vectorResta.y = vector1.y - vector2.y;
  vectorResta.z = vector1.z - vector2.z;
  return vectorResta;
}

double productoEscalar(const Vector3D &vector1, const Vector3D &vector2) {
  return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}

double productoInterno(const Vector3D &vector1, const Vector3D &vector2) {
  return productoEscalar(vector1, vector2);
}

Vector3D productoVectorial(const Vector3D &vector1, const Vector3D &vector2) {
  Vector3D vectorProducto;
  vectorProducto.x = vector1.y * vector2.z - vector1.z * vector2.y;
  vectorProducto.y = vector1.z * vector2.x - vector1.x * vector2.z;
  vectorProducto.z = vector1.x * vector2.y - vector1.y * vector2.x;
  return vectorProducto;
}

double norma(const Vector3D &vector) {
  return sqrt(productoEscalar(vector, vector));
}

Vector3D productoExterior(const Vector3D &vector1, const Vector3D &vector2) {
  return productoVectorial(vector1, vector2);
}

double productoGeometrico(const Vector3D &vector1, const Vector3D &vector2) {
  return norma(vector1) * norma(vector2) * cos(anguloEntreVectores(vector1, vector2));
}

double anguloEntreVectores(const Vector3D &vector1, const Vector3D &vector2) {
  return acos(productoEscalar(vector1, vector2) / (norma(vector1) * norma(vector2)));
}

int main() {
  Vector3D vector1, vector2;
  char operador;

  // Lectura de los vectores
  leerVector(vector1);
  leerVector(vector2);

  // Selección de la operación
  cout << "Ingrese el operador (+, -, *, /, p, i, v, n, o, g, a): ";
  cin >> operador;

  // Realización de la operación
  double resultado;
  Vector3D vectorResultado;
  switch (operador) {
    case '+':
      vectorResultado = sumarVectores(vector1, vector2);
      break;
    case '-':
      vectorResultado = restarVectores(vector1, vector2);
      break;
    case '*':
      resultado = productoEscalar(vector1, vector2);
      break;
    case '/':
      resultado = norma(vector1) / norma(vector2);
      break;
    case 'p':
      resultado = productoInterno(vector1, vector2);
      break;
    case 'i':
      resultado = productoEscalar(vector1, vector2);
      break;
    case 'v':
      vectorResultado = productoVectorial(vector1, vector2);
      break;
    case 'n':
      resultado = norma(vector1);
      break;
    case