#pragma once
#include <vector>
#include <tuple>

template <typename DataType>
class SumTree {
public:
    SumTree(size_t capacity_) : capacity(capacity_), write_count(0) {
        tree.resize(2*capacity - 1);
        data.resize(capacity);
        n_entries = 0;
    }

    double total() {
        return tree[0];
    }

    inline void add(double p, DataType data_elem) {
        int idx = write_count + capacity - 1;
        data[write_count] = data_elem;
        update(idx, p);
        write_count++;
        if (write_count >= (int)capacity)
            write_count = 0;
        if (n_entries < (int)capacity)
            n_entries++;
    }

    inline void update(int idx, double p) {
        double change = p - tree[idx];
        tree[idx] = p;
        propagate(idx, change);
    }

    inline auto get(double s) {
        int idx = retrieve(0, s);
        size_t data_idx = idx - capacity + 1;
        return std::make_tuple(idx, tree[idx], data[data_idx]);
    }

    int nentries() const {
        return n_entries;
    }

private:
    void propagate(int idx, double change) {
        int parent = (idx - 1) / 2;
        tree[parent] += change;
        if (parent != 0)
            propagate(parent, change);
    }

    int retrieve(int idx, double s) {
        int left = 2*idx + 1;
        int right = left + 1;
        if (left >= (int)tree.size())
            return idx;
        if (s <= tree[left])
            return retrieve(left, s);
        else
            return retrieve(right, s - tree[left]);
    }

private:
    size_t capacity;
    int n_entries;
    int write_count;
    std::vector<double> tree;
    std::vector<DataType> data;
};
