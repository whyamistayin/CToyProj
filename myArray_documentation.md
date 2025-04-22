# myArray Class

## Implementation

**Class `myArray`** is a dynamic array implemented as a hybrid of a Double-Linked List and `std::vector`.

Generally speaking, each element has references to the previous and next element, but caching is ensured by placing  
nodes close to each other like in a basic C++ array. This guarantees that methods have reasonable time complexity.  
Although it acts similarly to `std::vector`, it provides much more functionality.

---

## Methods of `myArray` Class

### Constructors

#### Default Constructor

##### `myArray()`

Default initializer that only allocates initial memory.

---

#### Single Element Constructor

##### `myArray(T &initial)`

Initializes the array with a single element provided in the `initial` argument.

---

#### Array Copy Constructor

##### `myArray(const T *inputArray, size_t len2)`

Initializes the array with `len2` elements from a standard C/C++ array.

---

#### Copy Constructor

##### `myArray(const myArray &inputArray, size_t len2)`

Copies `len2` elements from another `myArray` instance into the newly created array. If not specified, copies all by default.

---

#### Move Constructor

##### `myArray(myArray &&inputArray)`

Move constructor that efficiently transfers the resources from the given `inputArray` to the newly created instance.  
The `inputArray` is cleared after the transfer.
- Complexity: \(O(n)\)

---

### Overloaded Operators

#### Index Operator (Node Reference)

##### `Node<T> &operator[](long long index) const`

Takes an index and returns a reference to the corresponding node of the list. This is primarily used to modify  
the data stored in nodes. The `.get_data()` method must be called on the returned node to access its value.
- Complexity: \(O(1)\)

---

#### Slicing Operator

##### `myArray<T> operator[](long long start, long long end, long long step = 1) const`

Copies a specified part of the array using slicing. The interval is defined as \[*start*, *end*] and includes every  
`step`-th element. A negative `step` allows reverse order slicing.
- Complexity: \(O(n)\)

---

#### Equality Operator

##### `bool operator==(const myArray<T> &second)`

Checks if the arrays have identical elements at each index. Returns `true` if they match, otherwise `false`.
- Complexity: \(O(n)\)

---

#### Logical NOT Operator

##### `bool operator!() const`

Returns `true` if the array is empty, otherwise `false`.
- Complexity: \(O(1)\)

---

#### Addition Operator

##### `myArray<T> operator+(myArray<T> &other)`

Creates a new `myArray` instance by copying the current array and appending the contents of `other` to it.
- Complexity: \(O(n)\)

---

#### Assignment Operator (Copy)

##### `myArray<T> &operator=(const myArray &inputArray)`

Overloads the assignment operator for copying from another `myArray` instance. Allocates memory if the target array's  
capacity is insufficient to accommodate the content of `inputArray`.
- Complexity: \(O(n)\)

---

#### Assignment Operator (Move)

##### `myArray<T> &operator=(myArray &&inputArray) noexcept`

Overloads the assignment operator for moving from another `myArray` instance. Transfers resources efficiently and clears  
the source array after the transfer.
- Complexity: \(O(n)\)

---

## **Main Functionality Methods**

### **1. `size_t length() const`**
- **Description:** Returns the number of elements in the array.
- **Complexity:** `O(1)`

### **2. `size_t memory() const`**
- **Description:** Returns the allocated memory capacity for storing elements.
- **Complexity:** `O(1)`

### **3. `T at(long long index) const`**
- **Description:** Retrieves the value stored at a given index.
- **Complexity:** `O(1)`

### **4. `myArray<int> copy()`**
- **Description:** Returns a copy of the array.
- **Complexity:** `O(n)`

### **5. `void append(const T &element)`**
- **Description:** Appends a new element to the end of the array.
- **Complexity:** `O(1)`

### **6. `void insert(T element, long long index = 0)`**
- **Description:** Inserts an element at the specified index, shifting subsequent elements.
- **Complexity:** `O(n)`

### **7. `bool in(const T &element) const`**
- **Description:** Checks if an element exists in the array.
- **Complexity:** `O(n)`

### **8. `T pop(long long index = -1)`**
- **Description:** Removes and returns the element at the specified index.
- **Default Behavior:** Removes the last element.
- **Complexity:**
    - `O(1)` for the last element.
    - `O(n)` for any other index.

### **9. `void remove(T element)`**
- **Description:** Removes the first occurrence of the specified element.
- **Complexity:** `O(n)`

### **10. `size_t index(const T &element, size_t from = 0)`**
- **Description:** Returns the index of the first occurrence of an element, starting from the specified index.
- **Exceptions:** Throws `std::out_of_range` if the element is not found.
- **Complexity:** `O(n)`

### **11. `void reverse()`**
- **Description:** Reverses the array in place.
- **Complexity:** `O(n)`

### **12. `void clear(bool shrink = true)`**
- **Description:** Clears all elements from the array. Optionally shrinks allocated memory.
- **Complexity:** `O(n)`

### **13. `void sort(bool reverse = false)`**
- **Description:** Sorts the array in ascending order by default. Use `reverse = true` for descending order.
- **Complexity:** `O(n^2)`

### **14. `void extend(const myArray<T> &second)`**
- **Description:** Appends the contents of another array to this one.
- **Complexity:** `O(n)`

### **15. `std::string str(std::string del = ", ")`**
- **Description:** Returns a string representation of the array, with elements separated by the specified delimiter.
- **Complexity:** `O(n)`

### **16. `bool isSubarray(myArray<T> &other)`**
- **Description:** Checks if another array is a subarray of this one.
- **Complexity:** `O(n^m)`

### **17. `size_t subarrayIndex(myArray<T> &other, size_t from = 0)`**
- **Description:** Finds the starting index of the first occurrence of a subarray, beginning the search from the specified index.
- **Exceptions:** Throws `std::out_of_range` if the subarray is not found.
- **Complexity:** `O(n^m)`

### **18. `void vectorise(T (*func)(T))`**
- **Description:** Applies a function to every element in the array.
- **Complexity:** `O(n)`

### **19. `int countIf(bool (*func)(T))`**
- **Description:** Counts the number of elements that satisfy a given condition.
- **Complexity:** `O(n)`

### **20. `T front()` and `T back()`**
- **Description:** Returns the first and last elements of the array, respectively.
- **Complexity:** `O(1)`

### **21. `T max()` and `T min()`**
- **Description:** Returns the largest and smallest elements in the array. Requires logical operators to be defined for the element type.
- **Complexity:** `O(n)`

### **22. `T sum()`**
- **Description:** Calculates the sum of all elements in the array. Requires the `+` operator to be defined for the element type.
- **Complexity:** `O(n)`
