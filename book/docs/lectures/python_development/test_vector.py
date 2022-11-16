import pytest
from vector import Vector3D


def test_add():
    u = Vector3D(1, 2, 0)
    v = Vector3D(1, -1, 3)
    assert (u + v) == Vector3D(2, 1, 3)


def test_eq():
    u = Vector3D(1, 2, 0)
    assert u == Vector3D(1, 2, 0)
    assert u == Vector3D(1.00000001, 2, 0)
    assert u != Vector3D(1, 2, 1)
    assert u != Vector3D(1.001, 2, 0)


def test_sub():
    """Test subtraction"""
    u = Vector3D(1, 2, 0)
    v = Vector3D(1, -1, 3)
    assert (u - v) == Vector3D(0, 3, -3)


def test_dot():
    """Test dot product"""
    u = Vector3D(1, 2, 0)
    v = Vector3D(1, -1, 3)
    assert u.dot(v) == -1
    assert u * v == -1


def test_cross():
    """Test cross product"""
    u = Vector3D(1, 2, 0)
    v = Vector3D(1, -1, 3)
    assert u.cross(v) == Vector3D(6, -3, -3)
    assert u @ v == Vector3D(6, -3, -3)


def test_perp():
    """Test perpendicularity"""
    u = Vector3D(1, 2, 0)
    v = Vector3D(1, -1, 3)
    assert not u.perpendicular(v)
    assert (u @ v).perpendicular(u)
    assert (u @ v).perpendicular(v)


def test_length():
    """Test length"""
    u = Vector3D(1, 2, 0)
    v = Vector3D(1, -1, 3)
    assert (u.length**2 - 5) < 1e-12
    assert (v.length**2 - 11) < 1e-12


def test_no_scalar_addition():
    with pytest.raises(TypeError):
        Vector3D(1, 1, 0) + 3


def test_no_unit_vector():
    with pytest.raises(RuntimeError):
        Vector3D(0, 0, 0).unit()


if __name__ == "__main__":
    pytest.main()
