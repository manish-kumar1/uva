//
// trie.hpp
//
//  Created on: May 2, 2014
//      Author: Manish Kumar
//
#ifndef TRIE_HPP_
#define TRIE_HPP_

#include <map>
#include <string>
#include <iterator>
#include <stack>
#include <memory>
#include <algorithm>
#include <functional>
#include <tuple>

namespace mystl {

template<typename T, typename Comp, typename Alloc> class trie;

template<typename T, typename Comp = std::less<T>, typename Alloc = std::allocator<T>>
class trie_node final {
public:
  friend class mystl::trie<T, Comp, Alloc>;

  using key_type  = T;
  using comp_type = Comp;
  using size_type = size_t;
  using alloc_type = Alloc;
  using child_ptr = std::unique_ptr<trie_node<T, Comp, Alloc>>;
  using child_type = std::map<T, child_ptr, Comp>;


  void clear() noexcept {
    _M_words = _M_prefix = 0u;
    _M_children.clear();
  }

  size_type _M_words;
  size_type _M_prefix;
  std::map<T, child_ptr, Comp> _M_children;
};


template<typename _Iterator>
struct Trie_iterator_traits : public std::iterator_traits<_Iterator> {

};

template<typename TrieNode, typename Traits = Trie_iterator_traits<TrieNode>>
class trie_iterator : public std::iterator<std::bidirectional_iterator_tag, TrieNode> {
  public:

  typedef trie_iterator<TrieNode, Traits>                           self_type;
  typedef typename TrieNode::key_type                               char_type;
  typedef typename TrieNode::size_type                              size_type;
  typedef std::pair<const std::basic_string<char_type>, size_type>  value_type;
  typedef typename TrieNode::child_type::iterator                   child_iter;
  typedef std::tuple<std::basic_string<char_type>, TrieNode*, child_iter> iter_state;

  friend class trie<char_type, typename TrieNode::comp_type, typename TrieNode::alloc_type>;

  bool operator != (const self_type& __other) const {
    return this->_M_cur_node != __other._M_cur_node;
  }

  value_type operator *() {
    return std::make_pair(_M_prefix, _M_cur_node->_M_words);
  }

  self_type& operator ++ () {
    while (true) {
        if (_M_child_iter != _M_cur_node->_M_children.end()) {
            _M_states.push(std::make_tuple(_M_prefix, _M_cur_node, _M_child_iter));

            _M_prefix += _M_child_iter->first;
            _M_cur_node = _M_child_iter->second.get();
            _M_child_iter = _M_cur_node->_M_children.begin();

            if (_M_cur_node->_M_words > 0) {
                break;
            }
        }
        else if (!_M_states.empty()) {
            auto &_last_state = _M_states.top();
            _M_prefix = std::get<0>(_last_state);
            _M_cur_node = std::get<1>(_last_state);
            _M_child_iter = std::get<2>(_last_state);

            _M_states.pop();
            ++_M_child_iter;
        }
        else {
            _M_prefix = std::basic_string<char_type>();
            _M_cur_node = nullptr;
            break;
        }
    }
    return *this;
  }

  private:
  explicit trie_iterator(const std::basic_string<char_type> __prefix, TrieNode* __node) : 
                            _M_cur_node(__node), _M_prefix(__prefix), _M_states()
  {
    if (_M_cur_node) {
        _M_child_iter = _M_cur_node->_M_children.begin();
        //_M_states.push(std::make_tuple(__prefix, _M_cur_node, _M_child_iter));
    }
  }


  std::stack<iter_state>        _M_states;

  TrieNode*                     _M_cur_node;
  std::basic_string<char_type>  _M_prefix;
  child_iter                    _M_child_iter;
};


template<typename T, typename Comp = std::less<T>, typename Alloc = std::allocator<T>>
class trie {
public:
  using allocator_type = Alloc;
  using key_type = T;
  using key_comp = Comp;
  using size_type = size_t;
  using alloc_type = Alloc;
  using trie_node_type = trie_node<key_type, key_comp, alloc_type>;

  using iterator = trie_iterator<trie_node_type>;

  // constructors
  // default constructor
  explicit trie () : _M_head() {}

  // copy constructor
  //explicit trie (const trie<T,Comp,Alloc>&);



  // movers
  //trie (trie<T,Comp,Alloc>&&);

  // destructors
  virtual ~ trie () noexcept {}

  // assignments
  // copy assignment
  //trie<T,Comp,Alloc>& operator = (const trie<T,Comp,Alloc>&);
  //trie<T,Comp,Alloc>& operator = (trie<T,Comp,Alloc>&&);
  //trie<T,Comp,Alloc>& operator = (std::initializer_list<T>);

  // iterators
  iterator begin() noexcept {
    return trie_iterator<trie_node_type>(std::basic_string<T>(), &_M_head); 
  }
//  const_iterator begin() const noexcept;
//  const_iterator begin() const noexcept;

  iterator end() noexcept {
    return trie_iterator<trie_node_type>(std::basic_string<T>(), nullptr);
  }
  //const_iterator end() const  noexcept;
//  const_iterator cend() const noexcept;

  // capacity
  size_t size()  const  noexcept {
    return _M_head._M_prefix;
  }
  bool empty() const  noexcept {
    return (_M_head._M_prefix == 0u);
  }

  // modifiers
  std::pair<iterator, bool> insert(const std::basic_string<T>& __word) {
    return insert_impl(_M_head, __word, 0);
  }

protected:
  std::pair<iterator, bool> insert_impl(trie_node_type& __node, const std::basic_string<T>& __word, size_t __at) {
    if (__at == __word.size()) {
        ++__node._M_words;
        ++__node._M_prefix;
        return std::make_pair(trie_iterator<trie_node_type>(__word, &__node), false);
    }

    ++__node._M_prefix;

    trie_node_type *_new_node = nullptr;
    bool _new_insert = false;
    auto _it = __node._M_children.find(__word[__at]);
    if (_it == __node._M_children.end()) {
        _new_node = new trie_node_type();
        _new_insert = true;
        __node._M_children[__word[__at]].reset(_new_node);
    }
    else {
        _new_node = _it->second.get();
    }

    auto _ret = insert_impl(*_new_node, __word, ++__at);
    _ret.second |= _new_insert;
    return _ret;
  }


//  std::pair<iterator, bool> insert(const std::basic_string<T>&&);

//  template<typename InputIter>
//  void insert(InputIter first, InputIter last);

//  void insert(std::initializer_list<T>);

//  template<class... Args>
//  std::pair<iterator, bool> emplace(Args&&...);

//  iterator  erase(const_iterator);
//  iterator  erase(const_iterator first, const_iterator last);
//  size_type erase(const std::basic_string<T>&);

  void clear() noexcept {
    _M_head.clear();
  }

  // observers
//  key_comp key_compare() const;

  // operations
//  iterator find(const std::basic_string<T>&);

//  size_type count(const std::basic_string<T>&) const;

  // allocator
//  allocator_type get_allocator() const noexcept;

  private:
  trie_node<key_type, key_comp, allocator_type>   _M_head;
};

} // end namespace mystl

#endif /* TRIE_HPP_ */
