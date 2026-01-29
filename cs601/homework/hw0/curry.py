def curry2(f):
    def curry1(x):
        def curry(y):
            return f(x, y)
        return curry
    return curry1


def curryN(f, n, params=()):
    if n == 0:
        return f(*params)

    def curry(param):
        return curryN(f, n - 1, (*params, param))

    return curry


if __name__ == '__main__':
    def add2(a, b):
        return a + b

    assert curry2(add2)(3)(10) == 13

    curryN(print, 3)("i feel gr")(8)("now")  # prints i feel gr 8 now
    curryN(print, 0)   # prints one blank line (special case)
