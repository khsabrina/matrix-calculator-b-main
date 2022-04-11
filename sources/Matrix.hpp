#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cstdlib>
using namespace std;

namespace zich{
    class Matrix{
        public:
            int row;
            int col;
            vector<double> matrix;
            Matrix();
            Matrix(vector<double> const &m, int r, int c);
            Matrix(Matrix &m);
            Matrix operator+(Matrix const &m) const;
            Matrix operator+() const;
            void operator+=(Matrix const &m);
            Matrix operator-(Matrix const &m);
            Matrix operator-();
            void operator-=(Matrix const &m);
            bool operator==(Matrix const &m) const;
            bool operator>=(Matrix const &m) const;
            bool operator<=(Matrix const &m) const;
            bool operator!=(Matrix const &m) const;
            bool operator>(Matrix const &m) const;
            bool operator<(Matrix const &m) const;
            //postfix increment
            Matrix operator++(int);
            //Prefix Increment
            Matrix operator++();
            //postfix increment
            Matrix operator--(int);
            //Prefix Increment
            Matrix operator--();
            friend Matrix operator*(double,Matrix const &m);
            friend Matrix operator*(Matrix const &m,double);
            Matrix operator*(Matrix const &m) const;
            friend void operator*=(double,Matrix&);
            friend void operator*=(Matrix&,double);
            void operator*=(Matrix const &m);
            friend ostream& operator<< (ostream& output,Matrix const &m);
            friend istream & operator >> (istream &input,  Matrix &m);
            static vector<double> move_to_arr(vector<vector<double>> m, int row, int col);
            static vector<vector<double>> move_to_matrix(vector<double> m, int row, int col);
            



    };
}