# Set output to PNG file
set terminal png size 800,600
set output 'zipf_plot.png'

# Set to log-log scale
set logscale xy

# Add grid
set grid

# Labels
set xlabel "Rank"
set ylabel "Frequency"
set title "Zipf's Law in Moby Dick"

# Plot the data
plot "frequencies.txt" using 1:2 with points pointtype 7 pointsize 0.5 title "Word frequencies"