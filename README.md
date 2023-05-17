# Better Pointer

Better Pointer is a concept based pointer library for C++.
It is designed where the pointer simply calls _ref() and _unref() on the object it points to.
This allows for ref counting and object deletion to be handled by the object itself.

## Example

```c++
#include <atomic>
#include <better_ptr/better_ptr.hpp>

class Object final {
    std::atomic_size_t _ref_count = 0;
    
public:
    Object() = default;
    
    void _ref() { 
        ++_ref_count; 
    }
    
    void _unref() { 
        if (--_ref_count == 0) {
            delete this; 
        } 
    }
};

int main() {
    auto ptr = better_ptr::Pointer<Object>::make();
    return 0;
}
```