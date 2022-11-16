import pytest
from median import median


def test_median_one_element_list():
    assert 1 == median([1])


def test_median_two_element_list():
    lst = [2, 3]
    expected = 2.5
    actual = median(lst)
    assert expected == actual


def test_median_empty_list_raise_value_error():
    with pytest.raises(ValueError):
        median([])


def test_median_empty_tuple_raise_value_error():
    with pytest.raises(ValueError):
        median(())
