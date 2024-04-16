#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>


double m=70;
double g=9.81;
double b=0.49;
double v_lim=sqrt((m*g)/(b));

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

double EDO(double v){
    double m=70;
    double g=9.81;
    double b=0.49;
    return (b/m)*v*v-g;
}


std::ofstream dataFile2("euler.dat");
double euler(double t_f, double N){
    double v_0=0;
    double t=0;
    double h=t_f/N;
    double m=70;
    double g=9.81;
    double b=0.49;
    double v;
    

    while(t <= t_f){

        v=v_0+h*EDO(v_0);

        v_0=v;

        t=t+h;

        dataFile2 << t << " " << v << std::endl;
    }
    
    dataFile2.close();

 return 0;
}


int main(){
    double N=1000;
    double a=0;
    double t_f;

    
    std::cout<<"Ingrese el tiempo de caida de su caso"<<std::endl;
    std::cin>> t_f;


    double integral=trapezoidal(a, t_f, N);
    euler(t_f, N);

    std::cout<<"Estimacion de la integral: " << integral <<std::endl;


    std::ofstream dataFile("analitico.dat");
    for(double i=0.01 ; i <= t_f; i+=0.01){

        double v=velocidad(i);
        dataFile << i << " " << v << std::endl;

    }
    dataFile.close();


    std::ofstream scriptgp("trapo.gp");  

        scriptgp <<"set term png \n";
        scriptgp <<"set output 'posicionvstiempo.png' \n";
        scriptgp <<"set xlabel 'Tiempo(s)'\n";
        scriptgp <<"set ylabel 'Posición(m)'\n";
        scriptgp <<"plot 'trap.dat' u 1:2 w l title 'Integral por el "
                 "metodo trapezoidal'";

    scriptgp.close();

        std::ofstream scriptgp2("analitico.gp");  

        scriptgp2 <<"set term png \n";
        scriptgp2 <<"set output 'analitico.png' \n";
        scriptgp2 <<"set xrange [0:40] \n";
        scriptgp2 <<"set yrange [0:-40] \n";
        scriptgp2 <<"set xlabel 'Tiempo(s)'\n";
        scriptgp2 <<"set ylabel 'Velocidad(m/s)'\n";
        scriptgp2 <<"plot 'analitico.dat' u 1:2 w l title 'Funcion analitica'";

    scriptgp2.close();

        std::ofstream scriptgp3("euler.gp");  

        scriptgp3 <<"set term png \n";
        scriptgp3 <<"set output 'euler.png' \n";
        scriptgp3 <<"set xrange [0:40] \n";
        scriptgp3 <<"set yrange [0:-40] \n";
        scriptgp3 <<"set xlabel 'Tiempo(s)'\n";
        scriptgp3 <<"set ylabel 'Velocidad(m/s)'\n";
        scriptgp3 <<"plot 'euler.dat' u 1:2 w l title 'Solucion por Metodo de Euler'";

    scriptgp3.close();

        std::ofstream scriptgp4("comparativa.gp");  

        scriptgp4 <<"set term png \n";
        scriptgp4 <<"set output 'comparativa.png' \n";
        scriptgp4 <<"set xrange [0:40] \n";
        scriptgp4 <<"set yrange [0:-40] \n";
        scriptgp4 <<"set xlabel 'Tiempo(s)'\n";
        scriptgp4 <<"set ylabel 'Velocidad(m/s)'\n";
        scriptgp4 <<"plot 'analitico.dat' u 1:2 w l title 'Funcion analitica', 'euler.dat' u 1:2 w l title 'Solucion por Metodo de Euler'";

    scriptgp4.close();

    system("gnuplot trapo.gp");
    system("gnuplot analitico.gp");
    system("gnuplot euler.gp");
    system("gnuplot comparativa.gp");




    return 0;
}