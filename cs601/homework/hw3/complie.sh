opt sumtorial.ll --O3 -S -o opt.ll
llc opt.ll --filetype=obj -o sumtorial.o
gcc main.c sumtorial.o
