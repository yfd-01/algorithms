//
// Created by YFD on 2023/11/18.
//

#ifndef DOUBLE_LINK_LIST_H
#define DOUBLE_LINK_LIST_H

#include <iostream>
#include <memory>
#include <optional>

#include "iterator.hpp"

template <typename _T>
struct node {
    _T v;
    node<_T> *next, *prev;

    node(): next(nullptr), prev(nullptr), v(0) {}
    explicit node(int n): next(nullptr), prev(nullptr), v(n) {}
};

template <class _T>
class double_link_list {
private:
    typedef     node<_T>         _node;

    _node *head, *tail;      // 首尾虚节点
    uint32_t _size;          // 链表长度

public:
    typedef     iterator<_node, _T>     iterator;

public:
    double_link_list(): _size(0) {
        head = new _node();
        tail = new _node();
    }

    double_link_list(std::initializer_list<_T> initList): _size(0) {
        head = new _node();
        tail = new _node();
        _node* walker = head;

        for (auto it = initList.begin(); it != initList.end(); it++) {
            _node* t_node = new _node(*it);
            walker->next = t_node;

            bool mid_flag = true;
            if (it == initList.begin()) {
                t_node->prev = nullptr;
                mid_flag = false;
            }

            if (it == initList.end() - 1) {
                t_node->next = nullptr;
                mid_flag = false;

                if (walker != head) // 禁止构建单个元素时prev指向head
                    t_node->prev = walker;
            }

            if (mid_flag)
                // mid nodes
                t_node->prev = walker;

            walker = walker->next;
            _size++;
        }

        tail->next = walker;
    }

    double_link_list(const double_link_list& dll) = delete;     // 禁止拷贝构造
    // 移动构造
    double_link_list(double_link_list&& dll) noexcept {
        if (dll.head && dll.tail) {
            head = dll.head;
            tail = dll.tail;
            _size = dll._size;
        }
    }

    double_link_list& operator= (const double_link_list& dll) = delete;     // 禁止拷贝赋值
    // 移动赋值 =》 走移动构造

    void show_forward() const {
        _node* t_node = head->next;

        while (t_node) {
            std::cout<< t_node->v<< ' ';
            t_node = t_node->next;
        }
        std::cout<< '\n';
    }

    void show_backward() const {
        _node* t_node = tail->next;

        while (t_node) {
            std::cout<< t_node->v<< ' ';
            t_node = t_node->prev;
        }
        std::cout<< '\n';
    }

    bool insert(uint32_t pos, _T val) {
        if (pos > _size)  return false;

        _node* t_node = new _node(val);

        if (_size == 0) {
            head->next = t_node;
            tail->next = t_node;
            return true;
        }

        _node* walker = head;
        while (pos--) walker = walker->next;

        if (walker == head) {
            _node* fst_node = head->next;

            head->next = t_node;
            t_node->next = fst_node;
            fst_node->prev = t_node;
            t_node->prev = nullptr;
        } else if (walker == tail->next) {
            _node* last_node = tail->next;

            tail->next = t_node;
            last_node->next = t_node;
            t_node->prev = last_node;
            t_node->next = nullptr;
        } else {
            _node* next_node = walker->next;
            walker->next = t_node;
            t_node->prev = walker;

            t_node->next = next_node;
            next_node->prev = t_node;
        }

        _size++;
        return true;
    }

    bool erase(uint32_t pos) {
        if (_size == 0 || pos >= _size)  return false;

        if (_size == 1) {
            delete tail->next;
            head->next = nullptr;
            tail->next = nullptr;

            return true;
        }

        _node* walker = head;
        pos++;
        while (pos--) walker = walker->next;

        if (walker == head->next) {
            _node* next_node = walker->next;
            head->next = next_node;
            next_node->prev = nullptr;
        } else if (walker == tail->next) {
            _node* prev_node = walker->prev;
            tail->next = prev_node;
            prev_node->next = nullptr;
        } else {
            _node* prev_node = walker->prev;
            prev_node->next = walker->next;
            walker->next->prev = prev_node;
        }

        delete walker;
        _size--;

        return true;
    }

    void clear() {
        if (_size == 0) return;

        _node* t_node = head->next;

        while (true) {
            if (t_node->prev)   delete t_node->prev;
            if (t_node->next == nullptr) {
                delete t_node;
                break;
            }

            t_node = t_node->next;
        }

        head->next = nullptr;
        tail->next = nullptr;
        _size = 0;
    }

    uint32_t find(const _T& v) const {

    }

    uint32_t size() const {
        return _size;
    }

    iterator begin() {
        if (head->next)
            return iterator(head->next);

        return {};
    }

    iterator end() {
        return {};
    }

    iterator rbegin() {
        if (tail->next)
            return iterator(tail->next);

        return {};
    }

    iterator rend() {
        return {};
    }
};

#endif // DOUBLE_LINK_LIST_H
