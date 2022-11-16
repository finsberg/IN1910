import pytest
from bubble_sort import bubble_sort


def test_bubble_sort_correct():
    unordered = [5, 3, 2, 8, 2, 7, 9, 2]
    expected = sorted(unordered, reverse=True)

    assert expected == bubble_sort(unordered)


def test_bubble_sort_not_list_raise_value_error():
    for value in ("str", 1.1, {}, 1, True):
        with pytest.raises(ValueError):
            bubble_sort(value)


def test_bubble_sort_empty_list_return_empty_list():
    assert [] == bubble_sort([])


def test_bubble_sort_one_element_return_same_element_list():
    assert [1] == bubble_sort([1])
