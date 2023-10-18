#define NEUROLIB_IMPLEMENTATION
#include "./src/neurolib.hpp"

int main(int argc, char** argv)
{   
    srand(time(0));
    Matrix a = matrix_alloc(2, 2);
    float data[] = {2.0f, 0.0f, 1.0f, 0.0f};
    matrix_randomize(a, 0, 10);
    Matrix b = {2, 2, data};
    Matrix dst = matrix_alloc(2, 2);

    matrix_print(a);
    matrix_dot(dst, a, b);
    matrix_print(dst);

    return 0;
}