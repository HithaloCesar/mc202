from math import prod


def fix_matrix(matrixes):
    for m in matrixes:
        max_col = max(m)
        for row in m:
            for _ in range(len(max_col) - len(row)):
                row.append(0)
    return matrixes


def read_matrixes(matrix_count):
    matrixes = []
    for m in range(matrix_count):
        matrixes.append([])
        do = True
        while do or line != []:
            do = False
            line = [int(x) for x in input().split()]
            if line != []:
                matrixes[m].append(line)
    return fix_matrix(matrixes)

def multiply_matrixes(matrixes):
    product = matrixes[0]
    for m in range(1, len(matrixes)):
        product[i][
        product[i][k] *= matrixes[m][k][j]
    if
    return product

1 2
3 4
5 6

1 2 3
4 5 6

(1 * 1) + ()


def print_matrix(m):
    pass


def main():
    matrix_count = int(input("Insira o número de matrizes: "))
    matrixes = read_matrixes(matrix_count)
    product = multiply_matrixes(matrixes)
    print_matrix(product)


if __name__ == "__main__":
    main()
