#pragma once

#include <iostream>
#include <vector>

#include "Vec3.h"

/*	TODO :	Mat class is not required now, so it's ignored	*/

namespace Galatea
{
    struct Mat4;

    class Mat
    {
        private:
		    //=============================================================
		    //========== Variables ========================================

            unsigned int    m_lines;
            unsigned int    columns;
            float*          data;

        public:
		    //=============================================================
		    //========== Constructors/Destructors =========================

            Mat();
            Mat(const unsigned int& l, const unsigned int& c);
            Mat(unsigned int&& l, unsigned int&& c);
            Mat(const Mat& m);
            Mat(Mat&& m);
            Mat(const Mat4& m);
            ~Mat();

            //=============================================================
            //========== Properties =======================================

            const unsigned int&     Lines() const;
            const unsigned int&     Columns() const;
			const float*		    Array() const;

            const float&            Accessor(const unsigned int& l, const unsigned int& c) const;
            const float&            Accessor(const unsigned int& i) const;

            float&                  Accessor(const unsigned int& l, const unsigned int& c);
            float&                  Accessor(const unsigned int& i);

            //=============================================================
		    //========== Methods ==========================================

            Mat&        Init(const unsigned int& l, const unsigned int& c, float* array = nullptr);
            Mat&        Zero();
            void        Display() const;
            Mat         Transpose() const;
            Mat&        Transpose();
		    Mat         GetSubMatrix(const unsigned int& l, const unsigned int& c) const;
            float       Determinant() const;
            float       GetMinor(const unsigned int& l, const unsigned int& c) const;
            float       GetCofactor(const unsigned int& l, const unsigned int& c) const;
            Mat			GetCofactorMatrix() const;
            Mat			Inverse() const;

            static Mat  Identity(const unsigned int& size);
            static Mat  GetMat3Vectors(const Vec3& v1, const Vec3& v2, const Vec3& v3);

            //=============================================================
		    //========== Operator =========================================

            Mat	        operator+(const Mat& m) const;
            Mat	        operator-(const Mat& m) const;
            Mat	        operator*(const Mat& m) const;
            Mat	        operator*(const float& scale) const;
            Mat	        operator/(const float& scale) const;
            Mat&        operator=(const Mat& m);
            Mat&        operator=(Mat&& m);
            Mat&        operator+=(const Mat& m);
            Mat&        operator-=(const Mat& m);
            Mat&        operator*=(const Mat& m);
            Mat&        operator*=(const float& scale);
            Mat&        operator/=(const float& scale);

            float*      operator[](int pos) const;
		    float*      operator[](int pos);
    };

	//=============================================================
	//========== Operator: ostream ================================
    
    std::ostream&	operator<<(std::ostream& os, const Mat& m);
}