define i32 @foo(i32 %arg) {
	%i_mem = alloca i64

	%arg64 = sext i32 %arg to i64

	store i32 %arg, ptr %i_mem

	%arg2 = add i32 %arg, 10
	br label %start

start:
	%i = load i64, ptr %i_mem
	%ipp = add i64 %i, 1

	store i64 %ipp, ptr %i_mem
	%b = icmp slt i64 %i, 10
	br i1 %b, label %start, label %exit

exit:
	%ir = load i64, ptr %i_mem
	%ilil = trunc i64 %i to i32
	ret i32 %ilil
}
