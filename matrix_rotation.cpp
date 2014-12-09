// matrix_rotation.cpp 

#include "stdafx.h"
#include <iostream>
#include <limits> 
#include <type_traits>

#include "matrix_rotation.h"

namespace matrix_rotation_test {

    typedef int element_type;
    enum TEST_ERROR{
        TEST_ERROR_SIZE_OVERLOAD,
        TEST_ERROR_BAD_ALLOC
        };

    using namespace matrix_rotation;

    void DoTest(element_type *data, size_t size) {

        array_proxy<element_type, index_normal<element_type> > arr_normal = make_array_proxy<element_type, index_normal<element_type> >(data, size);
        printf("\nNormal:\n\n");
        print_array<element_type, index_normal<element_type> >( arr_normal, size);

        // uncomment to test write_array 
        //printf("Filling matrix by increment data\n");
        //write_array<element_type, index_normal<element_type> >( arr_normal, size);
        //printf("\nNormal filled through proxy indexes:\n\n");
        //print_array<element_type, index_normal<element_type> >( arr_normal, size);

        array_proxy<element_type, index_rot90<element_type> >  arr_rot90  = make_array_proxy<element_type, index_rot90<element_type> >(data, size);
        array_proxy<element_type, index_rot180<element_type> > arr_rot180 = make_array_proxy<element_type, index_rot180<element_type> >(data, size);
        array_proxy<element_type, index_rot270<element_type> > arr_rot270 = make_array_proxy<element_type, index_rot270<element_type> >(data, size);
        array_proxy<element_type, index_transpose<element_type> > arr_transpose = make_array_proxy<element_type, index_transpose<element_type> >(data, size);

        printf("\nMatrix rotated on 90 degrees:\n\n");
        print_array<element_type, index_rot90<element_type> >( arr_rot90, size);

        printf("\nMatrix rotated on 180 degrees:\n\n");
        print_array<element_type, index_rot180<element_type> >( arr_rot180, size);

        printf("\nMatrix rotated on 270 degrees:\n\n");
        print_array<element_type, index_rot270<element_type> >( arr_rot270, size);

        printf("\nTranspose matrix:\n\n");
        print_array<element_type, index_transpose<element_type> >( arr_transpose, size);
        };

    } //namespace matrix_rotation_test

namespace rottest = matrix_rotation_test;

int _tmain(int argc, _TCHAR* argv[])
    {

#if defined(_MSC_VER)
#	if (_MSC_VER >= 1700)
    //check element_type as POD type
    static_assert(std::is_pod<rottest::element_type>::value); // since c++11
#	endif
#endif

    size_t size;
    rottest::element_type *ptr_rawdata = NULL;

    while(1) {
        std::cout << "\n\nEnter matrix size NxN (0 - exit): ";
        std::cin >> size;
        if (size == 0) break;

        try {
            if ( (long long) size*size*sizeof(rottest::element_type) > (long long) std::numeric_limits<int>::max()/2) throw rottest::TEST_ERROR_SIZE_OVERLOAD;

            ptr_rawdata = new rottest::element_type[size*size];

            if (!ptr_rawdata) throw rottest::TEST_ERROR_BAD_ALLOC;
            }
        catch (std::bad_alloc& ) {
            printf("\n error--bad memory allocation for array [%d x %d]\n", size, size);
            continue;
            }
        catch (rottest::TEST_ERROR) {
            printf("\n Error-- can not create array [%d x %d]\n", size, size);
            continue;
            }

        printf("\nFilling array by increment data\n");

        for (size_t i=0; i<size*size; ++i){
            *(ptr_rawdata + i) = i;
            std::cout << *(ptr_rawdata + i) << "  ";
            }
        std::cout << std::endl;

        rottest::DoTest(ptr_rawdata, size);

        delete ptr_rawdata;
        ptr_rawdata = 0;
        };

    return 0;
    }
