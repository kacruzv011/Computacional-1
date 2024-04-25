set term png 
set output 'posicionvstiempo.png' 
set xlabel 'Tiempo(s)'
set ylabel 'Posición(m)'
plot 'trap.dat' u 1:2 w l title 'Integral por el metodo trapezoidal'