set term png 
set output 'comparativa.png' 
set xrange [0:40] 
set yrange [0:-40] 
set xlabel 'Tiempo(s)'
set ylabel 'Velocidad(m/s)'
plot 'analitico.dat' u 1:2 w l title 'Funcion analitica', 'euler.dat' u 1:2 w l title 'Solucion por Metodo de Euler'