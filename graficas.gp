set term png 
set output 'graficas.png' 
plot 'trap.dat' u 1:2 w l title 'Integral por el método trapezoidal', 'analitico.dat' u 1:2 w l title 'Funcion analitica', 'euler.dat' u 1:2 w l title 'Velocidad por Euler', 'euler.dat' u 1:3 w l title 'Posición por Euler'