import pytest
from prime import is_prime


def test_is_prime_with_neg_int_raise_value_error():
    with pytest.raises(ValueError):
        is_prime(-1)


def test_is_prime_with_non_int_raise_value_error():
    for value in ("str", 1.1, {}, []):
        with pytest.raises(ValueError):
            is_prime(value)


def test_is_prime_primes():
    for prime in (1, 2, 3, 5, 7, 11, 13):
        assert is_prime(prime)


def test_is_prime_non_primes():
    for non_prime in (4, 6, 9, 12, 15):
        assert not is_prime(non_prime)
