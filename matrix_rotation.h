// matrix_rotation.h
#ifndef __MATRIX_ROTATION_H__
#define __MATRIX_ROTATION_H__

namespace matrix_rotation {

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

} //namespace matrix_rotation

#endif	// __MATRIX_ROTATION_H__