#include "doctest.h"
#include <iostream>
#include "Matrix.hpp"
#include <sstream>
#include <stdexcept>
using namespace std;
using namespace zich;

TEST_CASE("bad initialization"){
    vector<double> v = {1,2,3,1,2,3,1,2,3};
    CHECK_THROWS(Matrix a(v,3,2));
    CHECK_THROWS(Matrix b(v,-3,3));
    CHECK_THROWS(Matrix c(v,3,-3)); 
}

TEST_CASE("good comparision tests"){
    vector<double> v = {1,2,3,1,2,3,1,2,3};
    Matrix mat(v,3,3);
    CHECK(mat==mat);
    Matrix mat2 = +mat;
    mat--;
    CHECK(mat<mat2);
    CHECK_FALSE(mat>=mat2);
    CHECK_FALSE(mat>mat2);
    CHECK(mat2>mat);
    CHECK_FALSE(mat!=mat);
    CHECK(mat<=mat2);
}

TEST_CASE("bad comparison test"){
    vector<double> v = {1,2,3,1,2,3,1,2,3};
    CHECK_THROWS(Matrix a(v,3,2));
    Matrix a(v,3,3);
    vector<double> v1 = {1,2,3,1,2,3};
    Matrix b(v1,2,3);  
    CHECK_THROWS(if(a==b){});
    CHECK_THROWS(if(a<b){});
    CHECK_THROWS(if(a<=b){});
    CHECK_THROWS(if(a>=b){});
    CHECK_THROWS(if(a>b){});
    CHECK_THROWS(if(a!=b){});
}
/*
Testing all addition and subtraction operators.
*/
TEST_CASE("Good addition and subtraction tests"){
    vector<double> m1 = {1,2,2,1,1,1,2,1};
    Matrix mat1(m1,4,2);
    vector<double> m2 = {1,3,4,5,6,7,8,8};
    Matrix mat2(m2,4,2);
    Matrix sum = mat1+mat2;
    vector<double> check = {2,5,6,6,7,8,10,9};
    Matrix mcheck(check,4,2);
    CHECK(mcheck==sum);

    for(size_t i=0;i<check.size();i++){
        check[i]++;
    }
    sum++;
    CHECK(Matrix(check,4,2)==sum);
    sum--;
    CHECK(mcheck==sum);
    ++sum;
    CHECK(Matrix(check,4,2)==sum);
    --sum;
    CHECK(mcheck==sum);
    vector<double> one = {1,1,1,1,1,1,1,1};
    Matrix onemat(one,4,2);
    sum+=onemat;
    CHECK(Matrix(check,4,2)==sum);
    sum-=onemat;
    CHECK(mcheck==sum);
    sum+=onemat;
    Matrix y = sum-onemat;
    CHECK(y==mcheck);
    CHECK(y==+y);
}

TEST_CASE("Bad addition and subtraction tests"){
    vector<double> v = {1,2,3,1,2,3,1,2,3};
    CHECK_THROWS(Matrix a(v,3,2));
    Matrix a(v,3,3);
    vector<double> v1 = {1,2,3,1,2,3};
    Matrix b(v1,2,3);
    CHECK_THROWS(Matrix c = a + b);
    CHECK_THROWS(Matrix c = a - b);
    CHECK_THROWS(a+=b);
    CHECK_THROWS(a-=b);
}

TEST_CASE("Good multiplication tests"){
    vector<double> vec = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    Matrix ID(vec,4,4);
    vector<double> m1 = {1,2,2,1,1,1,2,1};
    Matrix mat1(m1,2,4);
    Matrix mat2(m1,4,2);
    /**
     * CHECK if mult by identity matrix results in the same matrix.
     * 
     */
    CHECK(mat1==mat1*ID);
    CHECK(mat2==ID*mat2);
    /**
     * @brief GUASSIAN ELIMINATION USING ELEMENTARY MATRIX MULTIPLICATION. E3*E2*E1*A=U
     * 
     * A = [2 3 5]
     *     [4 5 6]
     *     [2 4 4]
     * 
     * 
     * U = [2 3 5]
     *     [0 -1 4]
     *     [0 0 -5]
     * 
     */
    vector<double> ansvec = {2,3,5,0,-1,-4,0,0,-5};
    Matrix U(ansvec,3,3);
    vector<double> Avec = {2,3,5,4,5,6,2,4,4};
    Matrix A(Avec,3,3);
    vector<double> E1vec = {1,0,0,-2,1,0,0,0,1};
    Matrix E1(E1vec,3,3);
    vector<double> E2vec = {1,0,0,0,1,0,-1,0,1};
    Matrix E2(E2vec,3,3);
    vector<double> E3vec = {1,0,0,0,1,0,0,1,1};
    Matrix E3(E3vec,3,3);
    CHECK(E3*E2*E1*A==U);
    /*
    Scalar multiplication.
    */
    vector<double> three_id = {3,0,0,0,0,3,0,0,0,0,3,0,0,0,0,3};
    Matrix three_ID(three_id,4,4);
    const double three = 3;
    const double third =(1.0/3.0);
    CHECK(three_ID==three*ID);
    CHECK(three_ID*third==ID);
    three_ID*=third;
    CHECK(three_ID==ID);
}
/*
Testing mult on non defined matrix mult (m1!=n2);
*/
TEST_CASE("Bad multipliacation tests"){
      vector<double> m1 = {1,2,2,1,1,1,2,1};
    Matrix mat1(m1,2,4);
    Matrix mat2(m1,1,8);
    CHECK_THROWS(mat1*mat2);
    CHECK_THROWS(mat2*mat1);
}
/*
Testing input and output functions.
*/
TEST_CASE("input and output test"){
    istringstream sinput("[1 2], [2 1], [1 1], [2 1]");
    Matrix x;
    sinput>>x;
    vector<double> comp = {1,2,2,1,1,1,2,1};
    Matrix compare(comp,4,2);
    CHECK(compare==x);
    ostringstream soutput;
    soutput << x;
    CHECK(soutput.str()=="[1 2]\n"
                         "[2 1]\n"
                         "[1 1]\n"
                         "[2 1]\n"); 
    istringstream sinput2("[1 2 2 1], [1 1 2 1]");
    Matrix cmp2(comp,2,4);
    Matrix y;
    sinput2>>y;
    CHECK(cmp2==y);
    ostringstream soutput2;
    soutput2<<y;
    CHECK(soutput2.str()=="[1 2 2 1]\n"
                          "[1 1 2 1]\n");

}
/*
Check assingment after changing original matricies demensions.
*/
TEST_CASE("mult"){
    vector<double> v = {1,2,3,4,1,2,3,4};
    Matrix A(v,4,2);
    Matrix B(v,2,4);
    CHECK_NOTHROW(A=A*B);
    CHECK_THROWS(A*=B);
    
    
}