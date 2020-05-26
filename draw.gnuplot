# Tohle jsem napsal v jednu rano a chci uz jit spat
# tento ---v--- prikaz slouzi k automatickemu spusteni skriptu pri ulozeni souboru ve vimu
# :autocmd BufWritePost * !gnuplot -c <afile>
#                                 _       _
#          __ _ _ __  _   _ _ __ | | ___ | |_
#         / _` | '_ \| | | | '_ \| |/ _ \| __|
#        | (_| | | | | |_| | |_) | | (_) | |_
#         \__, |_| |_|\__,_| .__/|_|\___/ \__|
#         |___/            |_|
#



set datafile separator ","

set grid mytic xtic
set xtic 0.5

set xtics rotate # rotate labels on the x axis

set style line 100 lt 1 lc rgb "grey" lw 0.5 # linestyle for the grid
set grid ls 100 # enable grid with specific linestyle
set grid

set term png
set terminal png size 1024,256
set output "out.png"

plot "samples.csv" using 1:2 lc rgb "blue" with lines title "waveform", "note_indices.csv" using 1:2 lc rgb "red" lw 2 title "detected notes"
