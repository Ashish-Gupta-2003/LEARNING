#include <vector>
#include <functional>

template <typename T, typename Operation>
class SegmentTree
{
private:
    std::vector<T> tree;
    size_t n;
    Operation op; // Operation to be performed (e.g., sum, min, max)
    T identity;   // Identity element for the operation

    void build(const std::vector<T> &arr, int node, int start, int end)
    {
        if (start == end)
        {
            tree[node] = arr[start];
            return;
        }

        int mid = start + (end - start) / 2;
        build(arr, 2 * node + 1, start, mid);
        build(arr, 2 * node + 2, mid + 1, end);
        tree[node] = op(tree[2 * node + 1], tree[2 * node + 2]);
    }

    T query(int node, int start, int end, int l, int r)
    {
        if (r < start || l > end)
            return identity;
        if (l <= start && end <= r)
            return tree[node];

        int mid = start + (end - start) / 2;
        T left = query(2 * node + 1, start, mid, l, r);
        T right = query(2 * node + 2, mid + 1, end, l, r);
        return op(left, right);
    }

    void update(int node, int start, int end, int idx, T val)
    {
        if (start == end)
        {
            tree[node] = val;
            return;
        }

        int mid = start + (end - start) / 2;
        if (idx <= mid)
            update(2 * node + 1, start, mid, idx, val);
        else
            update(2 * node + 2, mid + 1, end, idx, val);

        tree[node] = op(tree[2 * node + 1], tree[2 * node + 2]);
    }

public:
    // Constructor
    SegmentTree(const std::vector<T> &arr, Operation operation, T identity_element)
        : n(arr.size()), op(operation), identity(identity_element)
    {
        tree.resize(4 * n);
        build(arr, 0, 0, n - 1);
    }

    // Query the range [l, r]
    T query(int l, int r)
    {
        return query(0, 0, n - 1, l, r);
    }

    // Update value at index idx
    void update(int idx, T val)
    {
        update(0, 0, n - 1, idx, val);
    }
};

// Example usage with different operations
struct Sum
{
    template <typename T>
    T operator()(const T &a, const T &b) const { return a + b; }
};

struct Min
{
    template <typename T>
    T operator()(const T &a, const T &b) const { return std::min(a, b); }
};

struct Max
{
    template <typename T>
    T operator()(const T &a, const T &b) const { return std::max(a, b); }
};

// Example custom operation (GCD)
struct GCD
{
    template <typename T>
    T operator()(const T &a, const T &b) const
    {
        if (b == 0)
            return a;
        return operator()(b, a % b);
    }
};

// Example for sum operation
vector<int> arr = {1, 2, 3, 4, 5};
SegmentTree<int, Sum> sumTree(arr, Sum(), 0); // 0 is identity for sum

// Example for minimum
SegmentTree<int, Min> minTree(arr, Min(), INT_MAX); // INT_MAX is identity for min

// Example for maximum
SegmentTree<int, Max> maxTree(arr, Max(), INT_MIN); // INT_MIN is identity for max

// Example for GCD
SegmentTree<int, GCD> gcdTree(arr, GCD(), 0); // 0 is identity for GCD

// Usage
int sum_range = sumTree.query(1, 3); // Sum of elements from index 1 to 3
int min_range = minTree.query(0, 4); // Minimum element in range 0 to 4
sumTree.update(2, 10);               // Update element at index 2 to 10