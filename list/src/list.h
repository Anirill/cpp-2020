//#include "list.h"

// Your code goes here...


#pragma once
#include <iterator>
//#include <memory>


namespace task {

//template <class U, class Alloc = std::allocator<U>>


template<class T, class Alloc = std::allocator<T>>
class list {
    struct Node;
public:
    using value_type = T;
    using allocator_type = Alloc;
    typedef typename std::allocator_traits<allocator_type>::template rebind_alloc<Node> _node_allocator;
    //using _node_allocator = std::allocator_traits<allocator_type>::template rebind_alloc<Node>;
    //typedef typename allocator_type::rebind<Node>::other _node_all;    
    //std::allocator_traits<A>::rebind_alloc<Node<T>>
    //using node_allocator_type = allocator_type::rebind<Node>::_allocator;
    using _traits = std::allocator_traits<allocator_type>;
    using _node_traits = std::allocator_traits<_node_allocator>;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using node_pointer = Node*;
    using pointer = T*;
    using reference = T&;
    using const_pointer = const T*;
    using const_reference = const T&;

    template<typename P, typename R>
    class iterator_base {
    public:
        using difference_type = ptrdiff_t;
        using value_type = T;
        using pointer = P;
        using reference = R;

        using iterator_category = std::bidirectional_iterator_tag;

        iterator_base() = delete;
        explicit iterator_base(node_pointer c) : curr(c) {
            if (curr != NULL)
                pr = curr->prev;
        };        
        // explicit iterator_base(node_pointer c) : curr(c) {
        //     if (curr != NULL)
        //         pr = curr->prev;
        // };        
        
        iterator_base(const iterator_base& it) : curr(it.curr) {
            if (curr != NULL)
                pr = curr->prev;;
        };    
        ~iterator_base() = default;    

        iterator_base& operator=(const iterator_base& other) {
            if (this != &other) {
                this->curr = other.curr;
                if (this->curr != NULL)
                    this->pr = this->curr->prev;;
            }
            return *this;
        };

        node_pointer& operator& () {
            return this->curr;
        }

        reference operator*() const {
            // if (curr == nullptr)
            //     return value_type();
            return curr->value;
        }

        pointer operator->() const {
            if(curr == nullptr)
                return nullptr;
            return &(curr->value);
        }

        iterator_base& operator++() {
            pr = curr;
            curr = curr->next;
            return *this;
        }

        iterator_base operator++(int trash) {
            iterator_base *tmp = this;
            pr = curr;
            curr = curr->next;
            return *tmp;
        }

        iterator_base& operator--() {
            if (curr != NULL) {
                curr = curr->prev;                
            }
            else {
                curr = pr;
            }
            if (curr != NULL) {
                pr = curr->prev;
            }
            return *this;
        }

        iterator_base operator--(int trash) {
            iterator_base *tmp = this;
            if (curr != NULL) {
                curr = curr->prev;
            }
            else {
                curr = pr;
            }
            if (curr != NULL) {
                pr = curr->prev;
            }
            //curr = curr->prev;
            return *tmp;
        }

        bool operator==(iterator_base other) const {
            return other.curr == this->curr;
        }

        bool operator!=(iterator_base other) const {
            return !(*this == other);
        }

    private:
        node_pointer curr;
        node_pointer pr;
        
        // Your code hoes here...
    };

    // class const_iterator : iterator {
    // public:
    //     using difference_type = ptrdiff_t;
    //     using value_type = T;
    //     using pointer = const T*;
    //     using reference = const T&;
    //     using iterator_category = std::bidirectional_iterator_tag;    

    //     const_iterator operator--(int trash) {
    //         const_iterator *tmp = this;
    //         this->curr = curr->prev;
    //         return *tmp;
    //     }

    //     const_iterator operator++(int trash) {
    //         const_iterator *tmp = this;
    //         this->curr = curr->next;
    //         return *tmp;
    //     }
    // private:
    //     Node *curr;    
    // };


    //typedef typename allocator_type::rebind<T>::other _node_all;

    //using _traits = std::allocator_traits<allocator_type>


    using iterator = iterator_base<pointer, reference>; 
    using const_iterator = iterator_base<const_pointer, const_reference>;     
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    

    //list(); // +
    //list(const list &l); 
    
    //explicit list(const Alloc& alloc); //
    //list(size_t count, const T& value, const Alloc& alloc = Alloc()); //
    //explicit list(size_t count, const Alloc& alloc = Alloc()); //
    //list(const list& other);

    //~list(); // 

    list(list&& other) {

    };

    list() : first(nullptr), 
             last(nullptr), 
             s(0), 
             _allocator(allocator_type()) {;}

    explicit list(
        const Alloc& alloc
        ) : first(nullptr), 
            last(nullptr), 
            s(0), 
            _allocator(alloc) {;}; //   

    list(size_type count, 
         const_reference value, 
         const Alloc& alloc = Alloc()
        ) : first(nullptr), 
            last(nullptr), 
            s(0), 
            _allocator(alloc) {
        for (size_type i = 0; i < count; i++) {
            push_back(value);
        }    
    }    

    explicit list(
        size_type count, 
        const Alloc& alloc = Alloc()
        ) : first(nullptr), 
            last(nullptr), 
            s(0), 
            _allocator(alloc) {
        value_type value = value_type();
        for (size_t i = 0; i < count; i++) {
            push_back(value);
        }            
    }

    list(list& other,  // const does not work
         const Alloc& alloc = Alloc()
        ) : first(nullptr), 
            last(nullptr), 
            s(0), 
            _allocator(other._allocator) {
        //node_pointer it = &other.begin();
        auto it = other.begin();
        for (size_type i = 0; i < other.size(); i++) {
            //push_back(it->value);
            //it = it->next;
            push_back(*it);
            it++;            
        }        
    }

    ~list() {
        clear();
    }

    //Alloc get_allocator() const; //

    Alloc get_allocator() const {
        return _allocator;
    }

    //list& operator=(const list& other);
    // list& operator=(list&& other);
    // {  // using iterator???
    //     this->clear();
    //     this = list(std::move(other));
    //     // this->_allocator = other.get_allocator();
    //     // auto it = other.cbegin();
    //     // for (size_type i = 0; i < other.size(); i++) {
    //     //     push_back(it->value);
    //     //     it++;
    //     // }       
    //     return *this;
    // }


    list& operator=( list& other) {  // using iterator???
        this->clear();
        auto it = other.begin();
        for (size_type i = 0; i < other.size(); i++) {
            //push_back(it->value);
            //it = it->next;
            push_back(*it);
            it++;            
        }     
        //*this = list(other);
        // this->_allocator = other.get_allocator();
        // auto it = other.cbegin();
        // for (size_type i = 0; i < other.size(); i++) {
        //     push_back(it->value);
        //     it++;
        // }       
        return *this;
    }


    T& front() {
        return first->value;
    };
    const T& front() const {
        return first->value;
    };

    T& back(){
        return last->value;
    };

    const T& back() const {
        return last->value;
    };


    iterator begin() {
        //iterator it = iterator(front);
        return iterator(first);
    };
    iterator end(){
        //iterator it = iterator(back);
        auto it = iterator(last);
        ++it;
        return it;
    };

    const_iterator cbegin() {
        return const_iterator(first);
    };
    const_iterator cend() {
        auto it = const_iterator(last);
        ++it;
        return it;
    };

    reverse_iterator rbegin() {
        return reverse_iterator(last);
    };
    reverse_iterator rend() {
        return reverse_iterator(first);
    };

    const_reverse_iterator crbegin() {
        return const_reverse_iterator(last);
    };
    const_reverse_iterator crend() {
        return const_reverse_iterator(first);
    };


    //bool empty() const; //
    //size_t size() const;//
    //size_t max_size() const;//
    //void clear();//

    size_type size() const {
        return this->s;
    }

    size_type max_size() const {
        return SIZE_MAX;
    }

    bool empty() const {
        return (first == NULL && last == NULL);
    }

    void clear() {        
        while (!this->empty()) {
        //while (this->s != 0) {            
            this->pop_back();
        }
        return;
    }

    // bool insert_base_c (iterator pos, const T& value) {
    //     if (pos == this->end()) {
    //         //for (size_t i = 0; i < count; i++) {
    //             push_back(value);
    //             //this->s--;
    //             return true;
    //             //pos++;
    //         //}            
    //     }
    //     else if (pos == this->begin()) {
    //         //for (size_t i = 0; i < count; i++) {
    //             push_front(value);
    //             //this->s--;
    //             return true;
    //             //pos++;
    //         //}     
    //     }
    //     return false;
    // }

    bool insert_base_m (iterator pos, const T&& value) {
        if (pos == this->end()) {
            //for (size_t i = 0; i < count; i++) {
                push_back(std::move(value));
                //this->s--;
                return true;
                //pos++;
            //}            
        }
        else if (pos == this->begin()) {
            //for (size_t i = 0; i < count; i++) {
                push_front(std::move(value));
                //this->s--;
                return true;
                //pos++;
            //}     
        }
        return false;
    }

    iterator insert(const_iterator pos, const T& value) {
        return insert(pos, 1, value);
        // if(insert_base_c(pos, value))
        //     return pos;
        // else            
        //     return emplace(pos, value);
    };
    iterator insert(iterator pos, const T& value) {
        return insert(pos, 1, value);
        // if(insert_base_c(pos, value))
        //     return pos;
        // else                    
        //     return emplace(pos, value);
    };
    iterator insert(const_iterator pos, T&& value){
        if(insert_base_m(pos, std::move(value)))
            return pos;            
        else {
            node_pointer prev_buf = (&pos)->prev;
            node_pointer next_buf = &pos;
            prev_buf->next = NULL;
            prev_buf->next = &emplace(iterator(prev_buf->next), std::move(value));
            prev_buf->next->prev = prev_buf;
            prev_buf->next->next = next_buf;
            next_buf->prev = prev_buf->next;
            this->s++;
            return iterator(prev_buf->next); 
        }
              
    }    
    iterator insert(iterator pos, T&& value){
        if(insert_base_m(pos, std::move(value)))
            return pos;
        else {        
            node_pointer prev_buf = (&pos)->prev;
            node_pointer next_buf = &pos;
            prev_buf->next = NULL;
            prev_buf->next = &emplace(iterator(prev_buf->next), std::move(value));
            prev_buf->next->prev = prev_buf;
            prev_buf->next->next = next_buf;
            next_buf->prev = prev_buf->next;
            this->s++;
            return iterator(prev_buf->next); 
        }
    }

    // iterator insert(const_iterator pos, size_t count, const T& value){
    //     if (pos == this->end()) {
    //         for (size_t i = 0; i < count; i++) {
    //             push_back(value);
    //             //pos++;
    //         }
    //     }
    //     for (size_t i = 0; i < count; i++) {
    //         insert(pos, value);
    //         pos++;
    //     }
    //     return iterator(pos);
    // };

    iterator insert(iterator pos, size_t count, const T& value){
        if (pos == this->end()) {
            for (size_t i = 0; i < count; i++) {
                push_back(value);
                //pos++;
            }            
        }
        else if (pos == this->begin()) {
            for (size_t i = 0; i < count; i++) {
                push_front(value);
                //pos++;
            }     
        }
        else {
            node_pointer prev_buf;
            node_pointer next_buf;
            for (size_t i = 0; i < count; i++) {
                prev_buf = (&pos)->prev;
                next_buf = &pos;
                prev_buf->next = NULL;
                prev_buf->next = &emplace(iterator(prev_buf->next), value);
                prev_buf->next->prev = prev_buf;
                prev_buf->next->next = next_buf;
                next_buf->prev = prev_buf->next;
                //insert(pos, value);
                pos++;
                this->s++;
            }
        }
        return pos;
    };


    iterator erase(iterator pos) {
        if(pos == this->end())
            return this->end();
        if (&pos == last) {
            pop_back();     
            return this->end();
        }
        else if (pos == this->begin()) {
            pop_front();
            return iterator(first);
        }
        else {
            node_pointer prev_buf = (&pos)->prev;
            node_pointer next_buf = (&pos)->next;            
            delete_node(&pos);
            prev_buf->next = next_buf;
            if (next_buf != NULL)
                next_buf->prev = prev_buf;
            this->s--;        
            return iterator(next_buf);
        }        
    };

    iterator erase(iterator f, iterator l) {
        auto i = f;
        for (; i != l;) {
            i = erase(i);
        }
        return iterator(&i);
    };



    //void push_back(const T& value);
    //void push_back(T&& value);
    //void pop_back();

    // void create_node(Node* &p, const value_type &value) {
    //     p = _node_all.allocate(1);
    //     _node_all.construct(p, value);
    //     return;
    // }

    void delete_node(Node* &p) {
        _node_all.destroy(p);
        _node_all.deallocate(p, 1);
        return;
    }



    void push_back(const T& value) {
        
        if(last == nullptr) {
            last = &(emplace(this->cbegin(), value));    
            // if (last == NULL)
            //     this->s = 111;
            first = last;    
            last->next = nullptr;
            first->prev = nullptr;
        }

        //last->next = _traits::template rebind_alloc<Node>::allocate(1);
        //_traits::template rebind_alloc<Node>::construct(last->next, value);        
        //last->next = _node_traits::allocate(size_t(1));
        //_node_traits::construct(last->next, value);     
        else {            
            //std::cout << sizeof(Node);
            //create_node(last->next, value);
            emplace_back(value);
            //last->next = _node_all.allocate(1);
            //_node_all.construct(last->next, value);        
            last->next->prev = last;
            last = last->next;
            last->next = nullptr;
        }
        //std::printf("%d", s);
        //return;
        this->s++;
        //std::printf("%d", s);
        
        return;
    }

    void push_back(T&& value){
        if(last == nullptr) {
            //last = _node_all.allocate(1);
            //last->value = std::move(value);
            //last = (emplace_back(std::move(value)))->curr;
            last = &emplace(this->cbegin(), std::move(value));
            first = last;    
            last->next = nullptr;
            first->prev = nullptr;
        }
        else {            
            //last->next = _node_all.allocate(1);
            //last->next->value = std::move(value);
            emplace_back(std::move(value));
            last->next->prev = last;
            last = last->next;
            last->next = nullptr;
        }
        this->s++;
        return;
    };

    void pop_back() { // last and first deallocate
        if(last == nullptr) {
            return;
        }
        if (last == first) {
            delete_node(last);
            //_node_all.destroy(last);
            //_node_all.deallocate(last, 1);
            last = first = nullptr;        
            this->s = 0;
            return;              
        }
        else {
            last = last->prev;           
            //_traits::template rebind_alloc<Node>::destroy(last->next, 1);
            //_traits::template rebind_alloc<Node>::deallocate(last->next, 1);
            //_node_traits::destroy(_node_all, last->next);
            //_node_traits::destroy(last->next, std::size_t(1));
            //_node_traits::deallocate(last->next, size_t(1));
            //_node_all.destroy(last->next);
            //_node_all.deallocate(last->next, 1);
            delete_node(last->next);
            last->next = nullptr; 
        }  
        this->s--;    
        return;        
    };

    //void push_front(const T& value);
    //void push_front(T&& value);
    //void pop_front();
    //
    


    void push_front(const T& value) {
        if(first == nullptr) {
            //create_node(first, value);
            //first = (emplace_front(value))->curr;
            first = &emplace(this->cbegin(), value);
            //first = _node_all.allocate(1);
            //_node_all.construct(first, value);    
            last = first;    
            last->next = nullptr;
            first->prev = nullptr;
        }
        //first->prev = _traits::template rebind_alloc<Node>::allocate(1);
        //_traits::template rebind_alloc<Node>::construct(first->prev, value); 
       // first->prev = _node_traits::allocate(size_t(1));
       // _node_traits::construct(first->prev, value); 
        else {
            //create_node(first->prev, value);
            emplace_front(value);
            //first->prev = _node_all.allocate(1);
            //_node_all.construct(first->prev, value); 
            first->prev->next = first;
            first = first->prev;
            first->prev = nullptr;
            //first->value = value_type(value);
        }
        this->s++;
        return;
    };

    void push_front(T&& value) {
        if(first == nullptr) {
            //first = _node_all.allocate(1);
            //first->value = std::move(value);
            //first = (emplace_front(std::move(value)))->curr;
            first = &emplace(this->cbegin(), std::move(value));
            last = first;    
            last->next = nullptr;
            first->prev = nullptr;
        }
        else {
            //first->prev = _node_all.allocate(1);
            //first->prev->value = std::move(value);
            emplace_front(std::move(value));
            first->prev->next = first;
            first = first->prev;
            first->prev = nullptr;
        }
        this->s++;
        return;
    };

    void pop_front() {
        if(first == nullptr)
            return;
        if (last == first) {
            delete_node(first);
            //_node_all.destroy(last);
            //_node_all.deallocate(last, 1);
            last = first = nullptr;        
            this->s = 0;
            return;   
        }
        else
        {
            first = first->next;      
            //_traits::template rebind_alloc<Node>::destroy(first->prev, 1);             
            //_traits::template rebind_alloc<Node>::deallocate(first->prev, 1);
            //_node_traits::destroy(_node_all, first->prev);             
            //_node_traits::destroy(first->prev, size_t(1));             
            //_node_traits::deallocate(first->prev, size_t(1));
            //_node_all.destroy(first->prev);             
            //_node_all.deallocate(first->prev, 1);
            delete_node(first->prev);
            first->prev = nullptr; 

        }
        this->s--;
        return;
    };

    template <class... Args>
    iterator emplace(const_iterator pos, Args&&... args) {
        // if (&pos == &this->begin()) 
        //     //push_back()
        //     emplace_front(std::forward<Args>(args)...);
        // else if (&pos == &this->end())
        //     emplace_back(std::forward<Args>(args)...);
        // else {
        &pos = _node_all.allocate(1);
        _node_all.construct(&pos, std::forward<Args>(args)...);
        // }
        return iterator(&pos);
    };

    template <class... Args>
    iterator emplace(iterator pos, Args&&... args) {
        // if (&pos == &this->begin()) 
        //     //push_back()
        //     emplace_front(std::forward<Args>(args)...);
        // else if (&pos == &this->end())
        //     emplace_back(std::forward<Args>(args)...);
        // else {
            &pos = _node_all.allocate(1);
            _node_all.construct(&pos, std::forward<Args>(args)...);
        // }
        return iterator(&pos);
    };

    template <class... Args>
    void emplace_back(Args&&... args) {
        last->next = _node_all.allocate(1);
        _node_all.construct(last->next, std::forward<Args>(args)...);
        return;
    };

    template <class... Args>
    void emplace_front(Args&&... args) {
        first->prev = _node_all.allocate(1);
        _node_all.construct(first->prev, std::forward<Args>(args)...);
        return;
    };


    //void resize(size_t count);
    //void swap(list& other);

    void resize(size_t count) {
        value_type value = value_type();
        while (s < count) {
            push_back(value);
        }    
        while (s > count) {
            pop_back();
        }    
    };

    void swap(list& other) {
        if (_traits::propagate_on_container_swap::value)
            std::swap (_allocator, other._allocator);
        if (_node_traits::propagate_on_container_swap::value)
            std::swap (_node_all, other._node_all);        
        //list *tmp = this;
        std::swap(first, other.first);
        std::swap(last, other.last);
        std::swap(s, other.s);
    };

    void swap(node_pointer a, node_pointer b) {
        if(a == b || a == nullptr || b == nullptr)
            return;
        value_type buf = a->value;
        a->value = b->value;
        b->value = buf;
        // Node buf = Node();
        // buf.next = a->next;
        // buf.prev = a->prev;
        // buf.value = a->value;
        // a->next = b->next;
        // a->prev = b->prev;
        // a->value = b->value;
        // b->next = buf.next;
        // b->prev = buf.prev;
        // b->value = buf.value;
    }


    void merge(list& other) {
        if(this == &other)
            return;
        auto it1 = begin();
        //auto it2 = other.begin();

        for (size_type i = 0; i < s + other.size(); i++) {
            if(*it1 < other.front()) {
                it1++;
            }
            else {
                //it1++;
                insert(it1, other.front());                
                //it2++;
                //other.pop_front();
            }
        }
        

    };
    //void splice(iterator pos, list& other);
    void remove(const T& value) {};

    void unique() {
        if(first == last || first == nullptr)
            return;        
        node_pointer a = first;
        node_pointer b = a->next;
        if (b == nullptr)
            return;
        //value_type buf = a->value;
        //node_pointer p = nullptr;

        while(a != last || b != nullptr)
        {                
            //buf = a->value;
            if(a->value == b->value){
                a->next = b->next;
                if(a->next != nullptr) 
                    a->next->prev = a;
                if(b == last)
                    pop_back();
                else
                    delete_node(b);
                b = a->next;
                //std::swap(&it1, &it2);
            }    
            else {
                a = a->next;
                b = b->next;
            }
        }
    };

    void reverse() noexcept { 
        //Node buf = Node();
        node_pointer it1 = first;
        node_pointer it2 = last;

        for (size_type i = 0; i < s / 2; i++) {
            swap(it1, it2);
            it1 = it1->next;
            it2 = it2->prev;
        }
        // buf.next = first->next;
        // buf.prev = first->prev;

        // first->next = last->prev;
        // first->prev = last->next;         

    };


    void sort() {
        if(first == last || first == nullptr)
            return;        
        node_pointer a = first;
        node_pointer b = a->next;
        if (b == nullptr)
            return;
        bool unsorted_flag = false;

        // auto it1 = this->begin();
        // auto it2 = ++it1;
        // if (&it2 == nullptr)
        //     return;
        //it2++;
        do {
            //if(*it2 < *it1){
            unsorted_flag = false;
            while(a != last || b != nullptr)
            {                
                if(a->value > b->value){
                    //std::swap(&it1, &it2);
                    list::swap(a, b);
                    unsorted_flag = true;
                }    
                a = a->next;
                b = b->next;

                // it1++;
                // it2++;
                // if (&it2 == nullptr) {
                //     it1 = this->begin();
                //     it2 = ++it1;
                // }
            }
            a = first;
            b = a->next;

            
        }
        while (unsorted_flag);      
    };

    void splice(iterator pos, list& other) {
        auto it = other.begin();
        for (size_type i = 0; i < other.size(); i++) {
            //push_back(it->value);
            //it = it->next;
            insert(pos, *it);
            it++;            
        }    
        
    };





/*
    static_assert (
        std::is_same<typename Allocator::value_type, value_type>::value,
        "Allocator: allocator type must be the same as value_type"
    );
*/
    // Your code goes here?..

private:
    allocator_type _allocator;
    _node_allocator _node_all;
    //decltype(_allocator)::rebind<Node>::other _node_all;
    Node *first;
    Node *last;
    size_type s;

    struct Node {
        Node *prev;
        Node *next;
        value_type value;
        Node() : next(NULL), prev(NULL) {
            value = value_type();
            //value = _traits::allocate(1);
            //_allocator.construct(value, T());;
        };
        Node(const T &x) : next(NULL), prev(NULL) {
            value = value_type(x);
            //value = _traits::allocate(1);
            //_allocator.construct(value, x);
        };
        ~Node() {
            value.~value_type();
            //_allocator.destroy(value);
            //_allocator.deallocate(value, 1);                   
            //_traits::destroy(value);
            //_traits::deallocate(value, 1);            
        }
    };


    

    // Your code goes here...

};



}  // namespace task
