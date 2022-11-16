def is_prime(n):
    print(type(n))
    if not isinstance(n, int):
        raise ValueError(f"Expected int: {type(n)}")
    elif n < 0:
        raise ValueError(f"Expected positive int: {n}")
    elif n in [1, 2]:
        return True
    for i in range(2, n):
        if n % i == 0:
            return False

    return True
