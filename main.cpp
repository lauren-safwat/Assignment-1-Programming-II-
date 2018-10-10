// Course:  CS213 - Programming II  - 2018
// Title:   Assignment I - Task 1 - Problem 0
// Program: CS213-2018-A1-T1-P0
// Purpose: A set of functions for matrix manipulation
// Author 1 and ID and group: Lauren Safwat - 20170203 - Group 8
// Author 2 and ID and group: Kareem Magdy - 20170197 - Group 8
// Author 3 and ID and group: Amr Osama - 20170185 - Group 7
// Date:    10 October 2018


#include <iostream>
#include <cassert>
#include <iomanip>
#include <cstring>
#include <cmath>

using namespace std;

/* Create The New Structure ---------- */

struct matrix
{
    int rows,cols;
    int **p;

};

void createMatrix (int rows, int cols, int data[], matrix & mat);
matrix create_matrix(matrix & res,matrix & mat1);

/* =============== Task (1) =================== */

matrix operator+  (matrix mat1, matrix mat2); // Add if same dimensions
matrix operator-  (matrix mat1, matrix mat2); // Sub if same dimensions
matrix operator*  (matrix mat1, matrix mat2); // Multi if col1 == row2
matrix operator+  (matrix mat1, int scalar);  // Add a scalar
matrix operator-  (matrix mat1, int scalar);  // Subtract a scalar
matrix operator*  (matrix mat1, int scalar);  // Multiple by scalar

/* =============== Task (2) =================== */

istream& operator>> (istream& in, matrix& mat);
matrix operator+= (matrix& mat1, matrix mat2);
matrix operator-= (matrix& mat1, matrix mat2);
matrix operator+= (matrix& mat, int scalar);
matrix operator-= (matrix& mat, int scalar);
void   operator++ (matrix& mat);
void   operator-- (matrix& mat);

/* =============== Task (3) =================== */

ostream& operator<< (ostream& out, matrix mat);
bool   operator== (matrix mat1, matrix mat2);
bool   operator!= (matrix mat1, matrix mat2);
bool   isSquare   (matrix mat);
bool   isSymetric (matrix mat);
bool   isIdentity (matrix mat);
matrix transpose(matrix mat);

int main()
{
int data1[]={1,2,3,4,5,6,7,8,9};
matrix mat1,mat2,mat3;
createMatrix(3,3,data1,mat1);
createMatrix(3,3,data1,mat2);
createMatrix(3,3,data1,mat3);
cout << mat1;
cout << endl;
cout << (mat1 + mat2);
cout << endl;
cout << (mat1 - mat3);
cout << endl;
cout << (mat1 * mat2);
cout << endl;
cout << (mat2 + 3);
cout << endl;
cout << (mat3 - 1);
cout << endl;
cout << (mat2 * 2);
cout << endl;
cout << (mat1 += mat3);
cout << endl;
cout << (mat2 -= mat1);
cout << endl;
cout << (mat1 += 5);
cout << endl;
cout << (mat1 -= 2);
cout << endl;
cout << (mat1 == mat3);
cout << endl;
cout << (mat1 != mat2);
cout << endl;
cout << isSquare(mat1);
cout << endl;
cout << isSymetric(mat1);
cout << endl;
cout << isIdentity(mat1);
cout << endl;
cout << transpose(mat1);
cout << endl;
++mat1;
cout << mat1;
cout << endl;
--mat2;
cout << mat2;
cout << endl;
return 0;
}


/* =============== Creating The Matrix (1) =================== */

void createMatrix(int rows, int cols, int data[],matrix & mat)
{   mat.rows=rows;
    mat.cols=cols;
    int counter=0;
    mat.p=new int*[rows];
    for(int i=0;i<rows;i++)
    {
        mat.p[i]=new int[cols];
    }
    for(int i=0;i<rows;i++)
        {
            for(int j=0;j<cols;j++)
                {
                    mat.p[i][j]=data[counter];
                    counter++;
                }
        }

}


/* =============== Input The Elements =================== */

// istream allows you to input your elements of matrix

istream& operator>> (istream& in, matrix& mat)
{
    cout<<"enter the elements of the matrix "<<endl;
    for (int i = 0 ; i < mat.rows ; i++)
    {
        for (int j = 0 ; j < mat.cols ; j++)
        {
            in>>mat.p[i][j];
        }
    }
    return in;
}



/* =============== Output The Elements =================== */

ostream& operator<< (ostream& out, matrix mat)
{
    for(int i=0;i<mat.rows;i++)
    {
       for(int j=0;j<mat.cols;j++)
        {
            out<<mat.p[i][j]<<" ";
        }
        cout<<endl;
    }
}


/* =============== Creating a new matrix for the result =================== */

matrix create_matrix(matrix & res,matrix & mat1)
{
    res.rows=mat1.rows;
    res.cols=mat1.cols;
    res.p=new int*[res.rows];
    for(int i=0;i<res.rows;i++)
        res.p[i]=new int [res.cols];

}


/* =============== Adding 2 Matrices if they have the same dimensions =================== */
/* =============== The function takes 2 matrices & returns a new matrix with the sum =================== */

matrix operator+  (matrix mat1, matrix mat2)
{
    assert((mat1.rows = mat2.rows) && (mat1.cols = mat2.cols));
    matrix res;
    create_matrix(res,mat1);
    for (int i=0; i<res.rows; i++)
        for (int j=0; j<res.cols; j++)
            res.p[i][j] = mat1.p[i][j] + mat2.p[i][j];
    return res;
}


/* =============== Subtracting 2 Matrices if they have the same dimensions =================== */
/* =============== The function takes 2 matrices & returns a new matrix with the difference =================== */

matrix operator-  (matrix mat1, matrix mat2)
{
    assert((mat1.rows = mat2.rows) && (mat1.cols = mat2.cols));
    matrix res;
    create_matrix(res,mat1);
    for (int i=0; i<res.rows; i++)
        for (int j=0; j<res.cols; j++)
            res.p[i][j] = mat1.p[i][j] - mat2.p[i][j];
    return res;
}


/* =============== Multiplying 2 Matrices if col1 = row2 =================== */
/* =============== The function takes 2 matrices & returns a new matrix with the product =================== */

matrix operator*  (matrix mat1, matrix mat2)
{
    assert(mat1.cols = mat2.rows);
    matrix res;
    res.rows=mat1.rows;
    res.cols=mat2.cols;
    res.p=new int*[res.rows];
    for(int i=0;i<res.rows;i++)
        res.p[i]=new int [res.cols];

    for (int i=0; i<res.rows; i++)
        for (int j=0; j<res.cols; j++)
        {
            int sum=0;
            for (int k=0; k<mat1.cols; k++)
                sum += mat1.p[i][k] * mat2.p[k][j];
            res.p[i][j] = sum;
        }
    return res;
}


/* =============== Adding a scalar to a matrix and displaying the result in a new matrix =================== */

matrix operator+  (matrix mat1, int scalar)
{
    matrix res;
    create_matrix(res,mat1);
    for (int i=0; i<res.rows; i++)
        for (int j=0; j<res.cols; j++)
            res.p[i][j] = mat1.p[i][j] + scalar;
    return res;
}


/* =============== Subtracting a scalar from a matrix and displaying the result in a new matrix =================== */

matrix operator-  (matrix mat1, int scalar)
{
    matrix res;
    create_matrix(res,mat1);
    for (int i=0; i<res.rows; i++)
        for (int j=0; j<res.cols; j++)
            res.p[i][j] = mat1.p[i][j] - scalar;
    return res;
}


/* =============== Multiplying a matrix by a scalar and displaying the result in a new matrix =================== */

matrix operator*  (matrix mat1, int scalar)
{
    matrix res;
    create_matrix(res,mat1);
    for (int i=0; i<res.rows; i++)
        for (int j=0; j<res.cols; j++)
            res.p[i][j] = mat1.p[i][j] * scalar;
    return res;
}


/* =============== Adding 2 Matrices (2) =================== */

matrix operator += (matrix &mat1 , matrix &mat2)
{
  matrix mati;
create_matrix(mati,mat1);
matrix mati_2;
create_matrix(mati_2,mat2);
  for (int i = 0 ; i < mat1.rows ; i++)
  {
      for (int j = 0 ; j < mat1.cols ; j++)
      {
          mat1.p[i][j] += mat2.p[i][j];
      }
  }
  cout<<"the += of two matrices is"<<endl;

  for (int i = 0 ; i < mat1.rows ; i++)
  {
      for (int j = 0 ; j<mat1.cols ; j++)
      {
          cout<<mat1.p[i][j]<<" ";
      }
      cout<<endl;
  }
  return mat1;
}

/* =============== Subtracting 2 Matrices (2) =================== */

matrix operator -=(matrix &mat1 , matrix &mat2)
{
    for (int i = 0 ; i < mat1.rows ; i++)
  {
      for (int j = 0 ; j < mat1.cols ; j++)
      {
          mat1.p[i][j] -= mat2.p[i][j];
      }
  }
    cout<<"the -= of two matrices is"<<endl;

  for (int i = 0 ; i  <mat1.rows ; i++)
  {
      for (int j = 0 ; j < mat1.cols ; j++)
      {
          cout<<mat1.p[i][j]-mat2.p[i][j]<<" ";
      }
      cout<<endl;

  }
  return mat1;
}

/* =============== Increments The Matrix Elements =================== */

void operator++ (matrix &mat1)
{
    for (int i = 0 ; i < mat1.rows ; i++)
    {
        for (int j = 0 ; j < mat1.cols ; j++)
        {
            mat1.p[i][j]++;
        }
    }
 cout<<"matrix after increment by 1 is "<<endl;
}


/* =============== Decrements The Matrix Elements =================== */

void operator-- (matrix &mat1)
{
    for (int i = 0 ; i < mat1.rows ; i++)
    {
        for (int j = 0 ; j < mat1.cols ; j++)
        {
            mat1.p[i][j]--;
        }
    }
 cout<<"matrix after decrement by 1 is "<<endl;
}


/* =============== Add A Value To All The Elements Of The Matrix (2) =================== */

matrix operator+= (matrix &mat1 , int scalar)
{
    cout<<"enter the number that you want to add to the matrix "<<endl;
    cin>>scalar;
     cout<<"the Matrix after adding "<<scalar<<" to it is"<<endl;

    for (int i = 0 ; i < mat1.rows ; i++)
    {
        for (int j = 0 ; j < mat1.cols ; j++)
        {
           cout<<mat1.p[i][j]+scalar<<" ";
        }
        cout<<endl;
    }
    return mat1;
}

/* =============== Subtract A Value From All The Elements Of The Matrix (2) =================== */

matrix operator-= (matrix &mat1 , int scalar)
{
    cout<<"enter the number that you want to subtract from the matrix "<<endl;
    cin>>scalar;
     cout<<"the Matrix after subtracting "<<scalar<<" from it is"<<endl;
    for (int i = 0 ; i < mat1.rows ; i++)
    {
        for (int j = 0 ; j < mat1.cols ; j++)
        {
           cout<<mat1.p[i][j]-scalar<<" ";
        }
        cout<<endl;
    }
    return mat1;
}

/* =============== Checks For 2 Equal Matrices =================== */

bool   operator== (matrix mat1, matrix mat2)
{
    bool IsSame=true;
    if((mat1.rows==mat2.rows)&&(mat1.cols==mat2.cols))
        {
            for (int i = 0 ; i < mat1.rows ; i++)
            {
                for (int j = 0 ; j < mat1.cols ; j++)
                {
                    if(mat1.p[i][j]!=mat2.p[i][j])
                        IsSame=false;
                }
        }
            return IsSame==true? true:false;
        }
    else
        {
            return false;
        }
}

/* =============== Checks For 2 Non-Equal Matrices =================== */

bool   operator!= (matrix mat1, matrix mat2)
{
    bool NotSame=false;
    if((mat1.rows==mat2.rows)&&(mat1.cols==mat2.cols))
        {
            for (int i = 0 ; i < mat1.rows ; i++)
            {
                for (int j = 0 ; j < mat1.cols ; j++)
                {
                    if(mat1.p[i][j]!=mat2.p[i][j])
                        NotSame=true;
                }
        }
            return NotSame==true?true:false;
        }
    else
        {
            return true;
        }

}

/* =============== Checks For Square Matrix =================== */

bool   isSquare   (matrix mat)
{
    return mat.rows==mat.cols?true:false;
}

/* =============== Checks For Square And Symmetric Matrix =================== */

bool   isSymetric (matrix mat)
{
    bool IsSymetric=true;
    if(mat.rows==mat.cols)
    {
        for (int i = 0 ; i < mat.rows ; i++)
        {
            for (int j = 0 ; j < mat.cols ; j++)
            {
                if(mat.p[i][j]!=mat.p[j][i])
                    IsSymetric=false;
            }
        }
        return IsSymetric==true?true: false;
    }
    else
    {
     return false;
    }
}

/* =============== Checks For Square And Identity Matrix =================== */

bool   isIdentity (matrix mat)
{
    bool IsIdentity=true;
    if(mat.rows==mat.cols)
    {
        for (int i = 0 ; i < mat.rows ; i++)
        {
            for (int j = 0 ; j < mat.cols ; j++)
            {
                if(i==j)
                    if(mat.p[i][j]!=1)
                        IsIdentity=false;
                else
                {
                    if(mat.p[i][j]!=0)
                        IsIdentity=false;
                }
            }
        }
        return IsIdentity==true?true: false;
    }
    else{return false;}

}

/* =============== Transpose The Matrix =================== */

matrix transpose(matrix mat)//need to delete the pointer
{
 matrix res;
 res.rows=mat.cols;
 res.cols=mat.rows;
 res.p=new int*[mat.cols];
 for(int i=0;i<mat.cols;i++)
    res.p[i]=new int [mat.rows];
 for (int i = 0 ; i < mat.rows ; i++)
    {
        for (int j = 0 ; j < mat.cols ; j++)
        {
          res.p[j][i]=mat.p[i][j];
        }
    }

  return res;
}

