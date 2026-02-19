opt simple.ll -passes=verify,mem2reg -S -o opt.ll
llc opt.ll --filetype=obj -o simple.o
gcc main.c simple.o
