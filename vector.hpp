//
//  vector.hpp
//  maksim_kursovaya
//
//  Created by Alexander on 24.03.2023.
//

#ifndef vector_hpp
#define vector_hpp

#include <algorithm>
#include <vector>
#include <numeric>
#include <variant>
#include <memory>

template <typename T>
class Vector {
public:
    Vector() = default;
    Vector(std::size_t);
    Vector(const std::unique_ptr<T[]>&);
    Vector(Vector&&);
    
    std::size_t size() const;
    T magnitude() const;
    
    T mean() const;
    
    std::variant<T, std::vector<std::size_t>> max() const;
    std::variant<T, std::vector<std::size_t>> min() const;
    
    T sum() const;
    T product() const;
    
    void normalize();
    void clear();
    
    Vector subvec(std::size_t, std::size_t) const;
    
    T& operator[](std::size_t);
    bool operator==(const Vector&) const;
    bool operator!=(const Vector&) const;
    
    template <typename A>
    friend bool operator<(const Vector<A>&, const Vector<A>&);
    
    template <typename A>
    friend bool operator>(const Vector<A>&, const Vector<A>&);
    
    template <typename A>
    friend bool operator<=(const Vector<A>&, const Vector<A>&);
    
    template <typename A>
    friend bool operator>=(const Vector<A>&, const Vector<A>&);
    
    Vector& operator*=(T);
    Vector& operator+(const Vector&);
    Vector& operator-(const Vector&);
    
    template <typename A>
    friend A dot_product(const Vector<A>&, const Vector<A>&);
    
    template <typename A>
    friend Vector cross_product(const Vector<A>&, const Vector<A>&);
    
    template <typename A>
    friend std::ostream& operator<<(std::ostream&, Vector<A> const&);
    
    // iterators
    T* begin();
    const T* begin() const;
    
    T* end();
    const T* end() const;
private:
    std::size_t size_;
    std::unique_ptr<T[]> entries;
};

// overload std::swap
namespace std {
    template <typename T>
    void swap(Vector<T>& v1, Vector<T>& v2) noexcept(noexcept(v1.swap(v2))) {
        v1.swap(v2);
    }
}

// print vector elements
template <typename T>
std::ostream& operator<<(std::ostream& os, Vector<T> const& vec) {
    if (!vec.entries)
        return os << "nullptr";
    
    os << "[";
    for (std::size_t i = 0; i < vec.size(); i++) {
        os << vec.entries[i];
        if (i < vec.size() - 1)
            os << ", ";
    }
    os << "]";
    
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<std::size_t>& indexes) {
    os << "[";
    for (std::size_t i = 0; i < indexes.size(); i++) {
        os << indexes[i];
        if (i < indexes.size() - 1)
            os << ", ";
    }
    os << "]";
    
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::variant<T, std::vector<std::size_t>>& value) {
    std::visit([&](auto&& arg) {
        os << arg;
    }, value);
    
    return os;
}

template <typename T>
Vector<T>::Vector(std::size_t size)
    : size_(size),
      entries(std::make_unique<T[]>(size_))
{}

/*
 @brief         Constructs a Vector object from a unique_ptr to an array.
 @tparam T      the type of elements in the array.
 @param vec     the unique_ptr to the array to construct the vector from.
 
 This constructor takes a unique_ptr to an array and constructs a Vector
 object from it. The size of the vector is determined by the size of the array
 pointed to by the unique_ptr. If the unique_ptr is null, the size of the
 vector is 0.
 
 Note that ownership of the array is transferred to the Vector object, so
 the array should not be accessed or modified after constructing the vector.
*/
template <typename T>
Vector<T>::Vector(const std::unique_ptr<T[]>& vec)
    // returns the size of the array pointed to by vec.
    // If vec is null, then vec.get() returns a null pointer
    // and the ternary operator evaluates to the second operand, which is 0, resulting in a vector of size 0.
    : size_(vec.get() ? std::extent<decltype(vec)>::value : 0),
      entries(std::move(vec))
{}

template <typename T>
Vector<T>::Vector(Vector&& other)
    : size_(other.size_),
      entries(std::move(other.entries))
{}

template <typename T>
std::size_t Vector<T>::size() const {
    return size_;
}

template <typename T>
T Vector<T>::magnitude() const {
    return std::sqrt(dot_product(*this, *this));
}

template <typename T>
T Vector<T>::mean() const {
    if (size_ == 0)
        throw std::logic_error("Vector is empty");
    
    return sum() / size_;
}

/*
 @brief     Finds the maximum element(s) in the vector.
 @return    A std::variant object containing either the maximum element or a vector of indexes of the maximum elements.
 
 This function finds the maximum element(s) in the vector and returns them in a std::variant object.
 If there is only one maximum element, the function returns the element itself.
 If there are multiple maximum elements, the function returns a vector of indexes of those elements.
 
 The function uses the std::max_element function to find the maximum element(s) in the vector.
 
 If there is only one maximum element, the function counts the number of occurrences of that element in the vector.
 If there is only one occurrence, the function returns the index of that element.
 If there are multiple occurrences, the function creates a vector of indexes of those occurrences and returns it.
 
 Note that if the vector is empty, the function returns the default-constructed std::variant object,
 which contains the value of the first alternative (i.e., a default-constructed T object).
*/
template <typename T>
std::variant<T, std::vector<std::size_t>> Vector<T>::max() const {
    auto max_it = std::max_element(entries.get(), entries.get() + size_);
    
    if (std::count(entries.get(), entries.get() + size_, *max_it) == 1)
        return std::distance(entries.get(), max_it);
    else {
        std::vector<std::size_t> indexes;
        for (auto it = entries.get(); it != entries.get() + size_; ++it)
            if (*it == *max_it)
                indexes.push_back(std::distance(entries.get(), it));
        
        return indexes;
    }
}

template <typename T>
std::variant<T, std::vector<std::size_t>> Vector<T>::min() const {
    auto min_it = std::min_element(entries.get(), entries.get() + size_);
    
    if (std::count(entries.get(), entries.get() + size_, *min_it) == 1)
        return std::distance(entries.get(), min_it);
    else {
        std::vector<std::size_t> indexes;
        for (auto it = entries.get(); it != entries.get() + size_; ++it)
            if (*it == *min_it)
                indexes.push_back(std::distance(entries.get(), it));
        
        return indexes;
    }
}

template <typename T>
T Vector<T>::sum() const {
    return std::accumulate(entries.get(), entries.get() + size(), T());
}

template <typename T>
T Vector<T>::product() const {
    return std::accumulate(entries.get(), entries.get() + size(), T(1), std::multiplies<>());
}

template <typename T>
void Vector<T>::normalize() {
    static_assert(std::is_same_v<T, float> || std::is_same_v<T, double>, "Vector should consist of double or float types");
    
    T mag = magnitude();
    if (mag == 0)
        return;
    
    *this *= 1 / mag;
}

template <typename T>
void Vector<T>::clear() {
    size_ = 0;
    entries.reset();
}

template <typename T>
Vector<T> Vector<T>::subvec(std::size_t start, std::size_t end) const {
    if (start >= end || end > size_)
        throw std::out_of_range("Invalid range for subvector");
    
    Vector<T> sub(end - start);
    std::copy(entries.get() + start, entries.get() + end,sub.entries.get());
    
    return sub;
}

template <typename T>
T& Vector<T>::operator[](std::size_t i) {
    return entries[i];
}

template <typename T>
bool Vector<T>::operator==(const Vector& other) const {
    return entries == other.entries;
}

template <typename T>
bool Vector<T>::operator!=(const Vector& other) const {
    return entries != other.entries;
}

template <typename T>
bool operator<(const Vector<T>& v1, const Vector<T>& v2) {
    return std::lexicographical_compare(v1.entries.get(), v1.entries.get() + v1.size(),
                                        v2.entries.get(), v2.entries.get() + v2.size());
}

template <typename T>
bool operator>(const Vector<T>& v1, const Vector<T>& v2) {
    return std::lexicographical_compare(v2.entries.get(), v2.entries.get() + v2.size(),
                                        v1.entries.get(), v1.entries.get() + v1.size());
}

template <typename T>
bool operator<=(const Vector<T>& v1, const Vector<T>& v2) {
    return !(v2 < v1);
}

template <typename T>
bool operator>=(const Vector<T>& v1, const Vector<T>& v2) {
    return !(v1 < v2);
}

template <typename T>
Vector<T>& Vector<T>::operator*=(T scalar) {
    std::transform(entries.get(),
        entries.get() + size_,
        entries.get(), [scalar](T x)
    {
        return x * scalar;
    });
    
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator+(const Vector& other) {
    if (size() != other.size())
        throw std::invalid_argument("Vectors must have the same size");
    
    Vector<T> result(size());
    std::transform(entries.get(), entries.get() + size(), other.entries.get(), entries.get(), std::plus<>());
    
    return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator-(const Vector& other) {
    if (size() != other.size())
        throw std::invalid_argument("Vectors must have the same size");
    
    Vector<T> result(size());
    std::transform(entries.get(), entries.get() + size(), other.entries.get(), entries.get(), std::minus<>());
    
    return *this;
}

template <typename T>
T dot_product(const Vector<T>& u, const Vector<T>& v) {
    if (u.size() != v.size())
        throw std::invalid_argument("Vectors must have the same size");
    
    return std::inner_product(u.entries.get(),
                              u.entries.get() + u.size(),
                              v.entries.get(), T());
}

template <typename T>
Vector<T> cross_product(const Vector<T>& lhs, const Vector<T>& rhs) {
    if (lhs.size() != rhs.size())
        throw std::invalid_argument("Vectors must have the same size");
    
    Vector<T> w(lhs.size());
    for (std::size_t i = 0; i < lhs.size(); i++) {
        w[i] = std::inner_product(lhs.entries.get(),
                                  lhs.entries.get() + lhs.size(),
                                  rhs.entries.get(), T(),
                                  std::minus<>(),
                                  [i](T x, T y) {
                                      return x * y[i];
                                  });
    }
    
    return w;
}

template <typename T>
T* Vector<T>::begin() {
    return entries.get();
}

template <typename T>
const T* Vector<T>::begin() const {
    return entries.get();
}

template <typename T>
T* Vector<T>::end() {
    return entries.get() + size_;
}

template <typename T>
const T* Vector<T>::end() const {
    return entries.get() + size_;
}

#endif /* vector_hpp */

