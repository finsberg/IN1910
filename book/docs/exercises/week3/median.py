def median(data):
    """Returns the median of a dataset."""
    if len(data) == 0:
        raise ValueError("data cannot be empty")
    data.sort()
    if len(data) % 2 != 0:
        return data[len(data) // 2]
    else:
        middle_elements = data[len(data) // 2 - 1], data[len(data) // 2]
        return sum(middle_elements) / 2


# def median(data):
#    """Faulty function"""
#    data.sort()
#    return data[len(data)//2]

# def median(data):
#    """Upgraded, still faulty"""
#    data.sort()
#    if len(data) % 2 != 0:
#        return data[len(data)//2]
#    else:
#        middle_elements = data[len(data)//2 - 1], data[len(data)//2]
#        return sum(middle_elements)/2

print(median([11, 3, 1, 5, 3]))
