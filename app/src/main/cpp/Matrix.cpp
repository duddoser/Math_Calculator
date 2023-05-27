#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Matrix_Exception.cpp"

using namespace std;
template<class T> class Matrix{
 protected:
  T **ptr;
  int height;
  int width;
 public:
  Matrix(int Height = 2, int Width = 2){
    //конструктор
    height = Height;
    width = Width;
    ptr = new T* [height];
    for (int i = 0; i < height; i++)
      ptr[i] = new T[width];
  }

  Matrix(const Matrix& M){
    //конструктор копий
    height = M.height;
    width = M.width;
    ptr = new T* [height];
    for (int i = 0; i < height; i++){
      ptr[i] = new T[width];
      for (int j = 0; j < width; j++)
        ptr[i][j] = M.ptr[i][j];
    }

  }

  Matrix(int H, int W, vector<T> array)
  {
    height = H;
    width = W;
    ptr = new T* [height];
    for (int i = 0; i < height; i++)
    {
      ptr[i] = new T[width];
      for (int j = 0; j < width; j++)
        ptr[i][j] = array[i * width + j];
    }
  }

  Matrix(int H, int W, T elem)
  {
    height = H;
    width = W;
    ptr = new T* [height];
    for (int i = 0; i < height; i++)
    {
      ptr[i] = new T[width];
      for (int j = 0; j < width; j++)
        ptr[i][j] = elem;
    }
  }


  Matrix(ifstream& ifs){
    //конструктор для чтения матриц из файла
    ifs >> height;
    ifs >> width;
    ptr = new T* [height];
    for (int i = 0; i < height; i++){
      ptr[i] = new T[width];
      for (int j = 0; j < width; j++)
        ifs >> ptr[i][j];
    }
  }

  ~Matrix(){
    //деструктор
    if (ptr != NULL){
      for (int i = 0; i < height; i++)
        delete[] ptr[i];
      delete[] ptr;
      ptr = NULL;
    }
  }

  int h(){
    return height;
  }

  int w(){
    return width;
  }

  Matrix identityMatrix()
  {
    Matrix result(height, width);
    for(int i = 0; i < height; i++)
      result[i][i] = 1;
    return result;
  }

  Matrix concateMatrix(Matrix& b)
  {
    if (height != b.h ())
      return Matrix();
    Matrix result(height, width + b.w());
    for (int i = 0; i < height; i++){
      for (int j = 0; j < width; j++)
        result[i][j] = ptr[i][j];
      for (int j = 0; j < b.w (); j++)
        result[i][j + width ] = b[i][j];
    }
    return result;
  }

  Matrix& operator=(Matrix const& M){
    if(height == M.height && width == M.width){
      for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++)
          ptr[i][j] = M.ptr[i][j];
      }
    }
    else{
      throw WrongDimensions("Unequal size of matrices in operator= ", height, width, M.height, M.width);
    }
    return *this;
  }

  T* operator[](int index){
    if(index < 0){
      throw NegativeIndex("Negative index in opeartor[] ", index, -1);
    }
    if(index >= height){
      throw TooWideIndex("Too wide index in operator[] ", index, -1);
    }
    else return ptr[index];
  }

  T& operator()(int index1, int index2){
    if(index1 < 0  || index2 < 0 ){
      throw NegativeIndex("Negative index in operator() ", index1, -1);
    }
    if(index1 >= height || index2 >= height){
      throw TooWideIndex("Too wide index in operator() ", index1, -1);
    }
    else return ptr[index1][index2];
  }

  Matrix operator+(){
    // унарный плюс - транспонирование
    Matrix<T> Result(width, height);
    for(int i = 0; i < height; i++){
      for(int j = 0; j < width; j++){
        Result.ptr[j][i] = ptr[i][j];
      }
    }
    return Result;
  }

  Matrix operator+(Matrix M){
    if(width != M.width || height != M.height){
      throw WrongDimensions("Unequal size of matrices: ", height, width, M.height, M.width);
    }
    else{
      Matrix<T> Result(height, width);
      for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
          Result.ptr[i][j] = ptr[i][j] + M.ptr[i][j];
        }
      }
      return Result;
    }
  }

  Matrix operator*(Matrix M){
    if(width != M.height){
      throw WrongDimensions("Unequal size of matrices: ", height, width, M.height, M.width);
    }
    else{
      Matrix<T> Result(height, M.width);
      T cur_element;
      for(int i = 0; i < height; i++){
        for(int j = 0; j < M.width; j++){
          cur_element = 0;
          for(int k = 0; k < width; k++)
            cur_element += ptr[i][k] * M.ptr[k][j];
          Result.ptr[i][j] = cur_element;
        }
      }
      return Result;
    }
  }

  template<class T1> friend ostream& operator<<(ostream& s, Matrix<T1> M);
  template<class T1> friend istream& operator>>(istream& s, Matrix<T1>& M);

};


template<class T> ostream& operator<<(ostream& s, Matrix<T> M){
  if(typeid(s) == typeid(ofstream)){
    s << M.height << " " << M.width << " ";
    s << "\n";
  }
  for(int i = 0; i < M.height; i++){
    for(int j = 0; j < M.width; j++){
      s << M.ptr[i][j] << " ";
    }
    s << "\n";
  }

  return s;
}

template<class T> istream& operator>>(istream& s, Matrix<T>& M){
  if(typeid(s) == typeid(ifstream)){
    int h, w;
    s >> h >> w;
    if(w != M.width || h != M.height){
      // При чтении из файла и несовпадении размеров матриц, очищаем выделенную памать
      // и выделяем ее по новой
      for (int i = 0; i < M.height; i++)
        delete[] M.ptr[i];
      delete[] M.ptr;
      M.ptr = new T* [M.height];
      for (int i = 0; i < M.height; i++)
        M.ptr[i] = new T[M.width];
    }
  }
  for(int i = 0; i < M.height; i++){
    for(int j = 0; j < M.width; j++){
      s >> M.ptr[i][j];
    }
  }
  return s;
}

