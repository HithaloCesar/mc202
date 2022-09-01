ERROR = 1e-12


def square_root(x):
    y = x
    small_error = False
    while not small_error:
        previous_y = y
        y = (y + x / y) / 2
        if abs(previous_y - y) <= ERROR:
            small_error = True
    return y


def main():
    x = int(input("Insira um número: "))
    print("Raiz quadrada:", square_root(x))


if __name__ == "__main__":
    main()
