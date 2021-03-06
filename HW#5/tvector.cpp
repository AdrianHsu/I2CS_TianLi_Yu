#include "tvector.h"

template<int T>
TVector<T>::TVector()
{   
    vec = MyVector(T); 
}

template<int T>
TVector<T>::TVector(const TVector<T>& in)
    : vec(in.vec){}

template<int T>
TVector<T>::~TVector()
{
}

template<int T>
const TVector<T>& TVector<T>::operator=(const TVector<T> in)
{   
    vec = in.vec;
    return (*this);
}

template<int T>
int TVector<T>::getLength() const
{   
    return vec.getLength();
}

template<int T>
double TVector<T>::get(const int i) const
{   
    return vec.get(i);
}

template<int T>
TVector<T>& TVector<T>::set(const int i, const double value)
{   
    vec.set(i, value);
    return (*this);
}

template<int T>
TVector<T> TVector<T>::operator+(const TVector<T>& in) const
{   
    TVector<T> tmp;
    tmp.vec = vec + in.vec;
    return tmp;
}

template<int T>
double TVector<T>::operator*(const TVector<T>& in) const
{   
    return vec * in.vec;
}

template<int T>
TVector<T>& TVector<T>::resize(const int i)
{   
    cout << "ERROR: resize() for TVector is not defined." << endl;
    return *this;
}

template<int T>
ostream& operator<<(ostream& out, const TVector<T>& in)
{   
    out << in.vec;
    return out;
}
