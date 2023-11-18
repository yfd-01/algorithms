#include "ds/double_link_list.hpp"
#include <vector>

int main() {
    double_link_list<int> list = {10, -1, 20, 99, 100};
    list.show_forward();
    list.show_backward();

    list.insert(0, 66);
    list.insert(3, -20);
    list.show_forward();

    list.erase(0);
    list.show_forward();

    list.erase(list.size() - 1);
    list.show_backward();

//    list.clear();
//    list.show_forward();

    *list.begin() = 9999;
    *(list.begin() + 4 - 2) = -9999;
    list.show_forward();

    auto it1 = list.begin();
    auto it2 = list.rbegin() - 1;

    std::cout<< it2 - it1<< std::endl;
    *((list.rbegin() - 2)++) = -77;
    list.show_forward();

    std::cout<< "print all elems by iterator\n";
    for (double_link_list<int>::iterator it = list.begin(); it != list.end(); it++) {
        std::cout<< *it<< ' ';
    }
    std::cout<< '\n';

    std::cout<< "print all elems by rIterator\n";
    for (double_link_list<int>::iterator it = list.rbegin(); it != list.rend(); it--) {
        std::cout<< *it<< ' ';
    }

    return 0;
}