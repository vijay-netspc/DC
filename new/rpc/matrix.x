const SIZE=10;
typedef int row[SIZE];
typedef row mat[SIZE];
struct input{
        int r1;
        int c1;
        int r2;
        int c2;
        mat a;
        mat b;
};
struct output{
        mat c;
};
program MATRIX_PROG{
        version MATRIX_VERS{
                output matrix(input)=1;
        }=1;
}=0x12345678;
