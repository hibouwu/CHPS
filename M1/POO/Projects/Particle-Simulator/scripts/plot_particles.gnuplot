set terminal pngcairo size 800,600

set title "Particle positions at t = 1s"
set xlabel "Particle index"
set ylabel "Position"
set output "steady_particule_positions_t1.png"
plot "particles_positions" using ($0+1):1 with linespoints title "x(t=1)"

set title "Particle velocities at t = 1s"
set xlabel "Particle index"
set ylabel "Velocity"
set output "steady_particule_velocities_t1.png"
plot "particles_velocities" using ($0+1):1 with linespoints title "v(t=1)"
