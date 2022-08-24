ERROR = 1e-12


def square_root(x):
    low = 0
    high = x
    guess = x
    while not abs(guess * guess - x) <= ERROR:
        if guess * guess > x:
            high = guess
        if guess * guess < x:
            low = guess
        guess = (high + low) / 2
    return guess


def main():
    x = int(input("Insira um número: "))
    print("Raiz quadrada:", square_root(x))


if __name__ == "__main__":
    main()
