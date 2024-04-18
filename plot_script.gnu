set terminal pngcairo
set output 'plot.png'
plot 'velocities.csv' u 1:2  title 'Numerical', 'velocities.csv' u 1:3  title 'Analytical' ,pause -1
