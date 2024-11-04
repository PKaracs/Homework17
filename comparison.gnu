# Set output to PNG file
set terminal png size 1200,800
set output 'zipf_comparison.png'

# Set to log-log scale
set logscale xy

# Add grid
set grid

# Set labels
set xlabel "Rank"
set ylabel "Frequency"
set title "Zipf's Law Comparison: Moby Dick vs Anthem"

# Set legend
set key top right

# Plot both datasets
plot "frequencies_moby.txt" using 1:2 with points pointtype 7 pointsize 0.5 title "Moby Dick", \
     "frequencies_anthem.txt" using 1:2 with points pointtype 9 pointsize 0.5 title "Anthem"