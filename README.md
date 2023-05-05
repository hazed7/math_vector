## TL;DR
C++17 templated single file library that represents mathematical vector




## TOC
- [1. Getting Started](#installation)
- [2. Features](#features)
- [3. Usage](#usage)
- [4. License](#license)



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
const T& operator[](std::size_t) const;
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

- Compare two vectors (std::less, std::greater, std::less_equal, std::greater_equal)
```cpp
friend bool operator<(const Vector<A>&, const Vector<A>&);
friend bool operator>(const Vector<A>&, const Vector<A>&);

friend bool operator<=(const Vector<A>&, const Vector<A>&);
friend bool operator>=(const Vector<A>&, const Vector<A>&);
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

- Get subvector of the vector between two given indices
```cpp
Vector subvec(std::size_t, std::size_t) const;
```

- Clear vector
```cpp
void clear();
```

- Resize vector to a gived size and initialize the new elements to desired value
```cpp
void resize(std::size_t size, const T& default_value);
```

- Insert methods
```cpp
// Insert a single value at the specified position in the vector
void insert(std::size_t pos, const T& value);

// Insert multiple copies of a value at the specified position in the vector
void insert(std::size_t pos, std::size_t count, const T& value);

// Insert a range of elements, specified by iterators [first, last], at the specified position in the vector
void insert(std::size_t pos, InputIt first, InputIt last);

// Insert elements from an initializer list at the specified position in the vector
void insert(std::size_t pos, std::initializer_list<T> ilist);
```

- Remove value at index
```cpp
void erase(std::size_t pos);
```

- Remove value in a range
```cpp
void erase(std::size_t first, std::size_t last);
```

- Concatenate two vectors
```cpp
friend Vector concat(const Vector&, const Vector&);
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

- Calculate the mean of a vector
```cpp
T mean() const;
```

- Calculate the median of a vector
```cpp
T median() const;
```

- Calculate the dot product of two vectors
```cpp
friend T dot_product(const Vector<A>&);
```

- Calculate the cross product of two vectors
```cpp
friend Vector<A> cross_product(const Vector<A>&, const Vector<A>&);
```

- Normalize the vector to have a magnitude of 1
```cpp
void normalize();
```
---

### IO
- Stream the vector to an output stream using the << operator
```cpp
friend std::ostream& operator<<(std::ostream&, Vector<A> const&);
```

---
### Other
- Overloaded std::swap
- Also you can use std::sort & range-based loops with it




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

    double dot = dot_product(v1, v2);
    std::cout << dot << std::endl;  // Prints 32

    auto v4 = cross_product(v1, v2);
    std::cout << v4 << std::endl;  // Prints [-3, 6, -3]

    return 0;
}
```






## License
This project is licensed under the MIT License. See the LICENSE file for details.
