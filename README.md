# Better Pointer

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