def bubble_sort(lst):
    if not isinstance(lst, list):
        raise ValueError(f"Expected list: {type(lst)}")
    elif len(lst) < 2:
        return lst.copy()

    copy = lst.copy()

    for i in range(len(lst), 1, -1):
        for j in range(i - 1):
            if copy[j + 1] > copy[j]:
                copy[j], copy[j + 1] = copy[j + 1], copy[j]

    return copy
