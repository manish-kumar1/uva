#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <type_traits>
#include <sstream>
#include <exception>


namespace mylib {

class big_unsigned;

big_unsigned operator + (const big_unsigned& a, const big_unsigned& b);
big_unsigned operator - (const big_unsigned& a, const big_unsigned& b);

// storage class
template<typename Container>
class bignum_storage {
public:
    bignum_storage(size_t __n) : _M_blk(__n) {}

private:
    Container   _M_blk;
};


// bignumber traits
template<typename T>
class bignum_traits {
public:
    typedef T  digit_type;
    typedef T* pointer;

    static digit_type sum(const digit_type a, const digit_type b) { // a+b
        return a + b;
    }
    static digit_type sub(const digit_type a, const digit_type b) {   // a-b
        return a - b;
    }
    static digit_type to_digit_type(const int x) {
        return (x);
    }
};


// interface to underlying digit storage
class bignum_base {
public:
    typedef bignum_traits<short>  traits_type;

    typedef traits_type::digit_type digit_type;
    typedef digit_type     base;
    typedef std::vector<digit_type> container_type;

    typedef std::vector<digit_type>::iterator iterator;
    typedef std::vector<digit_type>::const_iterator const_iterator;
    typedef std::vector<digit_type>::reverse_iterator reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    bignum_base(digit_type __base, 
                const std::vector<digit_type>& __digits = std::vector<digit_type>()) : 
                _M_base(__base), _M_blk(__digits) {
    }

    size_t size() const { return _M_blk.size(); }
    iterator begin() { return iterator(_M_blk.begin());  }
    const_iterator begin() const { return const_iterator(_M_blk.cbegin()); }
    const_iterator cbegin() const { return const_iterator(_M_blk.cbegin()); }
    iterator end() { return iterator(_M_blk.end()); }
    const_iterator end() const { return const_iterator(_M_blk.cend()); }
    const_iterator cend() { return const_iterator(_M_blk.cend()); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(_M_blk.end()); }
    const_reverse_iterator rend() const { return const_reverse_iterator(_M_blk.begin()); }
    bignum_base& prune_zeros() {
        while ((_M_blk.size() > 1) && (_M_blk.back() == digit_type(0))) 
            _M_blk.pop_back();

        return *this;
    }

protected:
    base _M_base;   // base in which number is represented
    std::vector<digit_type> _M_blk;
};


// Big unsigned 
class big_unsigned : public bignum_base {
public:
    // modifiers
    big_unsigned() : bignum_base(10) {_M_blk.push_back(0);}

    big_unsigned(unsigned long long __rhs) : bignum_base(10) {
        do {
            _M_blk.push_back(__rhs % _M_base);
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

    template<typename InputIter>
    explicit big_unsigned(InputIter __start, InputIter __end) : bignum_base(10) {
        std::transform(__start, __end, std::inserter(_M_blk, _M_blk.begin()), traits_type::to_digit_type);
        prune_zeros();
    }

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

    big_unsigned& operator -= (const big_unsigned& __rhs) {
        if ((*this) < __rhs) throw std::logic_error("negative");

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
 

    big_unsigned& operator *= (const big_unsigned& __rhs) {
        return (*this) = karatsuba(*this, __rhs);
    }

protected:
    template<typename InputIter>
    InputIter init_from(InputIter __start, InputIter __end) {
        if (!_M_blk.empty()) _M_blk.clear();
        std::transform(__start, __end, std::inserter(_M_blk, _M_blk.begin()), traits_type::to_digit_type);
        return __start;
    }

    template<typename T>
    big_unsigned& append(T __digit, size_t __knt) {
        big_unsigned::container_type _new_blk(__knt, __digit);
        _new_blk.insert(_new_blk.end(), _M_blk.begin(), _M_blk.end());
        std::swap(_M_blk, _new_blk);
        return *this;
    }

    big_unsigned karatsuba(const big_unsigned& a, const big_unsigned& b) {
        size_t _a_size = a.size(), _b_size = b.size();
        size_t M = std::max(_a_size, _b_size);
        if (M <= 8) { // base case
            unsigned long long x = a.convert_to<unsigned long long>(),
                               y = b.convert_to<unsigned long long>();
            return big_unsigned(x*y);
        }

        size_t M2 = M - M/2;
        big_unsigned low1, high1, low2, high2;
        if (M2 <= _a_size) {
            low1.init_from(a.begin(), next(a.begin(), M2));
            high1.init_from(next(a.begin(), M2), a.end());
        }
        else {
            low1.init_from(a.begin(), next(a.begin(), _a_size));
        }

        if (M2 <= _b_size) {
            low2.init_from(b.begin(), next(b.begin(), M2)); 
            high2.init_from(next(b.begin(), M2), b.end());
        }
        else {
            low2.init_from(b.begin(), next(b.begin(), _b_size));
        }

        
        big_unsigned z0 = karatsuba(low1, low2);
        big_unsigned z2 = karatsuba(high1, high2);
        big_unsigned z1 = karatsuba(low1+high1, low2+high2);

        return z2.append(0, 2*M2) + (z1 - (z2+z0)).append(0, M2) + z0;
    }

public:
    
    template<typename T>
    T convert_to() const {
        T _tmp;
        std::stringstream _ss;
        std::copy(rbegin(), rend(), std::ostream_iterator<traits_type::digit_type>(_ss, ""));
        _ss >> _tmp;
        return _tmp;
    }

    std::string convert_to() const {
        std::ostringstream _oss;
        std::copy(rbegin(), rend(), std::ostream_iterator<traits_type::digit_type>(_oss,""));
        return _oss.str();
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
        std::copy(__rhs.rbegin(), __rhs.rend(), std::ostream_iterator<digit_type>(__oss, ""));
        return __oss;
    }

    friend std::istream& operator >> (std::istream& __iss, big_unsigned& __rhs) {
        std::string _in;
        __iss >> _in;
        __rhs = big_unsigned(_in);

        return __iss;
    }
};

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

}
