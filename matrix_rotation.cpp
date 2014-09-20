// matrix_rotation.cpp 

#include "stdafx.h"
#include <iostream>
#include <limits> 
using namespace std;

template < typename T>
struct index_normal {
    enum { resized = false };
    static T * const index(
        T *const base
        , size_t row_new
        , size_t col_new
        , size_t row_orig
        , size_t col_orig
        , size_t index_new
        , size_t j_new
        ) {
            return base + index_new*col_orig + j_new;
        }
    };

template < typename T>
struct index_rot90 {
    enum { resized = true };

    static T * const index(
        T *const base
        , size_t row_new
        , size_t col_new
        , size_t row_orig
        , size_t col_orig
        , size_t index_new
        , size_t j_new
        ) {
            int i_orig = (index_new*col_new + j_new)/row_orig;
            int j_orig = (index_new*col_new + j_new)%row_orig;
            int j_rot90 = i_orig;
            int i_rot90 = row_orig - 1 - j_orig;
            int row_index = col_orig*i_rot90 + j_rot90;
            return base + row_index;
        }
    };

template < typename T>
struct index_rot180 {
    enum { resized = false };
    static T * const index(
        T *const base
        , size_t row_new
        , size_t col_new
        , size_t row_orig
        , size_t col_orig
        , size_t index_new
        , size_t j_new
        ) {
            int row_index = (row_orig - 1 - index_new)*col_orig + (col_orig - 1 - j_new);
            return base + row_index;
        }
    };

template < typename T>
struct index_rot270 {
    enum { resized = true };
    static T * const index(
        T *const base
        , size_t row_new
        , size_t col_new
        , size_t row_orig
        , size_t col_orig
        , size_t index_new
        , size_t j_new
        ) {
            int i_orig = (index_new*col_new + j_new)/row_orig;
            int j_orig = (index_new*col_new + j_new)%row_orig;
            int i_rot270 = j_orig;
            int j_rot270 = col_orig - 1 - i_orig;
            int row_index = col_orig*i_rot270 + j_rot270;
            return base + row_index;
        }
    };

template < typename T>
struct index_transpose {
    enum { resized = true };
    static T * const index(
        T *const base
        , size_t row_new
        , size_t col_new
        , size_t row_orig
        , size_t col_orig
        , size_t index_new
        , size_t j_new
        ) {
            int row_index = col_orig*j_new + index_new;
            return base + row_index;
        }
    };

template < typename T, typename IndexPolicy>
class array_proxy{
public:
    class IndexHandler{
        array_proxy &obj;
        size_t index_new;
    public:
        T& operator[]( size_t j_new ){
            return *(
                IndexPolicy::index(
                obj.m_base
                , obj.m_row_new
                , obj.m_col_new
                , obj.m_row_orig
                , obj.m_col_orig
                , index_new
                , j_new)
                );
            }
        IndexHandler(array_proxy &object, size_t i )
            : obj(object)
            , index_new(i) {}
        };

    explicit array_proxy(T *base, size_t row, size_t col)
        : m_base(base)
        , m_row_new(col)
        , m_col_new(row)
        , m_row_orig(row)
        , m_col_orig(col)
        {
        }

    T *const m_base;
    size_t const m_row_new;
    size_t const m_col_new;
    size_t const m_row_orig;
    size_t const m_col_orig;

    IndexHandler operator[]( size_t i ) { 
        return IndexHandler(*this,i);
        }
    array_proxy &operator = (array_proxy const &);
    };

template <typename T, typename I>
array_proxy<T,I> make_array_proxy(T *base, size_t row, size_t col)
    {
    return array_proxy<T,I>(base, row, col);
    };

template <typename T, typename I>
void write_array(array_proxy<T,I>  &ar)
    {
    for (size_t i=0; i<ar.m_row; ++i){
        for (size_t j=0; j<ar.m_col; ++j){
            ar[i][j] = i*ar.m_col+j;
            }
        }
    };

template <typename T> char* ElementPrintFormat();
template <> char* ElementPrintFormat<int>() {return "%6d";}
template <> char* ElementPrintFormat<float>() {return "%e ";}

template <typename T, typename IndexPolicy>
void print_array(array_proxy<T,IndexPolicy>  &ar)
    {
    for (size_t i=0; i<(IndexPolicy::resized ? ar.m_row_new:ar.m_row_orig); ++i){
        for (size_t j=0; j<(IndexPolicy::resized ? ar.m_col_new:ar.m_col_orig); ++j){
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


void DoTest(element_type *data, size_t size_row, size_t size_col) {

    array_proxy<element_type, index_normal<element_type> > arr_normal = make_array_proxy<element_type, index_normal<element_type> >(data, size_row, size_col);
    //printf("Заполнение элементов матрицы\n");
    //write_array<element_type, index_normal<element_type> >( arr_normal);
    printf("\nНормальный вид:\n\n");
    print_array<element_type, index_normal<element_type> >( arr_normal);

    array_proxy<element_type, index_rot90<element_type> > arr_rot90 = make_array_proxy<element_type, index_rot90<element_type> >(data, size_row, size_col);
    printf("\nПоворот на 90 градусов:\n\n");
    print_array<element_type, index_rot90<element_type> >( arr_rot90);

    array_proxy<element_type, index_rot180<element_type> > arr_rot180 = make_array_proxy<element_type, index_rot180<element_type> >(data, size_row, size_col);
    printf("\nПоворот на 180 градусов:\n\n");
    print_array<element_type, index_rot180<element_type> >( arr_rot180);

    array_proxy<element_type, index_rot270<element_type> > arr_rot270 = make_array_proxy<element_type, index_rot270<element_type> >(data, size_row, size_col);
    printf("\nПоворот на 270 градусов:\n\n");
    print_array<element_type, index_rot270<element_type> >( arr_rot270);

    array_proxy<element_type, index_transpose<element_type> > arr_transpose = make_array_proxy<element_type, index_transpose<element_type> >(data, size_row, size_col);
    printf("\nТранспонирование:\n\n");
    print_array<element_type, index_transpose<element_type> >( arr_transpose);
    };

int _tmain(int argc, _TCHAR* argv[])
    {
    setlocale(LC_ALL, "Rus");

    size_t size_row;
    size_t size_col;
    element_type *ptr_rawdata = NULL;

    while(1) {
        cout << "\n\nВведите количество строк матрицы (0 - выход): ";
        cin >> size_row;
        if (size_row == 0) break;
        cout << "\nВведите количество колонок матрицы (0 - выход): ";
        cin >> size_col;
        if (size_col == 0) break;

        try {
            if ( (long long) size_row*size_col*sizeof(element_type) > (long long) std::numeric_limits<int>::max()/2) throw ERROR_SIZE_OVERLOAD;

            ptr_rawdata = new element_type[size_row*size_col];

            if (!ptr_rawdata) throw ERROR_BAD_ALLOC;
            }
        catch (std::bad_alloc& ) {
            printf("\n error--не удалось выделить память для матрицы размером [%d x %d]\n", size_row, size_col);
            //system("pause"); 
            continue;
            }
        catch (ERROR) {
            printf("\n Error--переполнение при формировании размера матрицы [%d x %d]\n", size_row, size_col);
            //system("pause"); 
            continue;
            }

        printf("\nЗаполнение массива\n");

        for (size_t i=0; i<size_row*size_col; ++i){
            *(ptr_rawdata + i) = i;
            cout << *(ptr_rawdata + i) << "  ";
            }
        cout << endl;

        DoTest(ptr_rawdata, size_row, size_col);

        delete ptr_rawdata;
        ptr_rawdata = 0;
        };

    //system("pause");
    return 0;
    }
