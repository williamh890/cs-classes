define i64 @sumtorial(i64 %n) {
start:
	br label %loop

loop:
	%i = phi i64 [ %n, %start ], [ %nextI, %loop ]
	%sum = phi i64 [ 0, %start ], [ %nextSum, %loop ]
	%nextI = add i64 %i, -1
	%shouldContinue = icmp sgt i64 %nextI, 0

	%nextSum = add i64 %sum, %i

	br i1 %shouldContinue, label %loop, label %end

end:
	ret i64 %nextSum
}
