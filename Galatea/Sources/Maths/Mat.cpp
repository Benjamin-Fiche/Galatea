#include "math.h"

#include "Maths/Mat.h"
#include "Maths/Mat4.h"

namespace Galatea
{
    //=============================================================
	//========== Constructors/Destructors =========================

    Mat::Mat() : m_lines {0}, columns {0}, data {nullptr}
    {}

    Mat::Mat(const unsigned int& l, const unsigned int& c)
        : m_lines {l}, columns {c}
    {
        data = new float[m_lines * columns];
        Zero();
    }
    
    Mat::Mat(unsigned int&& l, unsigned int&& c)
        : m_lines {std::move(l)}, columns {std::move(c)}
    {
        data = new float[m_lines * columns];
        Zero();
    }

    Mat::Mat(const Mat& m) : m_lines {m.m_lines}, columns {m.columns}
    {
        data = new float[m_lines * columns];
        
        for (unsigned int i = 0; i < m_lines * columns; i++)
            data[i] = std::move(m.data[i]);
    }
    
    Mat::Mat(Mat&& m)
        : m_lines {std::move(m.m_lines)}, columns {std::move(m.columns)}
    {
        data = new float[m_lines * columns];
        
        for (unsigned int i = 0; i < m_lines * columns; i++)
            data[i] = m.data[i];
    }
	
	Mat::Mat(const Mat4& m) : m_lines {4}, columns {4}
	{
		data = new float[m_lines * columns];
        
		for (unsigned int i{ 0 }; i < m_lines * columns; i++)
            data[i] = m.data[i];
	}
    
    Mat::~Mat()
    {
        if (data != nullptr)
            delete[] data;
    }
    
    //=============================================================
    //========== Properties =======================================
    
    const unsigned int& Mat::Lines() const
    {
        return m_lines;
    }
    
    const unsigned int& Mat::Columns() const
    {
        return columns;
    }
    
    const float& Mat::Accessor(const unsigned int& l, const unsigned int& c) const
    {
        return data[((l - 1) * columns + c) - 1];
    }
    
    const float& Mat::Accessor(const unsigned int& i) const
    {
        return data[i];
    }
    
    float& Mat::Accessor(const unsigned int& l, const unsigned int& c)
    {
        return data[((l - 1) * columns + c) - 1];
    }
    
    float& Mat::Accessor(const unsigned int& i)
    {
        return data[i];
    }

	const float* Mat::Array() const
	{
		return data;
	}
    
    //=============================================================
	//========== Methods ==========================================
    
    Mat& Mat::Init(const unsigned int& l, const unsigned int& c, float* array)
	{
		m_lines = l;
		columns = c;

		if (data != nullptr)
			delete[] data;

		data = new float[m_lines * columns];

        if (array == nullptr)
		    Zero();
        else
        {
            for (unsigned int i = 0; i < m_lines * columns; i++)
                data[i] = array[i];
        }

		return (*this);
	}

    Mat& Mat::Zero()
	{
		for (unsigned int i = 0; i < m_lines * columns; i++)
			data[i] = 0;
		return (*this);
	}

	void Mat::Display() const
	{
        if (m_lines == 0 || columns == 0)
            return;

		std::cout << "| ";
		for (unsigned int i = 0; i < m_lines * columns; i++)
		{
			if (i != 0 && i % columns == 0)
				std::cout << "\n| ";
			std::cout << data[i] << " | ";
		}
		std::cout << "\n";
	}

	Mat Mat::Transpose() const
	{
		Mat		m(columns, m_lines);

		for (unsigned int l = 1; l <= m_lines; l++)
			for (unsigned int c = 1; c <= columns; c++)
				m.Accessor(l, c) = Accessor(c, l);

		return m;
	}

	Mat& Mat::Transpose()
	{
		if (m_lines == columns)
		{
			std::swap(m_lines, columns);
			for (unsigned int l = 1; l <= m_lines; l++)
				for (unsigned int c = l + 1; c <= columns; c++)
					std::swap(Accessor(l, c), Accessor(c, l));
		}
		else
		{
			Mat	tmp(*this);
			std::swap(m_lines, columns);

			for (unsigned int l = 1; l <= m_lines; l++)
				for (unsigned int c = 1; c <= columns; c++)
					Accessor(l,c) = tmp.Accessor(c, l);
		}
		return (*this);
	}

	Mat Mat::GetSubMatrix(const unsigned int& line, const unsigned int& column) const
	{
		Mat		m(m_lines - 1, columns - 1);

		for (unsigned int l = 1; l <= m_lines; l++)
		{
			for (unsigned int c = 1; c <= columns; c++)
			{
				if (l < line && c < column)
					m.Accessor(l, c) = Accessor(l, c);
				else if (l < line && c > column)
					m.Accessor(l, c - 1) = Accessor(l, c);
				else if (l > line && c < column)
					m.Accessor(l - 1, c) = Accessor(l, c);
				else if (l > line && c > column)
					m.Accessor(l - 1, c - 1) = Accessor(l, c);
			}
		}
		return m;
	}

	float Mat::Determinant() const
	{
		if (m_lines == 1 && columns == 1)
			return data[0];
		else if (m_lines == 2 && columns == 2)
			return (data[0] * data[3] - data[2] * data[1]);
		else if (m_lines == 3 && columns == 3)
			return (data[0] * data[4] * data[8] - data[0] * data[5] * data[7] +
				data[1] * data[5] * data[6] - data[1] * data[3] * data[8] +
				data[2] * data[3] * data[7] - data[2] * data[4] * data[6]);
		else if (m_lines == 4 && columns == 4)
		{
			return (data[0] * data[5] * data[10] * data[15] -
				data[0] * data[5] * data[11] * data[14] -
				data[0] * data[6] * data[9] * data[15] +
				data[0] * data[6] * data[11] * data[13] +
				data[0] * data[7] * data[9] * data[14] -
				data[0] * data[7] * data[10] * data[13] -
				data[1] * data[4] * data[10] * data[15] +
				data[1] * data[4] * data[11] * data[14] +
				data[1] * data[6] * data[8] * data[15] -
				data[1] * data[6] * data[11] * data[12] -
				data[1] * data[7] * data[8] * data[14] +
				data[1] * data[7] * data[10] * data[12] +
				data[2] * data[4] * data[9] * data[15] -
				data[2] * data[4] * data[11] * data[13] -
				data[2] * data[5] * data[8] * data[15] +
				data[2] * data[5] * data[11] * data[12] +
				data[2] * data[7] * data[8] * data[13] -
				data[2] * data[7] * data[9] * data[12] -
				data[3] * data[4] * data[9] * data[14] +
				data[3] * data[4] * data[10] * data[13] +
				data[3] * data[5] * data[8] * data[14] -
				data[3] * data[5] * data[10] * data[12] -
				data[3] * data[6] * data[8] * data[13] +
				data[3] * data[6] * data[9] * data[12]);
		}
		else
		{
			float	det {0};

			for (unsigned int c = 1; c <= columns; c++)
				det += Accessor(1, c) * GetCofactor(1, c);
			return det;
		}
	} 

	float Mat::GetMinor(const unsigned int& line, const unsigned int& column) const
	{
		return GetSubMatrix(line, column).Determinant();
	}

	float Mat::GetCofactor(const unsigned int& line, const unsigned int& column) const
	{
		return powf(-1, line + column) * GetMinor(line, column);
	}

	Mat Mat::GetCofactorMatrix() const
	{
		Mat		m (m_lines, columns);
		for (unsigned int l = 1; l <= m_lines; l++)
			for (unsigned int c = 1; c <= columns; c++)
				m.Accessor(l, c) = GetCofactor(l, c);
		return m;
	}

	Mat Mat::Inverse() const
	{
		Mat		m(m_lines, columns);
		float	det = Determinant();

		m = GetCofactorMatrix().Transpose() / det;

		return m;
	}

	Mat Mat::Identity(const unsigned int& size)
	{
		Mat		m(size, size);

		for (unsigned int i = 0; i < size * size; i++)
		{
			if (i % (size + 1) == 0)
				m.data[i] = 1;
			else
				m.data[i] = 0;
		}

		return m;
	}

	Mat Mat::GetMat3Vectors(const Vec3& v1, const Vec3& v2, const Vec3& v3)
	{
		Mat	m(3, 3);

		m.data[0] = v1.x;
		m.data[1] = v1.y;
		m.data[2] = v1.z;
		m.data[3] = v2.x;
		m.data[4] = v2.y;
		m.data[5] = v2.z;
		m.data[6] = v3.x;
		m.data[7] = v3.y;
		m.data[8] = v3.z;

		return m;
	}

    //=============================================================
	//========== Operator =========================================

    Mat Mat::operator+(const Mat& m) const
	{
		Mat		r(m_lines, columns);
		
		for (unsigned int i = 0; i < m_lines * columns; i++)
			r.data[i] = data[i] + m.data[i];

		return r;
	}

	Mat Mat::operator-(const Mat& m) const
	{
		Mat		r(m_lines, columns);

		for (unsigned int i = 0; i < m_lines * columns; i++)
			r.data[i] = data[i] - m.data[i];

		return r;
	}

	Mat Mat::operator*(const Mat& m) const
	{
		Mat		r(m_lines, m.columns);

		for (unsigned int i = 1; i <= r.m_lines; i++)
			for (unsigned int j = 1; j <= r.columns; j++)
				for (unsigned int k = 1; k <= columns; k++)
					r.Accessor(i, j) += Accessor(i, k) * m.Accessor(k, j);

		return r;
	}

	Mat Mat::operator*(const float& scale) const
	{
		Mat	m (m_lines, columns);

		for (unsigned int i = 0; i < m.m_lines * m.columns; i++)
			m.data[i] = data[i] * scale;

		return m;
	}

	Mat Mat::operator/(const float& scale) const
	{
		Mat		r(m_lines, columns);

		for (unsigned int i = 0; i < m_lines * columns; i++)
			r.data[i] = data[i] / scale;

		return r;
	}

	Mat& Mat::operator=(const Mat& m)
	{
		m_lines = m.m_lines;
		columns = m.columns;

		if (data != nullptr)
			delete[] data;

		data = new float[m_lines * columns];

		for (unsigned int i = 0; i < m_lines * columns; i++)
			data[i] = m.data[i];

		return (*this);
	}

	Mat& Mat::operator=(Mat&& m)
	{
		m_lines = std::move(m.m_lines);
		columns = std::move(m.columns);

		if (data != nullptr)
			delete[] data;
		
		data = new float[m_lines * columns];

		for (unsigned int i = 0; i < m_lines * columns; i++)
			data[i] = std::move(m.data[i]);

		return (*this);
	}

	Mat& Mat::operator+=(const Mat& m)
	{
		for (unsigned int i = 0; i < m_lines *  columns; i++)
			data[i] += m.data[i];

		return (*this);
	}

	Mat& Mat::operator-=(const Mat& m)
	{
		for (unsigned int i = 0; i < m_lines *  columns; i++)
			data[i] -= m.data[i];

		return (*this);
	}

	Mat& Mat::operator*=(const Mat& m)
	{
		float		sum{0};

		for (unsigned int i = 1; i <= m_lines; i++)
		{
			for (unsigned int j = 1; j <= columns; j++)
			{
				for (unsigned int k = 1; k <= columns; k++)
					sum += Accessor(i, k) * m.Accessor(k, j);

				Accessor(i, j) = sum;
				sum = 0;
			}
		}

		return (*this);
	}

	Mat& Mat::operator*=(const float& scale)
	{
		for (unsigned int i = 0; i < m_lines * columns; i++)
			data[i] *= scale;
		
		return (*this);
	}

	Mat& Mat::operator/=(const float& scale)
	{
		for (unsigned int i = 0; i < m_lines * columns; i++)
			data[i] /= scale;

		return (*this);
	}

	float* Mat::operator[](int pos) const
	{
		return &data[pos * columns];
	}

	float* Mat::operator[](int pos)
	{
		return &data[pos * columns];
	}

	//=============================================================
	//========== Operator: ostream ================================

	std::ostream& operator<<(std::ostream& os, const Mat& m)
	{
		os << "| ";
		for (unsigned int i = 0; i < m.Lines() * m.Columns(); i++)
		{
			if (i != 0 && i % m.Columns() == 0)
				os << "\n| ";
			os <<m.Accessor(i) << " | ";
		}
		return os;
	}
}