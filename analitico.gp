set term png 
set output 'analitico.png' 
<<<<<<< HEAD
=======
set xrange [0:40] 
set yrange [0:-40] 
set xlabel 'Tiempo(s)'
set ylabel 'Velocidad(m/s)'
>>>>>>> 8265f91 (modificacion hasta euler mejorado)
plot 'analitico.dat' u 1:2 w l title 'Funcion analitica'