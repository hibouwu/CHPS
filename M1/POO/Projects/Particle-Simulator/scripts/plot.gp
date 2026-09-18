set terminal png size 800,600
set output 'unsteady_particule_positions_t0-t1.png'
set title "Particle Positions Over Time"
set xlabel "Particle index"
set ylabel "Position"
set grid

plot for [i=0:5] sprintf("particles_positions_%0.6f", i*0.2) w l title sprintf("t = %.1f", i*0.2)

set output 'unsteady_particule_velocities_t0-t1.png'
set title "Particle Velocities Over Time"
set xlabel "Particle index"
set ylabel "Velocity"

plot for [i=0:5] sprintf("particles_velocities_%0.6f", i*0.2) w l title sprintf("t = %.1f", i*0.2)
