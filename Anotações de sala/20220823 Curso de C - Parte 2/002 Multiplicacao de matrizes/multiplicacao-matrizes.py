def fix_matrix(matrixes):
    for m in matrixes:

    pass


def read_matrixes(matrix_count):
    matrixes = []
    for m in range(matrix_count):
        matrixes.append([])
        do = True
        while do or line != []:
            do = False
            line = [int(x) for x in input().split()]
            matrixes[m].append(line)
    return fix_matrix(matrixes)

def multiply_matrixes(ms):
    pass


def print_matrix(m):
    pass


def main():
    matrix_count = int(input("Insira o número de matrizes: "))
    matrixes = read_matrixes(matrix_count)
    product = multiply_matrixes(matrixes)
    print_matrix(product)


if __name__ == "__main__":
    main()
