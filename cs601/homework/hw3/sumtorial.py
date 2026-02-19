def f(n):
    return n * (n + 1) / 2


if __name__ == '__main__':
    print([int(f(x)) for x in range(100)])
