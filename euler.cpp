#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>

double v_lim = 0.49;
double g = 9.81;

double velocidad(double t) {
    return (-v_lim) * (-v_lim * pow(M_E, (g / v_lim) * t) + v_lim * pow(M_E, -(g / v_lim * t))) /
           ((-v_lim * pow(M_E, (g / v_lim) * t) - v_lim * pow(M_E, -(g / v_lim * t))));
}

// Método trapecio
std::ofstream dataFile3("trap.dat");
double trapezoidal(double a, double b, int N) {
    double h = (b - a) / N;
    double suma = 0.0;
    for (int i = 1; i < N; ++i) {
        double xi = a + i * h;
        if (i > 0 && i < N - 1) {
            suma += 2 * velocidad(xi);
        } else {
            suma += velocidad(xi);
        }
        dataFile3 << xi << " " << h * suma << std::endl;
    }
    dataFile3.close();
    return h * suma;
}

// Método de Euler para calcular velocidad y posición
std::ofstream eulerFile("euler.dat");
void euler(double t_final, double h) {
    double t = 0.0;
    double v = 0.0;
    double x = 0.0;
    while (t <= t_final) {
        eulerFile << t << " " << v << " " << x << std::endl;
        v += g * h;
        x += v * h;
        t += h;
    }
    eulerFile.close();
}

int main() {
    double N = 1000;
    double a = 0;
    double b;

    std::cout << "Ingrese el tiempo de caída de su caso" << std::endl;
    std::cin >> b;

    double trapdick = trapezoidal(a, b, N);
    std::cout << "Estimacion de la integral: " << trapdick << std::endl;

    std::ofstream dataFile("analitico.dat");
    for (double i = 0.01; i <= b; i += 0.01) {
        double v = velocidad(i);
        dataFile << i << " " << v << std::endl;
    }
    dataFile.close();

    euler(b, 0.01); // Llama al método de Euler

    // Generación de scripts de gnuplot
    std::ofstream script("graficas.gp");
    script << "set term png \n";
    script << "set output 'graficas.png' \n";
    script << "plot 'trap.dat' u 1:2 w l title 'Integral por el método trapezoidal', "
           << "'analitico.dat' u 1:2 w l title 'Funcion analitica', "
           << "'euler.dat' u 1:2 w l title 'Velocidad por Euler', "
           << "'euler.dat' u 1:3 w l title 'Posición por Euler'";
    script.close();

    system("gnuplot graficas.gp");

    return 0;
}
