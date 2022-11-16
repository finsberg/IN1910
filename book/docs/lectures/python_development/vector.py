"""
This module contains a class for representing 3-dimensional cartesian
vectors. We made this module in L6 as an example of Object-Oriented
programming.
"""
import numpy as np


class Vector3D:
    """Class for representing three-dimensional vectors."""

    def __init__(self, x, y, z):
        self.x = x
        self.y = y
        self.z = z

    def __str__(self):
        return "({:g}, {:g}, {:g})".format(self.x, self.y, self.z)

    def __repr__(self):
        return "{}({}, {}, {})".format(self.__class__.__name__, self.x, self.y, self.z)

    def __add__(self, other):
        if isinstance(other, Vector3D):
            x = self.x + other.x
            y = self.y + other.y
            z = self.z + other.z
            return Vector3D(x, y, z)

        else:
            raise TypeError("cannot add vector and {}".format(type(other)))

    def __neg__(self):
        return Vector3D(-self.x, -self.y, -self.z)

    def __sub__(self, other):
        if isinstance(other, Vector3D):
            return self + (-other)
        else:
            raise TypeError("cannot subtract vector and {}".format(type(other)))

    def dot(self, other):
        return self.x * other.x + self.y * other.y + self.z * other.z

    def cross(self, other):
        x = self.y * other.z - self.z * other.y
        y = self.z * other.x - self.x * other.z
        z = self.x * other.y - self.y * other.x
        return Vector3D(x, y, z)

    def __mul__(self, other):
        if isinstance(other, Vector3D):
            return self.dot(other)
        elif isinstance(other, (int, float)):
            return Vector3D(self.x * other, self.y * other, self.z * other)
        else:
            raise TypeError("cannot multiply vector and {}".format(type(other)))

    def __matmul__(self, other):
        """Interpret u@v as cross product"""
        return self.cross(other)

    def perpendicular(self, other):
        """Check whether two vectors are perpendicular."""
        return abs(self * other) < 1e-9

    def __rmul__(self, other):
        return self * other

    @property
    def length(self):
        return np.sqrt(self * self)

    @length.setter
    def length(self, new_length):
        scale = new_length / self.length
        self.x *= scale
        self.y *= scale
        self.z *= scale

    def unit(self):
        """Return a unit vector with the same orientation."""
        if self.length == 0:
            raise RuntimeError("Vector of zero length has no unit vector.")

        new_vector = Vector3D(self.x, self.y, self.z)
        new_vector.length = 1
        return new_vector

    def __eq__(self, other):
        same_x = np.isclose(self.x, other.x)
        same_y = np.isclose(self.y, other.y)
        same_z = np.isclose(self.z, other.z)
        return same_x and same_y and same_z
