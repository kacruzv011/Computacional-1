set term png 
<<<<<<< HEAD
set output 'trapo.png' 
=======
set output 'posicionvstiempo.png' 
set xlabel 'Tiempo(s)'
set ylabel 'Posición(m)'
>>>>>>> 8265f91 (modificacion hasta euler mejorado)
plot 'trap.dat' u 1:2 w l title 'Integral por el metodo trapezoidal'