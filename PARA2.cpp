#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>

double v_lim=0.49;
double g=9.81;

double velocidad(double t){
    return (-v_lim)*(-v_lim*pow(M_E,(g/v_lim)*t)+v_lim*pow(M_E,-(g/v_lim*t)))/((-v_lim*pow(M_E,(g/v_lim)*t)-v_lim*pow(M_E,-(g/v_lim*t))));
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




int main(){
    double N=1000;
    double a=0;
    double b;

    
    std::cout<<"Ingrese el tiempo de caida de su caso"<<std::endl;
    std::cin>> b;


    double trapdick=trapezoidal(a, b, N);

    std::cout<<"Estimacion de la integral" << trapdick <<std::endl;


    std::ofstream dataFile("analitico.dat");
    for(double i=0.01 ; i <= b; i+=0.01){

        double v=velocidad(i);
        dataFile << i << " " << v << std::endl;

    }
    dataFile.close();


    std::ofstream scriptgay("trapo.gp");  

        scriptgay <<"set term png \n";
        scriptgay <<"set output 'trapo.png' \n";
        scriptgay <<"plot 'trap.dat' u 1:2 w l title 'Integral por el "
                 "metodo trapezoidal'";

    scriptgay.close();

     std::ofstream scriptgay2("analitico.gp");  

        scriptgay2 <<"set term png \n";
        scriptgay2 <<"set output 'analitico.png' \n";
        scriptgay2 <<"plot 'analitico.dat' u 1:2 w l title 'Funcion analitica'";

    scriptgay2.close();

    system("gnuplot trapo.gp");
    system("gnuplot analitico.gp");




    return 0;
}