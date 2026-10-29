#include "project/heap.h"

#include <algorithm>
#include <stdexcept>

MaxHeap::MaxHeap() = default;

MaxHeap::MaxHeap(const std::vector<int>& values) {
    buildHeap(values);
}

bool MaxHeap::empty() const noexcept {
    return data_.empty();
}

std::size_t MaxHeap::size() const noexcept {
    return data_.size();
}

int MaxHeap::top() const {
    if (empty()) {
        throw std::logic_error("Heap is empty");
    }
    return data_.front();
}

bool MaxHeap::contains(int value) const {
    for (int item : data_) {
        if (item == value) {
            return true;
        }
    }
    return false;
}

void MaxHeap::push(int value) {
    data_.push_back(value);
    heapifyUp(data_.size() - 1);
}

int MaxHeap::pop() {
    if (empty()) throw std::logic_error("Heap is empty");
    int maximum = data_.front();
    data_.front() = data_.back();
    data_.pop_back();
    if (!empty()) heapifyDown(0);
    return maximum;
}

void MaxHeap::buildHeap(const std::vector<int>& values) {
    data_ = values;
    // Leaves already satisfy the invariant. Repair internal nodes bottom-up.
    for (std::size_t i = data_.size() / 2; i > 0; --i) heapifyDown(i - 1);
}

std::vector<int> MaxHeap::heapSort() {
    // Sort a copy so the original remains a usable max-heap.
    MaxHeap remaining(*this);
    std::vector<int> sorted(size());
    for (std::size_t i = sorted.size(); i > 0; --i) sorted[i - 1] = remaining.pop();
    return sorted;
}

std::vector<int> MaxHeap::toVector() const {
    return data_;
}

std::size_t MaxHeap::parentIndex(std::size_t index) {
    if (index == 0) {
        return 0;
    }
    return (index - 1) / 2;
}

std::size_t MaxHeap::leftChildIndex(std::size_t index) {
    return (2 * index) + 1;
}

std::size_t MaxHeap::rightChildIndex(std::size_t index) {
    return (2 * index) + 2;
}

void MaxHeap::heapifyUp(std::size_t index) {
    while (index > 0) {
        auto parent = parentIndex(index);
        if (data_[parent] >= data_[index]) break;
        swap(data_[parent], data_[index]);
        index = parent;
    }
}

void MaxHeap::heapifyDown(std::size_t index) {
    // Only internal nodes have children; this also avoids unsigned underflow.
    while (index < data_.size() / 2) {
        auto child = leftChildIndex(index);
        auto right = rightChildIndex(index);
        if (right < data_.size() && data_[right] > data_[child]) child = right;
        if (data_[index] >= data_[child]) break;
        swap(data_[index], data_[child]);
        index = child;
    }
}

void MaxHeap::swap(int& a, int& b) {
    std::swap(a, b);
}

bool MaxHeap::isValidHeap() const {
    for (std::size_t i = 1; i < data_.size(); ++i) {
        if (data_[parentIndex(i)] < data_[i]) {
            return false;
        }
    }
    return true;
}
