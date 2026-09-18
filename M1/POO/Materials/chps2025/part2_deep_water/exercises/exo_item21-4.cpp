#include <iostream>
#include <utility>

template <typename T, size_t...ints>
void print_tuple(T&& tuple, std::index_sequence<ints...>){
    ((std::cout << std::get<ints>(tuple) << ' '),...);
    std::cout << std::endl;
}

template  <typename...T>
void print_tuple2(std::tuple<T...> const& tuple){
    auto indexes = std::index_sequence_for<T...>();
    print_tuple(tuple,indexes);
}

// or 
template <typename Tuple>
void print_tuple3(Tuple && tuple){
    auto indexes = std::make_index_sequence<std::tuple_size_v<Tuple>>{};
    print_tuple(tuple,indexes);
}

int main(){
    auto tuple = std::make_tuple<int,char,double>(1,'a',0.); 
    print_tuple(tuple, std::make_index_sequence<3>());
    print_tuple2(tuple);

}