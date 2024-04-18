#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>


const double m=70;
const double g=9.81;
const double b=0.49;  //constantes del problema
const double v_lim=sqrt((m*g)/(b)); // velocidad limite 
const double N=100000; // numero de pasos para metodos numericos 

double velocidad(double t) {
    double vf;
    if(t <= 35){

         vf=(-v_lim) * (-v_lim * pow(M_E, (g / v_lim) * t) + v_lim * pow(M_E, -(g / v_lim * t))) /
           ((-v_lim * pow(M_E, (g / v_lim) * t) - v_lim * pow(M_E, -(g / v_lim * t))));
    }
    else
        vf=-v_lim;
    
    return vf;
};

// Método trapecioí
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

       dataFile3 << xi << " " << h*suma << std::endl;
          
    }
    
    dataFile3.close();

    return h * suma;
    
}

double caida(double v){
    return (b/m)*v*v-g;
}

//euler normal 
std::ofstream dataFile2("euler.dat");
double euler(double t_f, double N){
    double v_0=0;
    double t=0;
    double h=t_f/N;
    double v;
    

    while(t <= t_f){

        v=v_0+h*caida(v_0);

        v_0=v;

        t=t+h;

        dataFile2 << t << " " << v << std::endl;
    }
    
    dataFile2.close();

 return 0;
}
//euler vitaminas
std::ofstream dataFile4("euler_m.dat");
double euler_mejorado(double t_f, double N){
    double v_0=0;
    double t=0;
    double h=t_f/N;
    double v;
    double v_asterisco;
    double v_next;
    while (t<=t_f)
    {
    
        v_asterisco=v_0+h*caida(v_0);
        v_next=v_0+0.5*h*(caida(v_0)+caida(v_asterisco)); // definicion de variables
        v_0=v_next;
        t+=h;
        dataFile4 <<t<<" "<<v_next<<std::endl;
    }
    
return 0;
dataFile4.close();
}
// Función para mostrar el menú
void mostrar_menu() {
    std::cout << "\n--- Menú ---" << std::endl;
    std::cout << "1. Método analitico" << std::endl;
    std::cout << "2. Método de Euler normal" << std::endl;
    std::cout << "3. Método de Euler mejorado" << std::endl;
    std::cout << "4. Método del trapecio" << std::endl;
    std::cout << "5. Salir" << std::endl;
    std::cout << "Seleccione una opción: ";
}


int main(){
    
    double a=0;
    double t_f;

    
    //std::cout<<"Ingrese el tiempo de caida de su caso"<<std::endl;
    //std::cin>> t_f;


    //double integral=trapezoidal(a, t_f, N);
    //euler(t_f, N);
    //euler_mejorado(t_f,N);
    //std::cout<<"Estimacion de la integral: " << integral <<std::endl;


    std::ofstream dataFile("analitico.dat");
    for(double i=0.01 ; i <= t_f; i+=0.01){

        double v=velocidad(i);
        dataFile << i << " " << v << std::endl;

    }
    dataFile.close();


double opcion;
    while (true) {
        mostrar_menu(); // Mostrar el menú

        int opcion;
        std::cin >> opcion; // Leer la opción del usuario

        // Evaluar la opción elegida
        switch (opcion) {
             case 1: {
                // Llamar a la función para resolucion analitica
                    std::cout<<"Ingrese el tiempo de caida de su caso"<<std::endl;
                    std::cin>> t_f;
                    std::ofstream dataFile("analitico.dat");
                    for(double i=0.01 ; i <= t_f; i+=0.01){

                    double v=velocidad(i);
                    dataFile << i << " " << v << std::endl;

                        
                    }
                    dataFile.close();

                   std::ofstream scriptgp2("analitico.gp");  

                        scriptgp2 <<"set term png \n";
                        scriptgp2 <<"set output 'analitico.png' \n";
                        scriptgp2 <<"set xrange [0:40] \n";
                        scriptgp2 <<"set yrange [0:-40] \n";
                        scriptgp2 <<"set xlabel 'Tiempo(s)'\n";
                        scriptgp2 <<"set ylabel 'Velocidad(m/s)'\n";
                        scriptgp2 <<"plot 'analitico.dat' u 1:2 w l title 'Funcion analitica'";

                    scriptgp2.close();
                    system("gnuplot analitico.gp");
                break;
            }
            case 2: {
                // Llamar a la función de Euler normal
                double t_f;
                std::cout << "Introduce el tiempo final (t_f): ";
                std::cin >> t_f;
                //std::cout << "Introduce el número de pasos (N): ";
                //std::cin >> N;
                euler(t_f, N);

                        std::ofstream scriptgp3("euler.gp");  

                        scriptgp3 <<"set term png \n";
                        scriptgp3 <<"set output 'euler.png' \n";
                        scriptgp3 <<"set xrange [0:40] \n";
                        scriptgp3 <<"set yrange [0:-40] \n";
                        scriptgp3 <<"set xlabel 'Tiempo(s)'\n";
                        scriptgp3 <<"set ylabel 'Velocidad(m/s)'\n";
                        scriptgp3 <<"plot 'euler.dat' u 1:2 w l title 'Solucion por Metodo de Euler'";

                    scriptgp3.close();
                    system("gnuplot euler.gp");
                break;
            }
            case 3: {
                // Llamar a la función de Euler mejorado
                double t_f;
                std::cout << "Introduce el tiempo final (t_f): ";
                std::cin >> t_f;
                //std::cout << "Introduce el número de pasos (N): ";
                //std::cin >> N;
                euler_mejorado(t_f, N);

                        std::ofstream gp5("euler_mejorado.gp");  

                            gp5 <<"set term png \n";
                            gp5 <<"set output 'euler_mejorado.png' \n";
                            gp5 <<"set xrange [0:40] \n";
                            gp5 <<"set yrange [0:-40] \n";
                            gp5 <<"set xlabel 'Tiempo(s)'\n";
                            gp5 <<"set ylabel 'Velocidad(m/s)'\n";
                            gp5 <<"plot 'euler_m.dat' u 1:2 w l title 'Solucion por Metodo de Euler mejorado'";
                        gp5.close();
                        system("gnuplot euler_mejorado.gp");
                break;
            }
            case 4: {
                // Llamar a la función del método del trapecio
                double  b;
                a=0;
                std::cout << "Introduce el tiempo final (b): ";
                std::cin >> b;
                //std::cout << "Introduce el número de pasos (N): ";
                //std::cin >> N;
                trapezoidal(a, b, N);

                    std::ofstream scriptgp("trapo.gp");  

                        scriptgp <<"set term png \n";
                        scriptgp <<"set output 'posicionvstiempo.png' \n";
                        scriptgp <<"set xlabel 'Tiempo(s)'\n";
                        scriptgp <<"set ylabel 'Posición(m)'\n";
                        scriptgp <<"plot 'trap.dat' u 1:2 w l title 'Integral por el "
                                "metodo trapezoidal'";

                    scriptgp.close();

                    system("gnuplot trapo.gp");
                break;
            }
            case 5:
                // Salir del programacod
                std::cout << "Saliendo del programa..." << std::endl;
                return 0;
            case 6:
                // Salir del programa
                std::cout << "Saliendo del programa..." << std::endl;
                return 0;
            default:
                // Opción no válida
                std::cout << "Opción no válida. Por favor, intente nuevamente." << std::endl;
                break;
        }
    }





        std::ofstream scriptgp4("comparativa.gp");  

        scriptgp4 <<"set term png \n";
        scriptgp4 <<"set output 'comparativa.png' \n";
        scriptgp4 <<"set xrange [0:40] \n";
        scriptgp4 <<"set yrange [0:-40] \n";
        scriptgp4 <<"set xlabel 'Tiempo(s)'\n";
        scriptgp4 <<"set ylabel 'Velocidad(m/s)'\n";
        scriptgp4 <<"plot 'analitico.dat' u 1:2 w l title 'Funcion analitica', 'euler.dat' u 1:2 w l title 'Solucion por Metodo de Euler'";

    scriptgp4.close();



    
    
    system("gnuplot comparativa.gp");
    




    return 0;
}