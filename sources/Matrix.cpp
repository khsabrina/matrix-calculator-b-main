#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
#include <cstdlib>
#include <string>
using namespace std;
#include "Matrix.hpp"

namespace zich{
    Matrix::Matrix(vector<double> const &m, int r, int c){
        if(r<=0 || c<=0 || c*r != m.size()){
            throw invalid_argument{"Can't do this shit"};
        }
        this->matrix = m;
        this->row =r;
        this->col =c;
    }
    Matrix::Matrix(Matrix &m){
        this->matrix = m.matrix;
        this->row =m.row;
        this->col =m.col;
    }

    // Matrix::Matrix(){
    //     this->row=0;
    //     this->col=0;
    //     this->matrix = NULL;
    // }
    Matrix Matrix::operator+(Matrix const &m) const{
        if(this->row != m.row || this->col != m.col){
            throw invalid_argument{"Can't do this shit"};
        }
        vector<double> mat((size_t)(this->col*this->row));
        for(int i= 0 ;i<this->col*this->row; i++){
           mat[(unsigned int)i] = this->matrix[(unsigned int)i] + m.matrix[(unsigned int)i]; 
        }
        return Matrix{mat,this->row,this->col};
    }
    Matrix Matrix::operator+() const{
        return Matrix{this->matrix ,this->row ,this->col};  
    }
    void Matrix::operator+=(Matrix const &m){
        if(this->row != m.row || this->col != m.col){
            throw invalid_argument{"Can't do this shit"};
        }
        for(int i= 0 ;i<m.matrix.size(); i++){
            this->matrix[(unsigned int)i] = this->matrix[(unsigned int)i] +m.matrix[(unsigned int)i]; 
        }
    }
    Matrix Matrix::operator-(Matrix const &m){
        if(this->row != m.row || this->col != m.col){
            throw invalid_argument{"Can't do this shit"};
        }
        vector<double> mat((size_t)(this->col*this->row));
        for(int i= 0 ;i<this->col*this->row; i++){
           mat[(unsigned int)i] = this->matrix[(unsigned int)i] - m.matrix[(unsigned int)i]; 
        }
        return Matrix{mat,this->row,this->col};
    }
    Matrix Matrix::operator-(){
        vector<double> m((size_t)(this->col*this->row));
        for(int i= 0 ;i<this->col*this->row; i++){
           m[(unsigned int)i] = matrix[(unsigned int)i]*(-1); 
        }
        return Matrix{m,row,col};  
    }
    void Matrix::operator-=(Matrix const &m){
        if(this->row != m.row || this->col != m.col){
            throw invalid_argument{"Can't do this shit"};
        }
        for(int i= 0 ;i<this->col*this->row; i++){
            this->matrix[(unsigned int)i] = this->matrix[(unsigned int)i] -m.matrix[(unsigned int)i]; 
        }
    }
    bool Matrix::operator==(Matrix const &m) const{
        if(this->row != m.row ||this->col != m.col){
            throw invalid_argument{"Can't do this shit"};
        }
        for(int i= 0 ;i<this->matrix.size(); i++){
            if (this->matrix[(unsigned int)i] != m.matrix[(unsigned int)i]){
                return false;
            } 
        }
        return true;
    }
    bool Matrix::operator>=(Matrix const &m) const{
        return *this >m || *this ==m;
    }
    bool Matrix::operator<=(Matrix const &m) const {
        return *this <m || *this ==m;
    }
    bool Matrix::operator!=(Matrix const &m) const{
        return !(*this == m);
    }
    bool Matrix::operator>(Matrix const &m) const{
        if(this->row != m.row || this->col != m.col){
            throw invalid_argument{"Can't do this shit"};
        }
        double sum_matrix1=0;
        double sum_matrix2=0;
        for(int i= 0 ;i<this->matrix.size(); i++){
            sum_matrix1 = this->matrix[(unsigned int)i] + sum_matrix1;
            sum_matrix2 = m.matrix[(unsigned int)i] + sum_matrix2;
        }
        return (sum_matrix1 > sum_matrix2);

    }
    bool Matrix::operator<(Matrix const &m) const{
        if(this->row != m.row || this->col != m.col){
            throw invalid_argument{"Can't do this shit"};
        }
        double sum_matrix1=0;
        double sum_matrix2=0;
        for(int i= 0 ;i<this->matrix.size(); i++){
            sum_matrix1 = this->matrix[(unsigned int)i] + sum_matrix1;
            sum_matrix2 = m.matrix[(unsigned int)i] + sum_matrix2;
        }
        return (sum_matrix1 < sum_matrix2);

    }
    //postfix increment
    Matrix Matrix::operator++(int n){
        Matrix temp(*this);
        for(int i= 0 ;i<this->matrix.size(); i++){
          this->matrix[(unsigned int)i]++; 
        }
        return temp;
    }
    //Prefix Increment
    Matrix Matrix::operator++(){
        for(int i= 0 ;i<this->matrix.size(); i++){
          this->matrix[(unsigned int)i]++; 
        }
        return *this;
    }
    //postfix increment
    Matrix Matrix::operator--(int){
        Matrix temp(*this);
        for(int i= 0 ;i<this->matrix.size(); i++){
          this->matrix[(unsigned int)i]--; 
        }
        return temp;
    }
    //Prefix Increment
    Matrix Matrix::operator--(){
        for(int i= 0 ;i<this->matrix.size(); i++){
          this->matrix[(unsigned int)i]--; 
        }
        return *this;
    }
    Matrix operator*(double num ,Matrix const &m){
        vector<double> mat((size_t)(m.col*m.row));
        for(int i=0; i<(m.col*m.row);i++){
            mat[(unsigned int)i] = m.matrix[(unsigned int)i]*num;
        }
        return Matrix{mat,m.row,m.col};
    }
    Matrix operator*(Matrix const &m,double num){
        vector<double> mat((size_t)(m.col*m.row));
        for(int i=0; i<m.col*m.row;i++){
            mat[(unsigned int)i] = m.matrix[(unsigned int)i]*num;
        }
        return Matrix{mat,m.row,m.col};
    }
    vector<vector<double>> Matrix::move_to_matrix(vector<double> m, int row, int col){
        vector<vector<double>> mat;
        mat.resize((uint)row);
        for(size_t i =0;i<row;i++){
            mat[i].resize((uint)col);
        }
        int index =0;
        for(int i= 0; i<row; i++){
            for(int j=0; j<col; j++){
                mat[(unsigned int)i][(unsigned int)j]= m[(unsigned int)index];
                index++;
            }
        }
        return mat;
    }
    vector<double> Matrix::move_to_arr(vector<vector<double>> m, int row, int col){
        vector<double> mat((size_t)(col*row));
        int index =0;
        for(int i= 0; i<row; i++){
            for(int j=0; j<col; j++){
                mat[(unsigned int)index]= m[(unsigned int)i][(unsigned int)j];
                index++;
            }
        }
        return mat;
    }
    Matrix Matrix::operator*(Matrix const &m) const{
        if(this->col != m.row){
            throw invalid_argument{"Can't do this shit"};
        }
        vector<vector<double>> mat1=move_to_matrix(this->matrix,this->row,this->col);
        vector<vector<double>> mat2=move_to_matrix(m.matrix,m.row,m.col);
        vector<vector<double>> result_mat;
        result_mat.resize((uint)this->row);
        for(size_t i =0;i<this->row;i++){
            result_mat[i].resize((uint)m.col);
        }
        for(int i = 0; i < this->row; ++i){
            for(int j = 0; j < m.col; ++j){
                for(int k = 0; k < this->col; ++k)
                {
                    result_mat[(unsigned int)i][(unsigned int)j] += mat1[(unsigned int)i][(unsigned int)k] * mat2[(unsigned int)k][(unsigned int)j];
                }
            }
        }
        vector<double> ans_mat = move_to_arr(result_mat,this->row,m.col);
        return Matrix{ans_mat,this->row,m.col};

    }
    void operator*=(double num,Matrix& m){
        for(int i=0; i<m.matrix.size();i++){
            m.matrix[(unsigned int)i] = m.matrix[(unsigned int)i]*num;
        }
    }
    void operator*=(Matrix& m,double num){
        for(int i=0; i<m.matrix.size();i++){
            m.matrix[(unsigned int)i] = m.matrix[(unsigned int)i]*num;
        }
    }
    void Matrix::operator*=(Matrix const &m){
        if(this->col != m.row){
            throw invalid_argument{"Can't do this shit"};
        }
        Matrix ans = *this*m;
        this->row = ans.row;
        this->col = ans.col;
        this->matrix = ans.matrix;
    }
    ostream& operator<< (ostream& output, Matrix const &m) {
        for(int i=0; i< m.row; i++){
            output << "[";
            for(int j=0; j<m.col;j++){
                double num =m.matrix.at((unsigned int)( i*m.col+ j));
                if(j==m.col-1){
                    output << num;
                }
                else{
                    output << num << " ";
                }
            }
            if(i == m.row -1){
                output << "]";
            }
            else{
                output << "]\n";
            }
        }
        return output;
    }
    istream & operator >> (istream &input,  Matrix &m)
    {
        string s;
        string ans;
        while(getline(input,s)){
            ans+=s;
        }
        int rows=0;
        int cols=0;
        int size =0;
        for(size_t i =0; i<ans.size()-1; i++){
            if(ans[i] == ' ' && ans[i+1]== ' '){
                throw invalid_argument{"Can't do this shit"};
            }
            if(ans[i] == ',' && ans[i+1]!= ' '){
                throw invalid_argument{"Can't do this shit" + ans};
            }
            if(ans[i] == ']' && ans[i+1]== ' '){
                throw invalid_argument{"Can't do this shit"};
            }
            if(ans[i] == ' ' && ans[i+1]== ','){
                throw invalid_argument{"Can't do this shit"};
            }
        }
        for(size_t i =0; i<ans.size();i++){
            if(ans[i]==']'){
                rows++;
            }
        }
        size_t count=1;
        while(ans[count]!=']'){
            if(ans[count]==' '){
                cols++;
                count++;
            }
            count++;
        }
        string num;
        count=0;
        int count_numbers =0;
        size_t count_mat=0;
        vector<double> mat((size_t)(cols*rows));
        for(size_t i =0; i<ans.size();i++){
            if(ans[i]=='[' || ans[i]==']'){
                continue;
            }
            if(ans[i]==',' && ans[i+1] == ' '){
                i+=2;
            }
            else if(ans[i]==' '){
                num[count]= '\0';
                mat[count_mat]= stod(num);
                count_mat++;
                num=' ';
                count =0;
                count_numbers++;
            }
            else{
                num[count] = ans[i];
                count++;
            }
        }
        if(count_numbers!= rows*cols){
            throw invalid_argument{"Can't do this shit1"};
        }
        m.row = rows;
        m.col = cols;
        m.matrix = mat;
        return input;
    }

}