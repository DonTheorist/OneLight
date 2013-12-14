#ifndef FLUX_MATRIX4_H
#define FLUX_MATRIX4_H

#include "FluxVector2.hpp"
#include "FluxVector3.hpp"
#include "FluxUtils.hpp"

#include <iostream>
#include <array>
#include <cmath>

#define MATRIX4_SIZE 16

namespace Flux
{
    /**
     * This class represents a 4x4 square matrix. Elements of the matrix are stored in one continuous std::array, in row-major order.
     */
    class Matrix4
    {
        public:
            /** Default constructor.
             * Matrix is initialised as the 4x4 identity matrix. */
            Matrix4();
            /** Constructor allowing for all elements to be set (remeber in row-major order). */
            Matrix4(float m00, float m01, float m02, float m03,
                    float m10, float m11, float m12, float m13,
                    float m20, float m21, float m22, float m23,
                    float m30, float m31, float m32, float m33);
            /** Default destructor. */
            ~Matrix4();

            /** Transpose the matrix. */
            void transpose();

            /** Transpose a matrix. */
            static Matrix4 transpose(const Matrix4 &m);

            /** Returns the deterimnate of the matrix. */
            float determinant() const;

            /** Converts this matrix into its inverse. */
            void inverse();

            /** Returns the inverse of the given matrix. */
            static Matrix4 inverse(const Matrix4 &m);

            /** Returns a matrix representing a scale transform.
             * @param sx scale in the x direction.
             * @param sy scale in the y direction.
             */
            static Matrix4 makeScale(const float &sx, const float &sy);

            /** Returns a matrix representing a scale transform.
             * @param scale the x component and y component fo the Vector2 represent the scale in their respective directions.
             */
            static Matrix4 makeScale(const Vector2 &scale);

            /** Returns a matrix represeting a rotation around the z axis of theta radians counter clockwise. */
            static Matrix4 makeRotateZ(const float &theta);

            /** Returns a matrix represting a translation by x and y. */
            static Matrix4 makeTranslate(const float &x, const float &y);

            /** Returns a matrix representing a translation by the Vector2. */
            static Matrix4 makeTranslate(const Vector2 &t);

            /** Returns a matrix representing a transformation.
             * The tranformation is applied in the order of the arguments given (scale, rotation, translation).
             * @param sx scale in the x direction.
             * @param sy scale in the y direction.
             * @param theta rotation in radians counter clockwise arounf the z axis.
             * @param x translation in the x direction
             * @param y translation in the y direction.
             */
            static Matrix4 makeTransform(const float &sx, const float &sy, const float &theta, const float &x, const float &y);

            /** Retruns a matrix representing a transformation. See Matrix4::makeTransform(const float &sx, const float &sy, const float &theta, const float &x, const float &y) for more information.
             * This method is the same except Vector2 are used to represent the scale and translation.
             */
            static Matrix4 makeTransform(const Vector2 &scale, const float &theta, const Vector2 &translate);

            /** Returns a matrix representing orthognal projection. Used when constructing OrthographicCamera. */
            static Matrix4 makeOrthographic(const float &left, const float &right, const float &bottom, const float &top, const float &near, const float &far);

            /** Access an element of the matrix.
             * @param index the index to access (matrix is stored as a continuous row-major array). 
             */
            float& operator[] (const unsigned int &index);

            /** Test if two matricies are equivelant. 
             * Done with an element by element comparison
             */
            bool operator== (const Matrix4 &m) const;

            /** Test if two matrices are not equivelant. */
            bool operator!= (const Matrix4 &m) const;

            /** Perform matrix addition. */
            Matrix4& operator+= (const Matrix4 &m);

            /** Perform matrix multiplication. */
            Matrix4& operator*= (const Matrix4 &m);

            /** Perform matrix subtraction. */
            Matrix4& operator-= (const Matrix4 &m);

            /** Multiples a Vector3 by a matrix.
             * Whilst it is not mathmatically possible to multiple a 4x4 matric by a 3x1 vector it is done here by treating the Vector3 as a 4x1 vector, with the additional fourth element being set to one. The return value is hen the x, y and z componetns of the resulting vector.
             */
            Vector3 operator* (const Vector3 &v);

            /** Perform matrix addition. */
            Matrix4 operator+ (const Matrix4 &m) const;

            /** Perform matrix subtraction. */
            Matrix4 operator- (const Matrix4 &m) const;

            /** Perform matrix multiplication. */
            Matrix4 operator* (const Matrix4 &m) const;

            static Matrix4 multiplyTransform(const Matrix4 &m1, const Matrix4 &m2); 

            /** Write elements to stream, convenient for debugging. */
            friend std::ostream& operator<<(std::ostream &out, const Matrix4 &m);

            /** Return a const copy of the elements. */
            std::array<float, MATRIX4_SIZE> getElements() const;

            /** 4x4 identity matrix. */
            static const Matrix4 IDENTITY;

        private:
            /** Continuous std::array storing the matrix elements in row major order.
             * Defaults to the identity matrix.
             */
            std::array<float, MATRIX4_SIZE> elements = {{ 1.0f, 0.0f, 0.0f, 0.0f,
                                   0.0f, 1.0f, 0.0f, 0.0f,
                                   0.0f, 0.0f, 1.0f, 0.0f,
                                   0.0f, 0.0f, 0.0f, 1.0f }}; 
    };
}

#endif

