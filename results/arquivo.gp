set fit quiet
set title "Busca com std::bsearch Desordenado" font ",20" # O título que fica lá em cima
set ylabel "Tempo decorrido (ms)"
set xlabel "Tamanho do Vetor" # Em pt-BR msm pq é o nome de saída kk
set key left nobox
set term png
set output "graphs/mixed_wrapper_std_bsearch.png"# Arquivo (jpg, no caso) de saída
#set key right bottom
plot 'wrapper_std_bsearch/mixed_third_occurrence.dat' with lines title 'terceira ocorrencia','wrapper_std_bsearch/mixed_third_quartile.dat' with lines title '3/4', 'wrapper_std_bsearch/mixed_worst_case.dat' with lines title 'pior caso' #, ... quantos quiser

# Pra facilitar sua vida:
# se n tiver, instale o Package Control no seu sublime
# dps q instalar (e reiniciar o sublime), instale a package "Gnuplot"
# ^ (ctrl + shift + p -> digita "install" -> Package Control: Install Package -> digita "Gnuplot" -> enter)
# salve esse arquivo como um arquivo .gp
# edita as coisas no arquivo
# e roda no terminal com o comando: gnuplot -p 'arquivo.gp'