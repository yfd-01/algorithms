//
// Created by YFD on 2023/11/18.
//

#ifndef ITERATOR_H
#define ITERATOR_H

template <class _NT, class value_type>
class iterator {
private:
    _NT* _ptr;

public:
    iterator(): _ptr(nullptr) {}
    explicit iterator(_NT& v): _ptr(&v) {}
    explicit iterator(_NT* ptr): _ptr(ptr) {}

    iterator operator++ () {
        if (_ptr->next)
            _ptr = _ptr->next;
        else _ptr = nullptr;

        return *this;
    }

    iterator operator++ (int) {
        iterator it = *this;
        ++*this;

        return it;
    }

    iterator operator-- () {
        if (_ptr->prev)
            _ptr = _ptr->prev;
        else _ptr = nullptr;

        return *this;
    }

    iterator operator-- (int) {
        iterator it = *this;
        --*this;

        return it;
    }

    value_type& operator* () const {
        return _ptr->v;
    }

    value_type* operator-> () const {
        return &_ptr->v;
    }

    iterator operator+ (const iterator&) = delete;
    size_t operator- (const iterator& it) {
        if (_ptr == it._ptr)    return 0;

        size_t _range = 0;

        // forward && backward search
        _NT *fn, *bn;
        fn = bn = _ptr;
        while (fn || bn) {
            if (fn) fn = fn->next;
            if (bn) bn = bn->prev;
            _range++;

            if (fn == it._ptr)  return -_range;
            else if (bn == it._ptr) return _range;
        }

        return INT64_MIN;
    }

    iterator operator+ (const int& i) {
        iterator it = *this;

        for (int u = 0; u < i; u++)
            if (it._ptr)
                it._ptr = it._ptr->next;

        return it;
    }

    iterator operator- (const int& i) {
        iterator it = *this;

        for (int u = 0; u < i; u++)
            if (it._ptr)
                it._ptr = it._ptr->prev;

        return it;
    }

    bool operator== (const iterator& it) {
        return _ptr == it._ptr;
    }

    bool operator!= (const iterator& it) {
        return _ptr != it._ptr;
    }
};

#endif //ITERATOR_H
