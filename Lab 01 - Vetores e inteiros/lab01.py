def banner_set(u, b):
    for i in range(len(u)):
        b_in_u = False
        for j in range(len(b)):
            if u[i] == b[j]:
                b_in_u = True
                break
        if not b_in_u:
            u[i] = 0
    return u


def mobius_multiplication(u, M):
    for i in range(len(u)):
        if i % 2 == 1:
            u[i] *= M
    return u


def cyclic_movement(u, P):
    aux = []
    for i in range(P):
        aux.append(u[len(u)-P+i])
    for i in range(len(u)-1, P-1, -1):
        u[i] = u[i-P]
    for i in range(P):
        u[i] = aux[i]
    return u


def vector_inversion(u):
    # Inversão manual:
    # for i in range(len(u)//2):
    #     aux = u[i]
    #     u[i] = u[len(u)-1-i]
    #     u[len(u)-1-i] = aux
    # return u

    # Inversão automática:
    u.reverse()
    return u


def operate(u):
    operation = [int(i) for i in input().split()]
    if operation[0] == 1:
        return banner_set(u, operation[2:])
    if operation[0] == 2:
        return mobius_multiplication(u, operation[1])
    if operation[0] == 3:
        return cyclic_movement(u, operation[1])
    if operation[0] == 4:
        return vector_inversion(u)


def print_vector(u):
    for i in range(len(u)):
        if i != len(u) - 1:
            print(u[i], end=' ')
        else:
            print(u[i])


def main():
    T = int(input())
    u = [int(i) for i in input().split()]
    operation_count = int(input())
    for _ in range(operation_count):
        u = operate(u)
        print_vector(u)


if __name__ == "__main__":
    main()
