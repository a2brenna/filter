#ifndef __MEDIAN_FILTER_H__
#define __MEDIAN_FILTER_H__

#include <deque>
#include <vector>
#include <algorithm>
#include <cassert>

template <typename T>
class Median_Filter{

    public:
        Median_Filter(const size_t &window_size){
            assert(window_size > 1);
            _window_size = window_size;
        }
        void append(const T &new_val){
            _data.push_back(new_val);
            while(_data.size() < _window_size){
                _data.push_back(new_val);
            }
            while(_data.size() > _window_size){
                _data.pop_front();
            }
        }
        T operator()() const{
            std::vector<T> data(_data.begin(), _data.end());
            std::sort(data.begin(), data.end());
            return data[data.size() / 2];
        }

    private:
        size_t _window_size;
        std::deque<T> _data;

};

#endif
