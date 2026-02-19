; ModuleID = 'simple.ll'
source_filename = "simple.ll"

define i32 @foo(i32 %arg) {
  %i_mem = alloca i64, align 8
  %arg64 = sext i32 %arg to i64
  store i32 %arg, ptr %i_mem, align 4
  %arg2 = add i32 %arg, 10
  br label %start

start:                                            ; preds = %start, %0
  %i = load i64, ptr %i_mem, align 4
  %ipp = add i64 %i, 1
  store i64 %ipp, ptr %i_mem, align 4
  %b = icmp slt i64 %i, 10
  br i1 %b, label %start, label %exit

exit:                                             ; preds = %start
  %ir = load i64, ptr %i_mem, align 4
  %ilil = trunc i64 %i to i32
  ret i32 %ilil
}
