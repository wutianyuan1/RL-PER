#include <sumtree.h>
#include <algorithm>
#include <cmath>
#include <vector>
#include <random>
#include <iostream>


template <typename DataType>
class PriorityMemory {
public:
    PriorityMemory(size_t capacity_, double alpha_=0.6, double beta_=0.4, double err_=0.01)
    : err(err_), alpha(alpha_), beta(beta_), capacity(capacity_), tree(capacity),
    generater(rand_dev()) {} 

    void add(double error, DataType sample) {
        tree.add(error, sample);
    }

    auto sample(int batch_size) {
        std::vector<DataType> batch(batch_size);
        std::vector<int> idxs(batch_size);
        double segment = tree.total() / (double)batch_size;
        std::vector<double> priorities(batch_size);
        beta = std::min(1.0, beta + 0.001);
        for (int i = 0; i < batch_size; i++) {
            double a = segment * (double)i, b = segment * ((double)i + 1.0);
            std::uniform_real_distribution<double> uniform_dist(a, b);
            double s = uniform_dist(generater);
            auto [idx, p, data_elem] = tree.get(s);
            priorities[i] = p;
            batch[i] = data_elem;
            idxs[i] = idx;
        }
        for (int i = 0; i < batch_size; i++)
            priorities[i] /= tree.total();
        std::vector<double> is_weight(batch_size);
        for (int i = 0; i < batch_size; i++)
            is_weight[i] = std::pow(tree.nentries() * priorities[i], -beta);
        double max_elem = *std::max_element(is_weight.begin(), is_weight.end());
        for (int i = 0; i < batch_size; i++)
            is_weight[i] /= max_elem;
        return std::make_tuple(batch, idxs, is_weight);
    }

    void update(int idx, double error) {
        tree.update(idx, get_priority(error));
    }

    size_t get_capacity() const {
        return capacity;
    }

private:
    double get_priority(double error) {
        return std::pow((std::abs(error) + err), alpha);
    }

private:
    double err, alpha, beta;
    size_t capacity;
    SumTree<DataType> tree;
    std::random_device rand_dev;
    std::mt19937 generater;
};
