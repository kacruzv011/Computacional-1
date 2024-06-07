#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include <string>

// Constantes del sistema
const double k1 = 2.76; 
const double k2 =2.76; 
const double kc = 2.76;  

const int N = 1000000;
const double t_f = 10.0;

// Variables del tipo string (cadena de caracteres)
std::string archivo_datos_exp;  // Datos externos a graficar
std::string metodo;             // Nombre del dato a usar por el usuario

// Función analítica para la posición de la partícula 1
double x_a1(double A, double B, double t, double m, double omega) {
    return ((A+B)/2)*cos(omega*t)+((A-B)/2)*cos(sqrt(3)*omega*t);

}

// Función analítica para la velocidad de la partícula 1
double v_a1(double A, double B, double t, double m, double omega) {
    return -((A+B)/2)*omega*sin(omega*t)-((A-B)/2)*sqrt(3)*omega*sin(sqrt(3)*omega*t);
}

// Función analítica para la posición de la partícula 2
double x_a2(double A, double B, double t, double m, double omega) {
    return ((A+B)/2)*cos(omega*t)-((A-B)/2)*cos(sqrt(3)*omega*t);

}

// Función analítica para la velocidad de la partícula 2
double v_a2(double A, double B, double t, double m, double omega) {
   return -((A+B)/2)*omega*sin(omega*t)+((A-B)/2)*sqrt(3)*omega*sin(sqrt(3)*omega*t);
}



// Función para la energía total del sistema
double energia_total(double m1, double m2, double k1, double k2, double kc, 
                     double A, double B, double t, 
                     double omega1, double omega2) {
    // Posiciones y velocidades
    double x1 = x_a1(A, B, t, omega1, omega2);
    double v1 = v_a1(A, B, t, omega1, omega2);
    double x2 = x_a2(A, B, t, omega1, omega2);
    double v2 = v_a2(A, B, t, omega1, omega2);
    
    // Energía cinética
    double Ek = 0.5 * m1 * v1 * v1 + 0.5 * m2 * v2 * v2;
    
    // Energía potencial
    double Ep = 0.5 * k1 * x1 * x1 + 0.5 * k2 * x2 * x2 + 0.5 * kc * (x1 - x2) * (x1 - x2);
    double Et = Ek + Ep;
    
    // Energía total
    return Et;
}

// Ecuación diferencial de la posición de la primera masa
double dx_dt(double v) {
    return v;
}

// Ecuación diferencial de la velocidad de la primera masa
double dv_dt(double x1, double x2, double k1, double kc, double m1) {
    return -(k1 / m1) * x1 + (kc / m1) * (x2 - x1);
}

// Ecuación diferencial de la posición de la segunda masa
double dx_dt2(double v) {
    return v;
}

// Ecuación diferencial de la velocidad de la segunda masa
double dv_dt2(double x1, double x2, double k2, double kc, double m2) {
    return -(k2 / m2) * x2 + (kc / m2) * (x1 - x2);
}

void sol_analitica(double A, double B, double w1, double w2, double m1, double m2, double t_f) {
    std::ofstream dataFile_posiciona("posicion_analitica.dat"); 
    std::ofstream dataFile_velocidad("velocidad_analitica.dat");
    std::ofstream dataFile_energiaa("energia_analitica.dat");
    double t = 0.0;

    while (t <= t_f) {
        double posicion1 = x_a1(A, B, t, m1, w1);
        double posicion2 = x_a2(A, B, t, m2, w2);
        dataFile_posiciona << t << " " << posicion1 << " " << posicion2 << std::endl;

        double velocidad1 = v_a1(A, B, t, m1, w1);
        double velocidad2 = v_a2(A, B, t, m2, w2);
        dataFile_velocidad << t << " " << velocidad1 << " " << velocidad2 << std::endl;

        double energia = energia_total(m1, m2, k1, k2, kc, A, B, t, w1, w2);
        dataFile_energiaa << t << " " << energia << std::endl;

        t += 0.01; 
    }

    dataFile_posiciona.close();
    dataFile_velocidad.close();
    dataFile_energiaa.close();
}

// Número de puntos de datos experimentales
const int NUM_DATOS = 648;

// Estructura para almacenar los datos experimentales
struct DatosExperimentales {
    double tiempo;
    double posicion;
    double velocidad;
};

// Función para leer datos experimentales desde un archivo txt
//referencia constante a una cadena de caracteres
void leerDatosExperimentales(const std::string& archivo, DatosExperimentales datos[]) {
    //abrir archivo identificado como "archivo"
    std::ifstream file(archivo);
     
    std::string linea;
    // Ignorar la primera línea (cabecera)
    std::getline(file, linea);
    double t, p, v;
    char sep; //separador entre los datos de //t,p,v
    int i = 0;
    //leer los datos y se detenga cuando i<num
    while (file >> t >> sep >> p >> sep >> v && i < NUM_DATOS) {
        //almacenar datos 
        datos[i++] = {t, p, v};
    }
}

// Método de Euler para la solución del sistema
void euler(double t_f, double x1_0, double x2_0, double v1_0, double v2_0, double m1, double m2,
           const std::string& archivo_masa_A1, const std::string& archivo_masa_B2) {
    std::ofstream datafile2("euler.dat");

    double t = 0.0;
    double v1 = v1_0, v2 = v2_0;
    double x1 = x1_0, x2 = x2_0;
    double h = 0.016667;
    double A = 1.0, B = 1.0; // A y B deben inicializarse con valores apropiados
    double w1 = sqrt(k1) / m1;
    double w2 = sqrt(k2) / m2;

    // Leer datos experimentales para ambas masas
    DatosExperimentales datosExperimentalesMasaA1[NUM_DATOS];
    DatosExperimentales datosExperimentalesMasaB2[NUM_DATOS];
    leerDatosExperimentales(archivo_masa_A1, datosExperimentalesMasaA1);
    leerDatosExperimentales(archivo_masa_B2, datosExperimentalesMasaB2);

    int indexA1 = 0;
    int indexB2 = 0;

    while (t <= t_f) {
        // Cálculo de la nueva velocidad y posición usando el método de Euler para la primera masa
        double v1_new = v1 + h * dv_dt(x1, x2, k1, kc, m1);
        double x1_new = x1 + h * dx_dt(v1);

        // Cálculo de la nueva velocidad y posición usando el método de Euler para la segunda masa
        double v2_new = v2 + h * dv_dt2(x1, x2, k2, kc, m2);
        double x2_new = x2 + h * dx_dt2(v2);

        // Cálculo de la energía total de las dos masas
        double total_energy = 0.5 * m1 * v1 * v1 + 0.5 * m2 * v2 * v2 + 0.5 * k1 * x1 * x1 +
                              0.5 * k2 * x2 * x2 + 0.5 * kc * (x1 - x2) * (x1 - x2);
        // Calcular energía analítica
        double Ea = energia_total(m1, m2, k1, k2, kc, A, B, t, w1, w2);

        // Calcular errores analíticos
        double xa1 = x_a1(A, B, t, w1, w2);
        double va1 = v_a1(A, B, t, w1, w2);
        double xa2 = x_a2(A, B, t, w1, w2);
        double va2 = v_a2(A, B, t, w1, w2);

        double errorx1_analitico = std::abs(xa1 - x1);
        double errorv1_analitico = std::abs(va1 - v1);
        double errorx2_analitico = std::abs(xa2 - x2);
        double errorv2_analitico = std::abs(va2 - v2);
        double errorE = std::abs(total_energy - Ea);

        // Calcular errores experimentales
        double errorx1_exp_analitico = std::abs(datosExperimentalesMasaA1[indexA1].posicion - xa1);
        double errorv1_exp_analitico = std::abs(datosExperimentalesMasaA1[indexA1].velocidad - va1);
        double errorx2_exp_analitico = std::abs(datosExperimentalesMasaB2[indexB2].posicion - xa2);
        double errorv2_exp_analitico = std::abs(datosExperimentalesMasaB2[indexB2].velocidad - va2);
        double errorx1_exp_numerico = std::abs(datosExperimentalesMasaA1[indexA1].posicion - x1);
        double errorv1_exp_numerico = std::abs(datosExperimentalesMasaA1[indexA1].velocidad - v1);
        double errorx2_exp_numerico = std::abs(datosExperimentalesMasaB2[indexB2].posicion - x2);
        double errorv2_exp_numerico = std::abs(datosExperimentalesMasaB2[indexB2].velocidad - v2);

        // Escritura de resultados en el archivo
        datafile2 << t << " " << x1_new << " " << v1_new << " " << x2_new << " " << v2_new << " " 
                    <<total_energy << " "
                  << Ea << " " << errorE << " " << errorx1_exp_analitico << " " << errorv1_exp_analitico << " " << errorx2_exp_analitico << " " <<errorv2_exp_analitico << " "
                  << errorx1_exp_numerico << " " << errorv1_exp_numerico << " " << errorx2_exp_numerico << " " << errorv2_exp_numerico << std::endl;

        // Actualización de variables para el siguiente paso
        x1 = x1_new;
        v1 = v1_new;
        x2 = x2_new;
        v2 = v2_new;
        t = t + h;

        // Avanzar en los índices de datos experimentales
        if (indexA1 < NUM_DATOS - 1) indexA1++;
        if (indexB2 < NUM_DATOS - 1) indexB2++;
    }

    datafile2.close();
}

void euler_mejorado(double t_f, double x1_0, double x2_0, double v1_0, double v2_0, double m1, double m2,
                    const std::string& archivo_masa_A1, const std::string& archivo_masa_B2) {
    std::ofstream datafile2("euler_m.dat");

    double t = 0.0;
    double v1 = v1_0, v2 = v2_0;
    double x1 = x1_0, x2 = x2_0;
    double h = 0.016667;
    double A = 1.0, B = 1.0; // Inicialización de A y B con valores adecuados
    double w1 = sqrt(k1) / m1;
    double w2 = sqrt(k2) / m2;

    // Leer datos experimentales para ambas masas
    DatosExperimentales datosExperimentalesMasaA1[NUM_DATOS];
    DatosExperimentales datosExperimentalesMasaB2[NUM_DATOS];
    leerDatosExperimentales(archivo_masa_A1, datosExperimentalesMasaA1);
    leerDatosExperimentales(archivo_masa_B2, datosExperimentalesMasaB2);

    int indexA1 = 0;
    int indexB2 = 0;

    while (t <= t_f) {
        // Primer paso de Euler (estimaciones intermedias)
        double x1_mid = x1 + 0.5 * h * dx_dt(v1);
        double v1_mid = v1 + 0.5 * h * dv_dt(x1, x2, k1, kc, m1);
        
        double x2_mid = x2 + 0.5 * h * dx_dt2(v2);
        double v2_mid = v2 + 0.5 * h * dv_dt2(x1, x2, k2, kc, m2);

        // Segundo paso de Euler utilizando las estimaciones intermedias
        double x1_new = x1 + h * dx_dt(v1_mid);
        double v1_new = v1 + h * dv_dt(x1_mid, x2_mid, k1, kc, m1);

        double x2_new = x2 + h * dx_dt2(v2_mid);
        double v2_new = v2 + h * dv_dt2(x1_mid, x2_mid, k2, kc, m2);

        // Cálculo de la energía total de las dos masas
        double total_energy = 0.5 * m1 * v1_new * v1_new + 0.5 * m2 * v2_new * v2_new + 0.5 * k1 * x1_new * x1_new +
                              0.5 * k2 * x2_new * x2_new + 0.5 * kc * (x1_new - x2_new) * (x1_new - x2_new);

        // Calcular energía analítica
        double Ea = energia_total(m1, m2, k1, k2, kc, A, B, t, w1, w2);

        // Calcular errores analíticos
        double xa1 = x_a1(A, B, t, w1, w2);
        double va1 = v_a1(A, B, t, w1, w2);
        double xa2 = x_a2(A, B, t, w1, w2);
        double va2 = v_a2(A, B, t, w1, w2);

        double errorx1_analitico = std::abs(xa1 - x1_new);
        double errorv1_analitico = std::abs(va1 - v1_new);
        double errorx2_analitico = std::abs(xa2 - x2_new);
        double errorv2_analitico = std::abs(va2 - v2_new);
        double errorE = std::abs(total_energy - Ea);

        // Calcular errores experimentales
        double errorx1_exp_analitico = std::abs(datosExperimentalesMasaA1[indexA1].posicion - xa1);
        double errorv1_exp_analitico = std::abs(datosExperimentalesMasaA1[indexA1].velocidad - va1);
        double errorx2_exp_analitico = std::abs(datosExperimentalesMasaB2[indexB2].posicion - xa2);
        double errorv2_exp_analitico = std::abs(datosExperimentalesMasaB2[indexB2].velocidad - va2);
        double errorx1_exp_numerico = std::abs(datosExperimentalesMasaA1[indexA1].posicion - x1_new);
        double errorv1_exp_numerico = std::abs(datosExperimentalesMasaA1[indexA1].velocidad - v1_new);
        double errorx2_exp_numerico = std::abs(datosExperimentalesMasaB2[indexB2].posicion - x2_new);
        double errorv2_exp_numerico = std::abs(datosExperimentalesMasaB2[indexB2].velocidad - v2_new);

        // Escritura de resultados en el archivo
        datafile2 << t << " " << x1_new << " " << v1_new << " " << x2_new << " " << v2_new << " " 
                  << total_energy << " "
                  << Ea << " " << errorE << " " << errorx1_exp_analitico << " " << errorv1_exp_analitico << " " 
                  << errorx2_exp_analitico << " " << errorv2_exp_analitico << " "
                  << errorx1_exp_numerico << " " << errorv1_exp_numerico << " " << errorx2_exp_numerico << " " 
                  << errorv2_exp_numerico << std::endl;

        // Actualización de variables para el siguiente paso
        x1 = x1_new;
        v1 = v1_new;
        x2 = x2_new;
        v2 = v2_new;
        t = t + h;

        // Avanzar en los índices de datos experimentales
        if (indexA1 < NUM_DATOS - 1) indexA1++;
        if (indexB2 < NUM_DATOS - 1) indexB2++;
    }

    datafile2.close();
}



void runge_kutta(double t_f, double x1_0, double x2_0, double v1_0, double v2_0, double m1, double m2,
                 const std::string& archivo_masa_A1, const std::string& archivo_masa_B2) {
    std::ofstream datafile("runge_kutta.dat");

    double t = 0.0;
    double v1 = v1_0, v2 = v2_0;
    double x1 = x1_0, x2 = x2_0;
    double h = 0.016667;
    double A = 1.0, B = 1.0; // Inicialización de A y B con valores adecuados
    double w1 = sqrt(k1) / m1;
    double w2 = sqrt(k2) / m2;

    // Leer datos experimentales para ambas masas
    DatosExperimentales datosExperimentalesMasaA1[NUM_DATOS];
    DatosExperimentales datosExperimentalesMasaB2[NUM_DATOS];
    leerDatosExperimentales(archivo_masa_A1, datosExperimentalesMasaA1);
    leerDatosExperimentales(archivo_masa_B2, datosExperimentalesMasaB2);

    int indexA1 = 0;
    int indexB2 = 0;

    while (t <= t_f) {
        // Primer conjunto de k (k1)
        double k1_x1 = h * dx_dt(v1);
        double k1_v1 = h * dv_dt(x1, x2, k1, kc, m1);
        double k1_x2 = h * dx_dt2(v2);
        double k1_v2 = h * dv_dt2(x1, x2, k2, kc, m2);

        // Segundo conjunto de k (k2)
        double k2_x1 = h * dx_dt(v1 + 0.5 * k1_v1);
        double k2_v1 = h * dv_dt(x1 + 0.5 * k1_x1, x2 + 0.5 * k1_x2, k1, kc, m1);
        double k2_x2 = h * dx_dt2(v2 + 0.5 * k1_v2);
        double k2_v2 = h * dv_dt2(x1 + 0.5 * k1_x1, x2 + 0.5 * k1_x2, k2, kc, m2);

        // Tercer conjunto de k (k3)
        double k3_x1 = h * dx_dt(v1 + 0.5 * k2_v1);
        double k3_v1 = h * dv_dt(x1 + 0.5 * k2_x1, x2 + 0.5 * k2_x2, k1, kc, m1);
        double k3_x2 = h * dx_dt2(v2 + 0.5 * k2_v2);
        double k3_v2 = h * dv_dt2(x1 + 0.5 * k2_x1, x2 + 0.5 * k2_x2, k2, kc, m2);

        // Cuarto conjunto de k (k4)
        double k4_x1 = h * dx_dt(v1 + k3_v1);
        double k4_v1 = h * dv_dt(x1 + k3_x1, x2 + k3_x2, k1, kc, m1);
        double k4_x2 = h * dx_dt2(v2 + k3_v2);
        double k4_v2 = h * dv_dt2(x1 + k3_x1, x2 + k3_x2, k2, kc, m2);

        // Combinación de k para obtener la nueva posición y velocidad
        double x1_new = x1 + (k1_x1 + 2 * k2_x1 + 2 * k3_x1 + k4_x1) / 6.0;
        double v1_new = v1 + (k1_v1 + 2 * k2_v1 + 2 * k3_v1 + k4_v1) / 6.0;
        double x2_new = x2 + (k1_x2 + 2 * k2_x2 + 2 * k3_x2 + k4_x2) / 6.0;
        double v2_new = v2 + (k1_v2 + 2 * k2_v2 + 2 * k3_v2 + k4_v2) / 6.0;

        // Cálculo de la energía total de las dos masas
        double total_energy = 0.5 * m1 * v1_new * v1_new + 0.5 * m2 * v2_new * v2_new + 0.5 * k1 * x1_new * x1_new +
                              0.5 * k2 * x2_new * x2_new + 0.5 * kc * (x1_new - x2_new) * (x1_new - x2_new);

        // Calcular energía analítica
        double Ea = energia_total(m1, m2, k1, k2, kc, A, B, t, w1, w2);

        // Calcular errores analíticos
        double xa1 = x_a1(A, B, t, w1, w2);
        double va1 = v_a1(A, B, t, w1, w2);
        double xa2 = x_a2(A, B, t, w1, w2);
        double va2 = v_a2(A, B, t, w1, w2);

        double errorx1_analitico = std::abs(xa1 - x1_new);
        double errorv1_analitico = std::abs(va1 - v1_new);
        double errorx2_analitico = std::abs(xa2 - x2_new);
        double errorv2_analitico = std::abs(va2 - v2_new);
        double errorE = std::abs(total_energy - Ea);

        // Calcular errores experimentales
        double errorx1_exp_analitico = std::abs(datosExperimentalesMasaA1[indexA1].posicion - xa1);
        double errorv1_exp_analitico = std::abs(datosExperimentalesMasaA1[indexA1].velocidad - va1);
        double errorx2_exp_analitico = std::abs(datosExperimentalesMasaB2[indexB2].posicion - xa2);
        double errorv2_exp_analitico = std::abs(datosExperimentalesMasaB2[indexB2].velocidad - va2);
        double errorx1_exp_numerico = std::abs(datosExperimentalesMasaA1[indexA1].posicion - x1_new);
        double errorv1_exp_numerico = std::abs(datosExperimentalesMasaA1[indexA1].velocidad - v1_new);
        double errorx2_exp_numerico = std::abs(datosExperimentalesMasaB2[indexB2].posicion - x2_new);
        double errorv2_exp_numerico = std::abs(datosExperimentalesMasaB2[indexB2].velocidad - v2_new);

        // Escritura de resultados en el archivo
        datafile << t << " " << x1_new << " " << v1_new << " " << x2_new << " " << v2_new << " " 
                 << total_energy << " "
                 << Ea << " " << errorE << " " << errorx1_exp_analitico << " " << errorv1_exp_analitico << " " 
                 << errorx2_exp_analitico << " " << errorv2_exp_analitico << " "
                 << errorx1_exp_numerico << " " << errorv1_exp_numerico << " " << errorx2_exp_numerico << " " 
                 << errorv2_exp_numerico << std::endl;

        // Actualización de variables para el siguiente paso
        x1 = x1_new;
        v1 = v1_new;
        x2 = x2_new;
        v2 = v2_new;
        t = t + h;

        // Avanzar en los índices de datos experimentales
        if (indexA1 < NUM_DATOS - 1) indexA1++;
        if (indexB2 < NUM_DATOS - 1) indexB2++;
    }

    datafile.close();
}

// Función para que se muestre el menú y el usuario elija la masa a comparar
void menu_masas() {
    std::cout << "\n--- Bienvenido al programa que soluciona las ecuaciones relacioandas a un OAS. Seleccione la masa a trabajar. ---" << std::endl;
    std::cout << "1. Acoplado" << std::endl;
}

// Función para que se muestre el menú y el usuario elija el método a comparar
void mostrar_menu() {
    std::cout << "\n--- Menú de métodos ---" << std::endl;
    std::cout << "1. Método de Euler" << std::endl;
    std::cout << "2. Método de Euler mejorado" << std::endl;
    std::cout << "3. Método Runge-Kutta" << std::endl;
    std::cout << "Para salir presione Ctrl + z " << std::endl;
    
}

void graficar(const std::string& metodo, const std::string& archivo_masa_A1, const std::string& archivo_masa_B2) {
    // Script para la gráfica 3x2
    std::ofstream scriptgp1(metodo + "_masas.gp");
    scriptgp1 << "set term pngcairo size 1920, 1080\n";
    scriptgp1 << "set output '" << metodo << "_masas.png'\n";

    scriptgp1 << "set multiplot layout 2 , 3  title '" << metodo << " - Masas'\n";
    scriptgp1 << "set style line 1 lc rgb '#0060ad' lt 1 lw 2 pt 7 ps 1.5\n";
    scriptgp1 << "set style line 2 lc rgb '#dd181f' lt 1 lw 2 pt 5 ps 1.5\n";
    scriptgp1 << "set style line 3 lc rgb '#32cd32' lt 1 lw 2 pt 9 ps 1.5\n";
    scriptgp1 << "set style line 4 lc rgb '#ff8c00' lt 1 lw 2 pt 11 ps 1.5\n";

    // Gráficos para masa 1
    scriptgp1 << "set xlabel 'Tiempo(s)'\n";
    scriptgp1 << "set ylabel 'Posición (m)'\n";
    scriptgp1 << "plot '" << metodo << ".dat' u 1:2 w l ls 1 title 'Posición masa 1 (" << metodo << ")', \\\n";
    scriptgp1 << "'posicion_analitica.dat' u 1:2 w l ls 3 title 'Posición masa 1 (analítica)', \\\n";
    scriptgp1 << "'" << archivo_masa_A1 << "' u 1:2 w l ls 4 title 'Posición masa 1 (experimental)'\n";

    scriptgp1 << "set xlabel 'Tiempo(s)'\n";
    scriptgp1 << "set ylabel 'Velocidad (m/s)'\n";
    scriptgp1 << "plot '" << metodo << ".dat' u 1:3 w l ls 1 title 'Velocidad masa 1 (" << metodo << ")', \\\n";
    scriptgp1 << "'velocidad_analitica.dat' u 1:2 w l ls 3 title 'Velocidad masa 1 (analítica)', \\\n";
    scriptgp1 << "'" << archivo_masa_A1 << "' u 1:3 w l ls 4 title 'Velocidad masa 1 (experimental)'\n";


    scriptgp1 << "set xlabel 'Tiempo(s)'\n";
    scriptgp1 << "set ylabel 'Error'\n";
    scriptgp1 << "set yrange [0:8] \n";
    scriptgp1 << "plot '" << metodo << ".dat' u 1:9 w l ls 1 title 'Error Posición masa 1 exp-analitico', \\\n";
    scriptgp1 << "'" << metodo << ".dat' u 1:13 w l ls 2 title 'Error Posición masa 1 exp-numerico', \\\n";
    scriptgp1 << "'" << metodo << ".dat' u 1:10 w l ls 3 title 'Error Velocidad masa 1 exp-numerico', \\\n";
    scriptgp1 << "'" << metodo << ".dat' u 1:14 w l ls 4 title 'Error Velocidad masa 1 exp-analitico'\n";


    // Gráficos para masa 2
    scriptgp1 << "set xlabel 'Tiempo(s)'\n";
    scriptgp1 << "set ylabel 'Posición (m)'\n";
    scriptgp1 << "set yrange [-0.06:0.08] \n";
    scriptgp1 << "plot '" << metodo << ".dat' u 1:4 w l ls 2 title 'Posición masa 2 (" << metodo << ")', \\\n";
    scriptgp1 << "'posicion_analitica.dat' u 1:3 w l ls 3 title 'Posición masa 2 (analítica)', \\\n";
    scriptgp1 << "'" << archivo_masa_B2 << "' u 1:2 w l ls 4 title 'Posición masa 2 (experimental)'\n";

    scriptgp1 << "set xlabel 'Tiempo(s)'\n";
    scriptgp1 << "set ylabel 'Velocidad (m/s)'\n";
    scriptgp1 << "set yrange [-0.3:0.3] \n";
    scriptgp1 << "plot '" << metodo << ".dat' u 1:5 w l ls 2 title 'Velocidad masa 2 (" << metodo << ")', \\\n";
    scriptgp1 << "'velocidad_analitica.dat' u 1:3 w l ls 3 title 'Velocidad masa 2 (analítica)', \\\n";
    scriptgp1 << "'" << archivo_masa_B2 << "' u 1:3 w l ls 4 title 'Velocidad masa 2 (experimental)'\n";
    scriptgp1 << "set xlabel 'Tiempo(s)'\n";
    scriptgp1 << "set ylabel 'Error'\n";
    scriptgp1 << "set yrange [0:8] \n";
    scriptgp1 << "plot '" << metodo << ".dat' u 1:11 w l ls 1 title 'Error Posición masa 2 exp-analitico', \\\n";
    scriptgp1 << "'" << metodo << ".dat' u 1:15 w l ls 2 title 'Error Posición masa 2 exp-numerico', \\\n";
    scriptgp1 << "'" << metodo << ".dat' u 1:16 w l ls 3 title 'Error Velocidad masa 2 exp-numerico', \\\n";
    scriptgp1 << "'" << metodo << ".dat' u 1:12 w l ls 4 title 'Error Velocidad masa 2 exp-analitico'\n";

    scriptgp1 << "unset multiplot\n";

    scriptgp1.close();

    // Ejecutar gnuplot para generar la imagen de las masas
    system(("gnuplot " + metodo + "_masas.gp").c_str());

    // Script para la gráfica 1x2 (energía y error de energía)
    std::ofstream scriptgp2(metodo + "_energia.gp");
    scriptgp2 << "set term pngcairo size 1920, 1080\n";
    scriptgp2 << "set output '" << metodo << "_energia.png'\n";

    scriptgp2 << "set multiplot layout 1, 2 title '" << metodo << " - Energía'\n";

    scriptgp2 << "set xlabel 'Tiempo(s)'\n";
    scriptgp2 << "set ylabel 'Energía (J)'\n";
    scriptgp2 << "plot '" << metodo << ".dat' u 1:6 w l title 'Energía (" << metodo << ")', \\\n";
    scriptgp2 << "'energia_analitica.dat' u 1:2 w l title 'Energía (analítica)'\n";

    scriptgp2 << "set xlabel 'Tiempo(s)'\n";
    scriptgp2 << "set ylabel 'Error de Energía'\n";
    scriptgp2 << "plot '" << metodo << ".dat' u 1:8 w l title 'Error Energía'\n";

    scriptgp2 << "unset multiplot\n";

    scriptgp2.close();

    // Ejecutar gnuplot para generar la imagen de la energía
    system(("gnuplot " + metodo + "_energia.gp").c_str());
}

// Función principal
int main() {
    double m1,m2;
    double A;
    double B;

    int opc1;
    int opc2;

    std::string archivo_datos_exp_m1;
    std::string archivo_datos_exp_m2;

    menu_masas();
    std::cin >> opc1;

    switch (opc1) {
        case 1:
            m1 = 0.256;
            m2 = 0.256;
            A=0.010549524747328;
            B=0.0451894816350314;
            archivo_datos_exp_m1 = "masa_A1.txt";
            archivo_datos_exp_m2 = "masa_B2.txt";
            break;
        default:
            std::cout << "Opción incorrecta.";
            return 1;
    }

    mostrar_menu();
    std::cin >> opc2;

    double w1 = sqrt(k1 / m1);
    double w2 = sqrt(k2/m2);
    sol_analitica(A,B, w1,w2,m1,m2,t_f);

    switch (opc2) {
        case 1:
            metodo = "euler";
            euler(t_f, A, B,0,0,m1,m2,archivo_datos_exp_m1,archivo_datos_exp_m2);
            graficar(metodo,archivo_datos_exp_m1,archivo_datos_exp_m2);
            break;
        case 2:
            metodo = "euler_m";
            euler_mejorado(t_f, A, B,0,0,m1,m2,archivo_datos_exp_m1,archivo_datos_exp_m2);
            graficar(metodo,archivo_datos_exp_m1,archivo_datos_exp_m2);
            break;
        case 3:
            metodo = "runge_kutta";
            runge_kutta(t_f, A, B,0,0,m1,m2,archivo_datos_exp_m1,archivo_datos_exp_m2);
            graficar(metodo,archivo_datos_exp_m1,archivo_datos_exp_m2);
            break;
        default:
            std::cout << "Opción no válida. Por favor, intente nuevamente." << std::endl;
            break;
    }

    return 0;
}