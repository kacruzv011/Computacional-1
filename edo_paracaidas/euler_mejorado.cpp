#include <iostream>
#include<cmath>


//definir ecuacion diferencial dy/dx=fxy
double f(double x,double y){
    return x*x+y;
}

//eulermejorado
double euler_mejorado(double x0, double y0,double h, double xf){
    double x=x0;
    double y=y0;
    while (x<xf)
    {
    double y_asterisco=y+h*f(x,y);
    double y_next=y+0.5*h*(f(x,y)+f(x+h,y_asterisco)); // definicion de variables
    y=y_next;
    x+=h;

    }
    return y;
}
int main(){
    // definicion de parametreos
    // condiciones iniciales
    double x0=0.0;
    double y0=1.0;  //valores iniciales

    //........
    double h=0.1;
    double xf=3.0;
    std::cout<<"ingrese un valor para x final"<<std::endl;
    std::cin>>xf;
    double yf=euler_mejorado(x0,y0,h,xf);
    std::cout<<"el valor de y en x = "<<xf<<" es :"<<yf<<std::endl;
    return 0;
}





