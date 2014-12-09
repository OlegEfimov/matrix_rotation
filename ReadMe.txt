This code was inspired by a question from "CRACKING THE CODING INTERVIEW, FIFTH EDITION" Gayle Laakmann McDowell
/page 73/
1.6 Given an image represented by an NxN matrix, where each pixel in the image is
4 bytes, write a method to rotate the image by 90 degrees. Can you do this in
place?
/Author's solution on page 173/

Class matrix_rotation::array_proxy is not a solution as well as above. (It's just for fun, and to do fingers be quick)

There is also provided a set of index policy classes for raw array for 2d matrix rotation. It implements normal 2d indexing semantics.

Constructor's complexity: Constant

Screenshot of class matrix_rotation::array_proxy test:
>matrix_rotation.exe
Enter matrix size NxN (0 - exit): 4

Filling array by increment data
0  1  2  3  4  5  6  7  8  9  10  11  12  13  14  15
Normal:
     0     1     2     3
     4     5     6     7
     8     9    10    11
    12    13    14    15
Matrix rotated on 90 degrees:
    12     8     4     0
    13     9     5     1
    14    10     6     2
    15    11     7     3
Matrix rotated on 180 degrees:
    15    14    13    12
    11    10     9     8
     7     6     5     4
     3     2     1     0
Matrix rotated on 270 degrees:
     3     7    11    15
     2     6    10    14
     1     5     9    13
     0     4     8    12
Transpose matrix:
     0     4     8    12
     1     5     9    13
     2     6    10    14
     3     7    11    15
Enter matrix size NxN (0 - exit): 0
>