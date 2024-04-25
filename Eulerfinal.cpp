#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <string>

using namespace std;

const double g = 9.81;  // Aceleración debida a la gravedad en m/s^2

double f(double t, double y, double v) {
    // Define tu ecuación diferencial aquí, por ejemplo: dv/dt = -g, dy/dt = v
    return -g;
}

void euler(double y0, double v0, double t_final, double dt) {
    // Crear vectores para almacenar los resultados del método de Euler y los valores teóricos
    vector<double> t_values_euler;
    vector<double> y_values_euler;
    vector<double> v_values_euler;
    vector<double> y_teo_euler;
    vector<double> v_teo_euler;

    // Inicializar las condiciones iniciales
    double y_euler = y0;
    double v_euler = v0;
    double t_euler = 0.0;

    ofstream myfile("euler.dat");
    myfile.precision(7);

    // Iterar en el tiempo usando el método de Euler
    while (t_euler <= t_final) {
        t_values_euler.push_back(t_euler);
        y_values_euler.push_back(y_euler);
        v_values_euler.push_back(v_euler);

        // Calcular las nuevas velocidades y posiciones con el método de Euler
        double dv_dt_euler = f(t_euler, y_euler, v_euler);
        double dy_dt_euler = v_euler;

        v_euler = v_euler + dv_dt_euler * dt;
        y_euler = y_euler + dy_dt_euler * dt;

        // Calcular los valores teóricos y almacenarlos en los vectores correspondientes
        double y_teo = y0 + v0 * t_euler - 0.5 * g * t_euler * t_euler;
        double v_teo = v0 - g * t_euler;

        y_teo_euler.push_back(y_teo);
        v_teo_euler.push_back(v_teo);

        t_euler += dt;
    }

    // Mostrar los resultados del método de Euler y los valores teóricos
    for (size_t i = 0; i < t_values_euler.size(); ++i) {
        myfile << t_values_euler[i] << "\t" << y_values_euler[i] << "\t" << v_values_euler[i] << "\t" << y_teo_euler[i] << "\t" << v_teo_euler[i] << endl;
    }
    myfile.close();
}

void eulerMejorado(double y0, double v0, double t_final, double dt) {
    // Crear vectores para almacenar los resultados del método de Euler mejorado y los valores teóricos
    vector<double> t_values_mejorado;
    vector<double> y_values_mejorado;
    vector<double> v_values_mejorado;
    vector<double> y_teo_mejorado;
    vector<double> v_teo_mejorado;

    // Inicializar las condiciones iniciales
    double y_mejorado = y0;
    double v_mejorado = v0;
    double t_mejorado = 0.0;

    ofstream myfile("eulermejorado.dat");
    myfile.precision(7);

    // Iterar en el tiempo usando el método de Euler mejorado
    while (t_mejorado <= t_final) {
        t_values_mejorado.push_back(t_mejorado);
        y_values_mejorado.push_back(y_mejorado);
        v_values_mejorado.push_back(v_mejorado);

        // Calcular las nuevas velocidades y posiciones con el método de Euler mejorado
        double dv_dt_mejorado = f(t_mejorado, y_mejorado, v_mejorado);
        double dy_dt_mejorado = v_mejorado;

        // Predicción con el método de Euler
        double v_pred = v_mejorado + dv_dt_mejorado * dt;
        double y_pred = y_mejorado + dy_dt_mejorado * dt;

        // Actualización utilizando el método de punto medio (Euler mejorado)
        t_mejorado += dt;
        v_mejorado = v_mejorado + 0.5 * (dv_dt_mejorado + f(t_mejorado, y_pred, v_pred)) * dt;
        y_mejorado = y_mejorado + 0.5 * (dy_dt_mejorado + v_pred) * dt;

        // Calcular los valores teóricos y almacenarlos en los vectores correspondientes
        double y_teo = y0 + v0 * t_mejorado - 0.5 * g * t_mejorado * t_mejorado;
        double v_teo = v0 - g * t_mejorado;

        y_teo_mejorado.push_back(y_teo);
        v_teo_mejorado.push_back(v_teo);
    }

    // Mostrar los resultados del método de Euler mejorado y los valores teóricos
    for (size_t i = 0; i < t_values_mejorado.size(); ++i) {
        myfile << t_values_mejorado[i] << "\t" << y_values_mejorado[i] << "\t" << v_values_mejorado[i] << "\t" << y_teo_mejorado[i] << "\t" << v_teo_mejorado[i] << endl;
    }
    myfile.close();
}

int main() {
    double y0;  // Altura inicial en metros
    double v0;    // Velocidad inicial en m/s
    double t_final;  // Tiempo final en segundos
    double dt;   // Tamaño del paso de tiempo

    cout << "Ingrese la altura inicial en m: ";
    cin >> y0;
    cout << "Ingrese la velocidad inicial en m/s: ";
    cin >> v0;
    cout << "Ingrese el tiempo final en s: ";
    cin >> t_final;
    cout << "Ingrese el paso en s: ";
    cin >> dt;

    euler(y0, v0, t_final, dt);
    eulerMejorado(y0, v0, t_final, dt);

    return 0;
}
