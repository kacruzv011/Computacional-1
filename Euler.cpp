#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>

// Parámetros
const double g = 9.81; // Aceleración debido a la gravedad (m/s^2)
const double density = 1.225; // Densidad del aire (kg/m^3)
const double area = 0.6; // Área transversal del paracaidista (m^2)
const double form_factor = 1.0; // Coeficiente de forma geométrica
const double k = 0.5 * density * area * form_factor; // Coeficiente de resistencia del aire

// Ecuación diferencial: dv/dt = g - (k/m) * v
double velocity_derivative(double v) {
    return g - (k / 70.0) * v;
}

// Método de Euler para resolver la ecuación diferencial
std::vector<double> euler_method(double v0, double t0, double tf, double dt) {
    std::vector<double> velocities;
    double v = v0;
    double t = t0;
    while (t <= tf) {
        velocities.push_back(v);
        v += velocity_derivative(v) * dt;
        t += dt;
    }
    return velocities;
}

// Solución analítica de la ecuación diferencial
double analytical_solution(double t) {
    return (g * 70.0 / k) * (1 - exp(-(k / 70.0) * t));
}

int main() {
    double t0 = 0.0; // Tiempo inicial
    double tf = 10.0; // Tiempo final
    double v0 = 0.0; // Velocidad inicial

    // Paso de tiempo para el método de Euler
    double dt = 0.01;

    // Resolución numérica utilizando el método de Euler
    std::vector<double> numerical_velocities = euler_method(v0, t0, tf, dt);

    // Resolución analítica
    std::vector<double> analytical_velocities;
    for (double t = t0; t <= tf; t += dt) {
        analytical_velocities.push_back(analytical_solution(t));
    }

    // Escribir resultados en un archivo CSV
    std::ofstream file("velocities.csv");
    file << "Time,Numerical Velocity,Analytical Velocity\n";
    for (size_t i = 0; i < numerical_velocities.size(); ++i) {
        file << t0 + i * dt << "," << numerical_velocities[i] << "," << analytical_velocities[i] << "\n";
    }
    file.close();

    // Generar script de gnuplot
    std::ofstream gpScript("plot_script.gnu");
    gpScript << "set terminal pngcairo\n";
    gpScript << "set output 'plot.png'\n";
    gpScript << "plot ";
    gpScript << "'velocities.csv' u 1:2  title 'Numerical', ";
    gpScript << "'velocities.csv' u 1:3  title 'Analytical' ,";
    gpScript << "pause -1\n";
    gpScript.close();

    // Ejecutar gnuplot con el script generado
    std::system("gnuplot plot_script.gnu");

    std::cout << "Resultados guardados en el archivo velocities.csv\n";
    std::cout << "Gráfico generado como plot.png\n";

    return 0;
}
