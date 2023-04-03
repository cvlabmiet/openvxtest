/*! @file
 *  @brief Demo implementation of Connected-component labeling.
 *  @author Iaroslav Murenkov
 *  @date: 2022-03-30
 */

#include <cstdint>
#include <cwchar>
#include <sys/types.h>

#include <iostream>
#include <algorithm>
#include <vector>
#include <map>

#include "detail/types.h"

#define INSIDE 0
#define TOP 1
#define LEFT 2
#define RIGHT 4
#define BOTTOM 8

uint8_t _is_background(const uint8_t pixel);
uint8_t _get_pos(const vx_image image, const uint32_t ind);
bool _has_neighbors4(const vx_image image, const uint32_t ind);
bool _has_neighbors8(const vx_image image, const uint32_t ind);
bool _has_neighbors(const vx_image image, const uint32_t ind, const uint8_t connectivity);
std::vector<int32_t> _get_neighbors_labels4(const vx_image image, const uint32_t ind);
std::vector<int32_t> _get_neighbors_labels8(const vx_image image, const uint32_t ind);
std::vector<int32_t> _get_neighbors_labels(const vx_image image, const uint32_t ind, const uint8_t connectivity);

class UnionFind {
    public:
        UnionFind(size_t size) : parent(size), rank(size), count(size) {
            for (size_t idx = 0; idx < size; idx++) {
                parent[idx] = idx;
                rank[idx] = 0;
            }
        }

        int32_t find(int32_t x) {
            while (x != parent[x]) {
                parent[x] = parent[parent[x]];
                x = parent[x];
            }
            return x;
        }

        void unite(int32_t x, int32_t y) {
            int32_t root_x = find(x);
            int32_t root_y = find(y);
            if (root_x != root_y) {
                if (rank[root_x] < rank[root_y])
                    parent[root_x] = root_y;
                else if (rank[root_x] > rank[root_y])
                    parent[root_y] = root_x;
                else {
                    parent[root_y] = root_x;
                    rank[root_x]++;
                }
                count--;
            }
        }

        size_t getCount() const { return count; }

    private:
        std::vector<int32_t> parent;
        std::vector<int32_t> rank;
        size_t count;
};


int32_t ref_cclabeling(const vx_image src_image, vx_image labels, const int connectivity)
{
    if (!(connectivity == 4 || connectivity == 8))
        throw std::invalid_argument("Invalid connectivity!");

    const uint32_t src_width = src_image->width;
    const uint32_t src_height = src_image->height;
    const uint32_t labels_width = labels->width;
    const uint32_t labels_height = labels->height;

    if (src_width != labels_width || src_height != labels_height)
        return VX_ERROR_INVALID_PARAMETERS;

    const uint8_t* src_data = static_cast<const uint8_t*>(src_image->data);
    int32_t* labels_data = static_cast<int32_t*>(labels->data);

    UnionFind linked(src_width * src_height / 2 + 1);
    for (size_t ind = 0; ind < labels_width * labels_height; ++ind)
        labels_data[ind] = 0;
    int32_t label = 1;

    // First scan
    for (size_t ind = 0; ind < src_width * src_height; ++ind) {
        if (_is_background(src_data[ind]))
            continue;

        if (!_has_neighbors(src_image, ind, connectivity)) {
            linked.unite(label, label);
            labels_data[ind] = label++;
        } else {
            std::vector<int32_t> neighbors_labels = _get_neighbors_labels(labels, ind, connectivity);
            labels_data[ind] = (neighbors_labels.size() > 0)
                ? *std::min_element(std::begin(neighbors_labels), std::end(neighbors_labels))
                : label;

            for (auto lab : neighbors_labels)
                linked.unite(lab, labels_data[ind]);
        }
    }

    // Second scan
    for (uint32_t ind = 0; ind < src_width * src_height; ++ind)
        if (!_is_background(src_data[ind]))
            labels_data[ind] = linked.find(labels_data[ind]);

    // Normalize labels
    std::map<int32_t, int32_t> map;
    int32_t norm = 1;
    for (size_t ind = 0; ind < src_width * src_height; ++ind)
        if (!_is_background(src_data[ind])) {
            if (auto found = map.find(labels_data[ind]); found == map.end()) {
                map.insert({labels_data[ind], norm});
                labels_data[ind] = norm++;
            } else
                labels_data[ind] = found->second;
        }

    return norm;
}

uint8_t _is_background(const uint8_t pixel) { return !pixel; }

uint8_t _get_pos(const vx_image image, const uint32_t ind)
{
    const uint32_t w = image->width;
    const uint32_t h = image->height;

    uint8_t pos = INSIDE;
    pos |= (ind < w) ? TOP : INSIDE;
    pos |= (ind % w == 0) ? LEFT : INSIDE;
    pos |= ((ind + 1) % w == 0) ? RIGHT : INSIDE;
    pos |= (ind > w * (h - 1) - 1) ? BOTTOM : INSIDE;

    return pos;
}

bool _has_neighbors4(const vx_image image, const uint32_t ind)
{
    const uint32_t w = image->width;
    const uint8_t* data = static_cast<const uint8_t*>(image->data);

    uint8_t pos = _get_pos(image, ind);
    std::vector<uint8_t> neighbors;
    switch (pos) {
        case INSIDE:
        case BOTTOM:
            return (data[ind] == data[ind-w] || data[ind] == data[ind-1]);
        case TOP:
        case TOP | RIGHT:
            return (data[ind] == data[ind-1]);
        case LEFT:
        case BOTTOM | LEFT:
            return (data[ind] == data[ind-w]);
        case RIGHT:
        case BOTTOM | RIGHT:
            return (data[ind] == data[ind-w] || data[ind] == data[ind-1]);
        case TOP | LEFT:
            return 0;

        default:
            throw std::invalid_argument("Unknown position!");
    }
}

bool _has_neighbors8(const vx_image image, const uint32_t ind)
{
    const uint32_t w = image->width;
    const uint8_t* data = static_cast<const uint8_t*>(image->data);

    uint8_t pos = _get_pos(image, ind);
    std::vector<uint8_t> neighbors;
    switch (pos) {
        case INSIDE:
        case BOTTOM:
            return (data[ind] == data[ind-w-1] || data[ind] == data[ind-w] || data[ind] == data[ind-w+1] || data[ind] == data[ind-1]);
        case TOP:
        case TOP | RIGHT:
            return (data[ind] == data[ind-1]);
        case LEFT:
        case BOTTOM | LEFT:
            return (data[ind] == data[ind-w] || data[ind] == data[ind-w+1]);
        case RIGHT:
        case BOTTOM | RIGHT:
            return (data[ind] == data[ind-w-1] || data[ind] == data[ind-w] || data[ind] == data[ind-1]);
        case TOP | LEFT:
            return 0;

        default:
            throw std::invalid_argument("Unknown position!");
    }
}

bool _has_neighbors(const vx_image image, const uint32_t ind, const uint8_t connectivity)
{
    switch (connectivity) {
        case 4:
            return _has_neighbors4(image, ind);
        case 8:
            return _has_neighbors8(image, ind);
        default:
            throw std::invalid_argument("Invalid connectivity!");
    }
}

std::vector<int32_t> _get_neighbors_labels4(const vx_image image, const uint32_t ind)
{
    const uint32_t w = image->width;
    const int32_t* data = static_cast<const int32_t*>(image->data);

    uint8_t pos = _get_pos(image, ind);
    std::vector<int32_t> neighbors_labels;
    switch (pos) {
        case INSIDE:
        case BOTTOM:
            if (data[ind-w])
                neighbors_labels.push_back(data[ind-w]);
            if (data[ind-1])
                neighbors_labels.push_back(data[ind-1]);
            break;
        case TOP:
        case TOP | RIGHT:
            if (data[ind-1])
                neighbors_labels.push_back(data[ind-1]);
            break;
        case LEFT:
        case BOTTOM | LEFT:
            if (data[ind-w])
                neighbors_labels.push_back(data[ind-w]);
            break;
        case RIGHT:
        case BOTTOM | RIGHT:
            if (data[ind-w])
                neighbors_labels.push_back(data[ind-w]);
            if (data[ind-1])
                neighbors_labels.push_back(data[ind-1]);
            break;
        case TOP | LEFT:
            break;

        default:
            throw std::invalid_argument("Unknown position!");
    }

    return neighbors_labels;
}

std::vector<int32_t> _get_neighbors_labels8(const vx_image image, const uint32_t ind)
{
    const uint32_t w = image->width;
    const int32_t* data = static_cast<const int32_t*>(image->data);

    uint8_t pos = _get_pos(image, ind);
    std::vector<int32_t> neighbors_labels;
    switch (pos) {
        case INSIDE:
        case BOTTOM:
            if (data[ind-w-1])
                neighbors_labels.push_back(data[ind-w-1]);
            if (data[ind-w])
                neighbors_labels.push_back(data[ind-w]);
            if (data[ind-w+1])
                neighbors_labels.push_back(data[ind-w+1]);
            if (data[ind-1])
                neighbors_labels.push_back(data[ind-1]);
            break;
        case TOP:
        case TOP | RIGHT:
            if (data[ind-1])
                neighbors_labels.push_back(data[ind-1]);
            break;
        case LEFT:
        case BOTTOM | LEFT:
            if (data[ind-w])
                neighbors_labels.push_back(data[ind-w]);
            if (data[ind-w+1])
                neighbors_labels.push_back(data[ind-w+1]);
            break;
        case RIGHT:
        case BOTTOM | RIGHT:
            if (data[ind-w-1])
                neighbors_labels.push_back(data[ind-w-1]);
            if (data[ind-w])
                neighbors_labels.push_back(data[ind-w]);
            if (data[ind-1])
                neighbors_labels.push_back(data[ind-1]);
            break;
        case TOP | LEFT:
            break;

        default:
            throw std::invalid_argument("Unknown position!");
    }

    return neighbors_labels;
}

std::vector<int32_t> _get_neighbors_labels(const vx_image image, const uint32_t ind, const uint8_t connectivity) {
    switch (connectivity) {
        case 4:
            return _get_neighbors_labels4(image, ind);
        case 8:
            return _get_neighbors_labels8(image, ind);
        default:
            throw std::invalid_argument("Invalid connectivity!");
    }
}
