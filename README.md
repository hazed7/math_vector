## TL;DR
C++17 templated single file library that represents mathematical vector, a quantity that has both magnitude and direction.




## TOC
- [1. Introduction](#introduction)
- [2. Getting Started](#installation)
- [3. Features](#features)
- [4. Usage](#usage)
- [5. License](#license)






## Introduction
A vector is typically represented by an ordered set of numbers, called its components. In Vector, the components are of type T, which can be any arithmetic type.

Vector provides various operations that can be performed on vectors, including finding their magnitude, dot product, cross product, and more.





## Getting Started

### Prerequisites
To use this library you must have a C++ compiler that supports C++17 or later.

### Installation
To use this library in your project, simply include the vector.hpp header file in your code and instantiate the Vector template with the desired type, like so:
```cpp
#include "vector.hpp"

// Create a vector of 3 components with elements of type double
Vector<double> v(3);
```






## Features

### Construction
- Create an empty vector
```cpp
Vector() = default;
```

- Create a vector of a given size
```cpp
Vector(std::size_t);
```

- Create a vector from a pre-existing array
```cpp
Vector(const std::unique_ptr<T[]>&);
```

- Move constructor
```cpp
Vector(Vector&&);
```

---

### Element Access
- Access individual elements of the vector using the [] operator
```cpp
T& operator[](std::size_t);
```

- Get a pointer to the first element of the vector using the begin() iterator
```cpp
T* begin();
const T* begin() const;
```

- Get a pointer past the last element of the vector using the end() iterator
```cpp
T* end();
const T* end() const;
```

---

### Comparison
- Compare two vectors for equality or inequality using the == and != operators
```cpp
bool operator==(const Vector&) const;
bool operator!=(const Vector&) const;
```

---

### Utils
- Get size of the vector
```cpp
std::size_t size() const;
```

- Find maximal element(-s) of the vector
```cpp
std::variant<T, std::vector<std::size_t>> max() const;
```

- Find minimal element(-s) of the vector 
```cpp
std::variant<T, std::vector<std::size_t>> min() const;
```

---

### Operations
- Sum of the elements
```cpp
T sum() const;
```

- Product of the elements
```cpp
T product() const;
```

---

### Mathematical operations
- Multiply a vector by a scalar
```cpp
Vector& operator*=(T);
```

- Add or subtract two vectors
```cpp
Vector& operator+(const Vector&);
Vector& operator-(const Vector&);
```

- Calculate the magnitude (length) of a vector
```cpp
T magnitude() const;
```

- Calculate the dot product of two vectors
```cpp
friend T dot_product(const Vector&);
```

- Calculate the cross product of two vectors
```cpp
friend Vector cross_product(const Vector&, const Vector&);
```

---

### IO
- Stream the vector to an output stream using the << operator
```cpp
friend std::ostream& operator<<(std::ostream&, Vector<A> const&);
```






## Usage

### Here's the example usage:
```cpp
#include "vector.hpp"

#include <iostream>

int main() {
    Vector<double> v1(3);
    v1[0] = 1.0;
    v1[1] = 2.0;
    v1[2] = 3.0;

    Vector<double> v2(3);
    v2[0] = 4.0;
    v2[1] = 5.0;
    v2[2] = 6.0;

    Vector<double> v3 = v1 + v2;
    std::cout << v3 << std::endl;  // Prints [5, 7, 9]

    double dot = dot_product(v1, v2);
    std::cout << dot << std::endl;  // Prints 32

    Vector<double> v4 = cross_product(v1, v2);
    std::cout << v4 << std::endl;  // Prints [-3, 6, -3]

    return 0;
}
```






## License
This project is licensed under the MIT License. See the LICENSE file for details.
