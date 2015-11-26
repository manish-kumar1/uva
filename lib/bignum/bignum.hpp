#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <type_traits>
#include <sstream>
#include <exception>



class big_unsigned;

big_unsigned operator + (const big_unsigned& a, const big_unsigned& b);
big_unsigned operator - (const big_unsigned& a, const big_unsigned& b);
big_unsigned operator * (const big_unsigned& a, const big_unsigned& b);
big_unsigned karatsuba(const big_unsigned& a, const big_unsigned& b);



template<typename Container>
class bignum_storage {
public:
    bignum_storage(size_t __n) : _M_blk(__n) {}

private:
    Container   _M_blk;
};



template<typename T>
class bignum_traits {
public:
    typedef T  digit_type;
    typedef T* pointer;

    static constexpr digit_type sum(const digit_type a, const digit_type b) { // a+b
        return a + b;
    }
    static constexpr digit_type sum(const digit_type a, const digit_type b, const digit_type c) { // a+b
        return a + b + c;
    }
    static constexpr digit_type sub(const digit_type a, const digit_type b) {   // a-b
        return a - b;
    }
    static constexpr digit_type to_digit_type(const int x) {
        return (x);
    }

    static constexpr char to_char_type(const int x) {
        return x + '0';
    }
};

class bignum_base {
public:
    typedef bignum_traits<int8_t>  traits_type;

    typedef traits_type::digit_type digit_type;
    typedef digit_type     base;
    typedef std::vector<digit_type> container_type;

    typedef std::vector<digit_type>::iterator iterator;
    typedef std::vector<digit_type>::const_iterator const_iterator;
    typedef std::vector<digit_type>::reverse_iterator reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    bignum_base() = delete;

    explicit bignum_base(digit_type __base, 
                const std::vector<digit_type>& __digits = std::vector<digit_type>()) : 
                _M_base(__base), _M_blk(__digits) {
    }

    inline size_t size() const { return _M_blk.size(); }

    inline iterator begin() { return iterator(_M_blk.begin());  }
    inline const_iterator begin() const { return const_iterator(_M_blk.cbegin()); }
    inline const_iterator cbegin() const { return const_iterator(_M_blk.cbegin()); }
    inline iterator end() { return iterator(_M_blk.end()); }
    inline const_iterator end() const { return const_iterator(_M_blk.cend()); }
    inline const_iterator cend() { return const_iterator(_M_blk.cend()); }
    inline const_reverse_iterator rbegin() const { return const_reverse_iterator(_M_blk.end()); }
    inline const_reverse_iterator rend() const { return const_reverse_iterator(_M_blk.begin()); }

    bignum_base& prune_zeros() {
        while ((_M_blk.size() > 1) && (_M_blk.back() == digit_type(0))) 
            _M_blk.pop_back();

        if (_M_blk.empty()) _M_blk.push_back(digit_type(0));
        return *this;
    }

    inline bignum_base& prepend(const digit_type __digit) {
        _M_blk.push_back(__digit);
        return (*this);
    }

    inline size_t resize(size_t __new_size, const digit_type __digit) {
        _M_blk.resize(__new_size, __digit);
        return __new_size;
    }
protected:
    base _M_base;
    container_type _M_blk;
};


class big_unsigned : public bignum_base {
public:
    // modifiers
    big_unsigned() : bignum_base(10) {_M_blk.push_back(digit_type(0));}

    big_unsigned(unsigned long long __rhs) : bignum_base(10) {
        do {
            _M_blk.push_back(digit_type(__rhs % _M_base));
            __rhs /= _M_base;
        } while (__rhs > 0ull);
    }

    big_unsigned(const big_unsigned& __rhs) : bignum_base(__rhs._M_base, __rhs._M_blk) {}
    big_unsigned(big_unsigned&& __rhs) : bignum_base (std::move(__rhs)) {}

    big_unsigned& operator = (const big_unsigned& __rhs) {
        if (this != &__rhs) {
            this->_M_base = __rhs._M_base;
            this->_M_blk  = __rhs._M_blk;
        }
        return (*this);
    }

    big_unsigned& operator = (big_unsigned&& __rhs) {
        if (this != &__rhs) {
            _M_base = std::move(__rhs._M_base);
            _M_blk = std::move(__rhs._M_blk);
        }
        return *this;
    }

    explicit big_unsigned(const std::string& __rhs) : bignum_base(10) {
        std::transform(__rhs.rbegin(), __rhs.rend(), std::inserter(_M_blk, _M_blk.begin()), [](const std::string::value_type _d) {
            return _d - '0';
        });
        prune_zeros();
    }

//#if 0
    big_unsigned& operator += (const big_unsigned& __rhs) {
        // TODO: check base is same ?
        if (_M_blk.size() < __rhs.size()) _M_blk.resize(__rhs.size(), traits_type::digit_type(0));
        bool _carry = false;
        auto _adder = 
            [&_carry, this](const digit_type __d1, const digit_type __d2) {
                auto _tmp = traits_type::sum(__d1, __d2);
                if (_carry) _tmp = traits_type::sum(_tmp, traits_type::digit_type(1));
                if (_tmp < this->_M_base) {
                    _carry = false;  //traits_type::digit_type(0);
                    return _tmp;
                } else {
                    _carry = true; //traits_type::digit_type(1);
                    return traits_type::sub(_tmp, this->_M_base);
                }
            };

        auto _outIter = std::transform(__rhs.begin(), __rhs.end(), begin(), begin(), _adder);

        for(;_outIter != end(); ++_outIter) {
            if (_carry) *_outIter = _adder(*_outIter, traits_type::digit_type(0));
            else break;
        }

        if (_carry) _M_blk.push_back(traits_type::digit_type(1));

        prune_zeros();
        return (*this);
    }
#if 0

    big_unsigned& operator+= (const big_unsigned& __rhs) {
        if (_M_blk.size() < __rhs.size()) resize(__rhs.size(), traits_type::digit_type(0));
        digit_type _carry(0);
        auto _outIter = std::transform(__rhs.begin(), __rhs.end(), begin(), begin(),
                      [&_carry, this](const digit_type __d1, const digit_type __d2) {
                        auto _tmp = traits_type::sum(__d1, __d2, _carry);
                        _carry = _tmp/this->_M_base;
                        return _tmp % this->_M_base;
        });

        std::all_of(_outIter, end(), [&_carry, this, &_outIter](const digit_type __d1) {
                        auto _tmp = traits_type::sum(__d1, _carry);
                        *_outIter++ = _tmp % this->_M_base;
                        _carry = _tmp/this->_M_base;
                        return _carry != digit_type(0);
        });

        if (_carry == digit_type(1)) prepend(_carry);
        prune_zeros();

        return (*this);
    }
#endif
    big_unsigned& operator -= (const big_unsigned& __rhs) {
        if ((*this) < __rhs) {
            throw std::logic_error("negative");
        }

        const digit_type ZERO(0), ONE(1);
        bool _carry = false;
        auto _subtractor = [&](const digit_type _d1, const digit_type _d2) { // d2 - d1
            auto _tmp = traits_type::sub(_d2, _d1);
            if (_carry) _tmp = traits_type::sub(_tmp, ONE);
            if (_tmp >= ZERO) {
                _carry = false;
                return _tmp;
            }
            else {
                _carry = true;
                return traits_type::sum(_tmp, _M_base);
            }
        };

        auto _outIter = std::transform(__rhs.begin(), __rhs.end(), begin(), begin(), _subtractor);
        for (; _outIter != end(); ++_outIter) {
            if (_carry) {
                _carry = false;
                *_outIter = _subtractor(ONE, *_outIter);
            }
            else break;
        }

        prune_zeros();
        return *this;
    }

    friend big_unsigned karatsuba(const big_unsigned& a, const big_unsigned& b); 
    friend big_unsigned divide(big_unsigned& a, const big_unsigned& b); 

    big_unsigned& operator *= (const big_unsigned& __rhs) {
        return (*this) = karatsuba(*this, __rhs);
    }

    big_unsigned& operator /= (const big_unsigned& __rhs) {
        divide(*this, __rhs);
        return (*this);
    }

    big_unsigned& operator ^= (const unsigned int __rhs) {
        return (*this) = pow(*this, __rhs);
    }

protected:

    big_unsigned pow(const big_unsigned& a, const unsigned int b) {
        if (b == 0) return big_unsigned(1);
        big_unsigned tmp = pow(a, b/2);
        if (b % 2 == 0) return tmp * tmp;
        return tmp * tmp * a;
    }

    template<typename InputIter>
    InputIter init_from(InputIter __start, InputIter __end) {
        if (!_M_blk.empty()) _M_blk.clear();
        std::transform(__start, __end, std::inserter(_M_blk, _M_blk.begin()), traits_type::to_digit_type);
        prune_zeros();
        return __start;
    }

    template<typename T>
    big_unsigned& append(T __digit, size_t __knt) {
        big_unsigned::container_type _new_blk(__knt, __digit);
        _new_blk.insert(_new_blk.end(), _M_blk.begin(), _M_blk.end());
        std::swap(_M_blk, _new_blk);
        prune_zeros();
        return *this;
    }


public:
    
    template<typename T>
    T convert_to() const {
        T _tmp;
        std::stringstream _ss;
        std::transform(rbegin(), rend(), std::ostreambuf_iterator<char>(_ss), [](const digit_type _d) {
            return traits_type::to_char_type(_d);
        });
        //std::copy(rbegin(), rend(), std::ostream_iterator<traits_type::digit_type>(_ss, ""));
        _ss >> _tmp;
        return _tmp;
    }

    // observers
    bool operator == (const big_unsigned& __rhs) const {
        return __rhs.size() == size() && std::equal(this->begin(), this->end(), __rhs.begin());
    }

    bool operator != (const big_unsigned& __rhs) const {
        return ! (operator == (__rhs));
    }

    bool operator < (const big_unsigned& __rhs) const {
        size_t _rhs_size = __rhs.size();
        if (size() < _rhs_size) return true;
        else if (size() > _rhs_size) return false;
        else return std::lexicographical_compare(rbegin(), rend(), __rhs.rbegin(), __rhs.rend());
    } 
    
    friend std::ostream& operator << (std::ostream& __oss, const big_unsigned& __rhs) {
        //std::copy(__rhs.rbegin(), __rhs.rend(), std::ostream_iterator<digit_type>(__oss, ""));
        std::transform(__rhs.rbegin(), __rhs.rend(), std::ostreambuf_iterator<std::ostream::char_type>(__oss), [](const digit_type _d) {
            return traits_type::to_char_type(_d);
        });
        return __oss;
    }

    friend std::istream& operator >> (std::istream& __iss, big_unsigned& __rhs) {
        std::string _in;
        __iss >> _in;
        __rhs = big_unsigned(_in);

        return __iss;
    }
};



template<>
unsigned long long big_unsigned::convert_to<unsigned long long>() const {
        unsigned long long ret = 0ull, tens = 1;
        std::for_each(begin(), end(), [&ret, &tens](const digit_type& _d) {
            ret += (_d*tens);
            tens *= 10;
        });
        return ret;
}

template<>
std::string big_unsigned::convert_to<std::string>() const {
    std::ostringstream _oss;
    std::transform(rbegin(), rend(), std::ostreambuf_iterator<char>(_oss), [](const digit_type _d) {
            return traits_type::to_char_type(_d);
    });
        return _oss.str();
}


big_unsigned karatsuba(const big_unsigned& a, const big_unsigned& b) {
    size_t _a_size = a.size(), _b_size = b.size();
    size_t M = std::max(_a_size, _b_size);
    if (M <= 8) { // base case
        unsigned long long x = a.convert_to<unsigned long long>(),
                           y = b.convert_to<unsigned long long>();
        return big_unsigned(x*y);
    }

    size_t M2 = M/2;
    big_unsigned low1, high1, low2, high2;

    if (M2 < _a_size) {
        low1.init_from(a.begin(), next(a.begin(), M2));
        high1.init_from(next(a.begin(), M2), a.end());
    }
    else {
        low1.init_from(a.begin(), next(a.begin(), _a_size));
    }


    if (M2 < _b_size) {
        low2.init_from(b.begin(), next(b.begin(), M2)); 
        high2.init_from(next(b.begin(), M2), b.end());
    }
    else {
        low2.init_from(b.begin(), next(b.begin(), _b_size));
    }

    big_unsigned z0 = karatsuba(low1, low2);
    big_unsigned z2 = karatsuba(high1, high2);
    big_unsigned z1 = karatsuba(low1+high1, low2+high2);

    big_unsigned t = z2+z0;
    return z2.append(0, 2*M2) + ((z1 - t).append(0, M2)) + z0;
}

big_unsigned divide(big_unsigned& a, const big_unsigned& b) {
    big_unsigned tmp;

    const big_unsigned tens(10);
    for( int i = a.size()-1; i >= 0; i-- )
    {
        tmp *= tens;
        tmp += a._M_blk[i];
        a._M_blk[i] = 0;
        while( !(tmp < b) ) { tmp -= b; a._M_blk[i]++; }
    }

    a.prune_zeros();

    return tmp; 
}

big_unsigned operator + (const big_unsigned& a, const big_unsigned& b) {
    big_unsigned tmp(a);
    tmp += b;
    return tmp;
}

big_unsigned operator - (const big_unsigned& a, const big_unsigned& b) {
    big_unsigned tmp(a);
    tmp -= b;
    return tmp;
}

big_unsigned operator * (const big_unsigned& a, const big_unsigned& b) {
    big_unsigned tmp(a);
    tmp *= b;
    return tmp;
}

big_unsigned operator ^ (const big_unsigned& a, const unsigned int n) {
    big_unsigned tmp(a);
    tmp ^= n;
    return tmp;
}

big_unsigned operator / (const big_unsigned& a, const big_unsigned& b) {
    big_unsigned tmp(a);
    tmp /= b;
    return tmp;
}

