// matrix_rotation.cpp 

#include "stdafx.h"
#include <iostream>
#include <limits> 
using namespace std;

template < typename T>
struct index_normal {
    static T * const index(T *const base, size_t size_r1, size_t index_r1, size_t i) {
        return base + index_r1*size_r1 + i;
        }
    };

template < typename T>
struct index_rot90 {
    static T * const index(T *const base, size_t size_r1, size_t index_r1, size_t i) {
        return base + (size_r1 - 1 - i)*size_r1 + index_r1;
        }
    };

template < typename T>
struct index_rot180 {
    static T * const index(T *const base, size_t size_r1, size_t index_r1, size_t i) {
        return base + (size_r1 - 1 - index_r1)*size_r1 + (size_r1 - 1 - i);
        }
    };

template < typename T>
struct index_rot270 {
    static T * const index(T *const base, size_t size_r1, size_t index_r1, size_t i) {
        return base + i*size_r1 + (size_r1 - 1 - index_r1);
        }
    };

template < typename T>
struct index_transpose {
    static T * const index(T *const base, size_t size_r1, size_t index_r1, size_t i) {
        return base + i*size_r1 + index_r1;
        }
    };

template < typename T, typename IndexPolicy>
class array_proxy{
    class IndexHandler{
        array_proxy &obj;
        size_t index;
    public:
        T& operator[]( size_t j ){
            return *(IndexPolicy::index(obj.m_base,obj.m_size,index,j));
            }
        IndexHandler(array_proxy &object, size_t i )
            : obj(object)
            , index(i) {}
        };
public:
    explicit array_proxy(T *base, size_t size)
        : m_base(base)
        , m_size(size)
        {}
    IndexHandler operator[]( size_t i ) { 
        return IndexHandler(*this,i);
        }
private:
    T *const m_base;
    size_t const m_size;
    };

template <typename T, typename I>
array_proxy<T,I> make_array_proxy(T *base, size_t size)
    {
    return array_proxy<T,I>(base, size);
    };

template <typename T, typename I>
void write_array(array_proxy<T,I>  &ar, size_t size)
    {
    for (size_t i=0; i<size; ++i){
        for (size_t j=0; j<size; ++j){
            ar[i][j] = i*size+j;
            }
        }
    };

template <typename T> char* ElementPrintFormat();
template <> char* ElementPrintFormat<int>() {return "%6d";}
template <> char* ElementPrintFormat<float>() {return "%e ";}

template <typename T, typename I>
void print_array(array_proxy<T,I>  &ar, size_t size)
    {
    for (size_t i=0; i<size; ++i){
        for (size_t j=0; j<size; ++j){
            printf(ElementPrintFormat<T>(), ar[i][j]);
            }
        printf("\n");
        }
    };

enum ERROR{
    ERROR_SIZE_OVERLOAD,
    ERROR_BAD_ALLOC
    };

typedef int element_type;


void DoTest(element_type *data, size_t size) {

    array_proxy<element_type, index_normal<element_type> > arr_normal = make_array_proxy<element_type, index_normal<element_type> >(data, size);
    //printf("Заполнение элементов матрицы\n");
    //write_array<element_type, index_normal<element_type> >( arr_normal, size);
    printf("\nНормальный вид:\n\n");
    print_array<element_type, index_normal<element_type> >( arr_normal, size);

    array_proxy<element_type, index_rot90<element_type> > arr_rot90 = make_array_proxy<element_type, index_rot90<element_type> >(data, size);
    printf("\nПоворот на 90 градусов:\n\n");
    print_array<element_type, index_rot90<element_type> >( arr_rot90, size);

    array_proxy<element_type, index_rot180<element_type> > arr_rot180 = make_array_proxy<element_type, index_rot180<element_type> >(data, size);
    printf("\nПоворот на 180 градусов:\n\n");
    print_array<element_type, index_rot180<element_type> >( arr_rot180, size);

    array_proxy<element_type, index_rot270<element_type> > arr_rot270 = make_array_proxy<element_type, index_rot270<element_type> >(data, size);
    printf("\nПоворот на 270 градусов:\n\n");
    print_array<element_type, index_rot270<element_type> >( arr_rot270, size);

    array_proxy<element_type, index_transpose<element_type> > arr_transpose = make_array_proxy<element_type, index_transpose<element_type> >(data, size);
    printf("\nТранспонирование:\n\n");
    print_array<element_type, index_transpose<element_type> >( arr_transpose, size);
    };

int _tmain(int argc, _TCHAR* argv[])
    {
    setlocale(LC_ALL, "Rus");

    size_t size;
    element_type *ptr_rawdata = NULL;

    while(1) {
        cout << "\n\nВведите размер матрицы NxN (0 - выход): ";
        cin >> size;
        if (size == 0) break;

        try {
            if ( (long long) size*size*sizeof(element_type) > (long long) std::numeric_limits<int>::max()/2) throw ERROR_SIZE_OVERLOAD;

            ptr_rawdata = new element_type[size*size];

            if (!ptr_rawdata) throw ERROR_BAD_ALLOC;
            }
        catch (std::bad_alloc& ) {
            printf("\n error--не удалось выделить память для матрицы размером [%d x %d]\n", size, size);
            //system("pause"); 
            continue;
            }
        catch (ERROR) {
            printf("\n Error--переполнение при формировании размера матрицы [%d x %d]\n", size, size);
            //system("pause"); 
            continue;
            }

        printf("\nЗаполнение массива\n");

        for (size_t i=0; i<size*size; ++i){
            *(ptr_rawdata + i) = i;
            cout << *(ptr_rawdata + i) << "  ";
            }
        cout << endl;

        DoTest(ptr_rawdata, size);

        delete ptr_rawdata;
        ptr_rawdata = 0;
        };

    //system("pause");
    return 0;
    }
