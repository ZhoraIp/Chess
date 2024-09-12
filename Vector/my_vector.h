#ifndef CHESS_VECTOR_H
#define CHESS_VECTOR_H
#include <iostream>


template<typename T> class Vector{
private:
    T *arr = nullptr;
    size_t sz = 0; // размер
    size_t cap = 0; // выдел память
public:
    Vector(){
        sz = 0;
        cap = 0;
        arr = nullptr;
    };

    explicit Vector(int s){
        resize(s);
        sz = s;
        cap = s;
    };

    explicit Vector(int s, const T& value){
        resize(s, value);
        sz = s;
        cap = s;
    };

    Vector(const Vector<T> &value){
        resize(value.size());
        reserve(value.size());
        for(size_t i = 0; i < value.size(); ++i) {
            new(arr+i) T(value[i]);
        }
        sz = value.size();
        cap = value.size();
    };

    Vector(std::initializer_list<T> list){
        reserve(list.size());
        size_t i = 0;
        for(const T* ptr = list.begin(); ptr != list.end(); ++ptr, ++i) {
            if(ptr == nullptr) {}
            else new(arr+i) T(*ptr);
        }
        sz = list.size();
        cap = list.size();
    }

    Vector(std::initializer_list<std::initializer_list<T>> list){
        Vector<T> *newarr;
        newarr = reinterpret_cast<Vector<T>*>(new uint8_t[list.size() * sizeof(Vector<T>)]);
//        T* newarr = reinterpret_cast<T*>(new uint8_t[n * sizeof(T)]);
//        newarr.arr = new Vector<T>[list.size()];
//        newarr->sz = list.size();
//        newarr->cap = list.size();
        int k = 0;
        for(auto i = list.begin(); i != list.end(); ++i){
            for(int j = 0; j < i->size(); ++j){
                new (newarr + j) Vector<T>(i);
            }
            newarr[k].sz = i->size();
            newarr[k].cap = i->size();
            k++;
        }
        sz = list.size();
        cap = list.size();
        arr = newarr;
    }

    size_t size() const{
        return sz;
    }
    size_t capacity() const{
        return cap;
    }

    void reserve(size_t n){
        if(n <= cap) return;
        T* newarr = reinterpret_cast<T*>(new uint8_t[n * sizeof(T)]);
        //T* newarr = new T[n];
        for(size_t i = 0; i < sz; ++i){
            new (newarr + i) T(arr[i]); //placement new
            //newarr[i] = arr[i];
        }
        for(size_t i = 0; i < sz; ++i) {
            (arr + i)->~T();
        }
        delete[] reinterpret_cast<uint8_t*>(arr);
        arr = newarr;
        cap = n;
    }

    void resize(size_t n, const T& value = T()){
        if(n > cap) reserve(n);
        for(size_t i = sz; i < n; ++i) {
            new(arr+i) T(value);
        }
        if(n < sz){
            sz = n;
        }
    }

    void push_back(const T& value){
        if(cap == 0) reserve(10);
        if(cap == sz) {
            reserve(2 * sz);
        }
        new (arr+sz) T(value);
        //arr[sz] = value
        ++sz;
    }

    void pop_back() {
        --sz;
        (arr+sz)->~T();
    }

    ~Vector() {
        for(size_t i = 0; i < sz; ++i) {
            (arr + i)->~T();
        }
        delete[] reinterpret_cast<uint8_t*>(arr);
    }

    T& operator[] (int ind){
        return arr[ind];
    }
    const T& operator[](int ind) const{
        return arr[ind];
    }

    Vector<T>& operator=(Vector<T>& arg){
        if(&arg == this) return *this;
        if(arg.size() <= cap){
            for(int i = 0; i < arg.size(); i++){
                arr[i] = arg[i];
                sz = arg.size();
            }
            return *this;
        }

        T* newarr = reinterpret_cast<T*>(new uint8_t[arg.size() * sizeof(T)]);
        for(size_t i = 0; i < arg.size(); ++i){
            new (newarr + i) T(arg[i]);
        }

        for(int i = 0; i < sz; ++i) {
            (arr + i)->~T();
        }
        delete[] reinterpret_cast<uint8_t*>(arr);

        sz = arg.size();
        cap = arg.capacity();
        arr = newarr;
        return *this;
    }

    class iterator{
    private:
        T* it;
    public:

        T* getIt() const{
            return this->it;
        }

        explicit iterator(T* p){
            it = p;
        }

        iterator& operator++() {
            it++;
            return *this;
        }

        iterator& operator--() {
            it--;
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --*this;
            return tmp;
        }

        T& operator*() {
            return *it;
        }



//        iterator& operator+=(int n) {
//            it+=n;
//            return *this;
//        }
//
//        iterator& operator-=(int n) {
//            it-=n;
//            return *this;
//        }

        bool operator==(const iterator& b) const {
            return it == b.getIt();
        }

        bool operator!=(const iterator& b) const {
            return it != b.getIt();
        }
    };

    iterator begin(){
        return iterator(&arr[0]);
    }

    iterator end(){
        return Vector<T>::iterator(&arr[sz]);
    };

//    void erase(const Vector<T>::iterator &it){
//        T* newarr = reinterpret_cast<T*>(new uint8_t[sz-1 * sizeof(T)]);
//        int j = 0;
//        for(auto i = begin(); i != end(); ++i){
//            if(i == it) break;
//            new (newarr + j) T(arr[j]);
//            j++;
//        }
//        for(int i = j+1; j < sz; ++i){
//            new (newarr + i-1) T(arr[i]);
//        }
//
//        for(int i = 0; i < sz; ++i) {
//            (arr + i)->~T();
//        }
//        delete[] reinterpret_cast<uint8_t*>(arr);
//
//        sz = sz-1;
//        arr = newarr;
//        //return *this;
//    }

    bool empty() const {
        return (sz == 0);
    };

};



#endif
