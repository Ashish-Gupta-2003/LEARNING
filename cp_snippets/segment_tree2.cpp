#include <vector>
#include <algorithm>
using i64 = long long;

template <class Info>
struct SegmentTree
{
    int n;
    std::vector<Info> tree;

    SegmentTree() : n(0) {}

    // Initialize with size and default value
    SegmentTree(int n_, Info v_ = Info())
    {
        init(n_, v_);
    }

    // Initialize with vector
    template <class T>
    SegmentTree(const std::vector<T> &init_)
    {
        init(init_);
    }

    void init(int n_, Info v_ = Info())
    {
        init(std::vector<Info>(n_, v_));
    }

    template <class T>
    void init(const std::vector<T> &init_)
    {
        n = init_.size();
        tree.assign(4 * n, Info());
        build(1, 0, n - 1, init_);
    }

    void build(int node, int start, int end, const std::vector<Info> &arr)
    {
        if (start == end)
        {
            tree[node] = arr[start];
            return;
        }
        int mid = (start + end) >> 1;
        build(2 * node, start, mid, arr);
        build(2 * node + 1, mid + 1, end, arr);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    void update(int node, int start, int end, int idx, const Info &val)
    {
        if (start == end)
        {
            tree[node] = val;
            return;
        }
        int mid = (start + end) >> 1;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        tree[node] = tree[2 * node] + tree[2 * node + 1];
    }

    Info query(int node, int start, int end, int l, int r)
    {
        if (start > r || end < l)
            return Info();
        if (l <= start && end <= r)
            return tree[node];
        int mid = (start + end) >> 1;
        return query(2 * node, start, mid, l, r) +
               query(2 * node + 1, mid + 1, end, l, r);
    }

    void modify(int idx, const Info &val)
    {
        update(1, 0, n - 1, idx, val);
    }

    Info rangeQuery(int l, int r)
    {
        return query(1, 0, n - 1, l, r);
    }
};

// Example of complex Info structure for various operations
struct ComplexInfo
{
    static const i64 INF = 1e18;
    i64 sum;  // sum of elements
    i64 pref; // maximum prefix sum
    i64 suff; // maximum suffix sum
    i64 ans;  // maximum subarray sum
    i64 len;  // length of segment

    ComplexInfo() : sum(0), pref(-INF), suff(-INF), ans(-INF), len(0) {}

    ComplexInfo(i64 x) : sum(x), pref(x), suff(x), ans(x), len(1) {}

    // Combine two segments
    friend ComplexInfo operator+(const ComplexInfo &a, const ComplexInfo &b)
    {
        ComplexInfo res;
        res.sum = a.sum + b.sum;
        res.pref = std::max(a.pref, a.sum + b.pref);
        res.suff = std::max(b.suff, b.sum + a.suff);
        res.ans = std::max({a.ans, b.ans, a.suff + b.pref});
        res.len = a.len + b.len;
        return res;
    }
};

// Example of your provided Info structure
struct CustomInfo
{
    static const i64 INF = 1e18;
    i64 len;
    i64 maxl;
    i64 maxr;
    i64 minl;
    i64 minr;
    i64 ans;

    CustomInfo() : len(0), maxl(-INF), maxr(-INF), minl(INF), minr(INF), ans(0) {}

    CustomInfo(int x, int i) : len(1), maxl(x + i), maxr(x - i),
                               minl(x - i), minr(x + i), ans(0) {}

    friend CustomInfo operator+(const CustomInfo &a, const CustomInfo &b)
    {
        CustomInfo c;
        c.len = a.len + b.len;
        c.maxl = std::max(a.maxl, b.maxl);
        c.maxr = std::max(a.maxr, b.maxr);
        c.minl = std::min(a.minl, b.minl);
        c.minr = std::min(a.minr, b.minr);
        c.ans = std::max({a.ans, b.ans, a.maxl - b.minr, b.maxr - a.minl});
        return c;
    }
};

// Using ComplexInfo (Maximum Subarray Sum)
vector<i64> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
SegmentTree<ComplexInfo> maxSubarrayTree(n);
for (int i = 0; i < n; i++)
{
    maxSubarrayTree.modify(i, ComplexInfo(arr[i]));
}
i64 maxSubarraySum = maxSubarrayTree.rangeQuery(0, n - 1).ans;

// Using CustomInfo (Your example)
SegmentTree<CustomInfo> customTree(n);
for (int i = 0; i < n; i++)
{
    customTree.modify(i, CustomInfo(arr[i], i));
}
i64 result = customTree.rangeQuery(0, n - 1).ans;

// explanation of info:
/*Let's start with ComplexInfo which is designed to solve the Maximum Subarray Sum problem:

    Structure Fields :

    cpp

    static const i64 INF = 1e18; // Large value for initialization
i64 sum;                         // Total sum of the segment
i64 pref;                        // Maximum prefix sum (sum of elements from start)
i64 suff;                        // Maximum suffix sum (sum of elements from end)
i64 ans;                         // Maximum subarray sum in this segment
i64 len;                         // Length of the segment

Constructors :

    cpp

    // Default constructor - used for empty/invalid segments
    ComplexInfo() : sum(0), pref(-INF), suff(-INF), ans(-INF), len(0)
{
}

// Single element constructor
ComplexInfo(i64 x) : sum(x), pref(x), suff(x), ans(x), len(1) {}

Merge Operation :

    cpp

    friend ComplexInfo
    operator+(const ComplexInfo &a, const ComplexInfo &b)
{
    ComplexInfo res;
    // Total sum is simple addition
    res.sum = a.sum + b.sum;

    // Maximum prefix can be either a's prefix or a's total sum plus b's prefix
    res.pref = std::max(a.pref, a.sum + b.pref);

    // Maximum suffix can be either b's suffix or b's total sum plus a's suffix
    res.suff = std::max(b.suff, b.sum + a.suff);

    // Maximum subarray sum can be:
    // 1. Maximum subarray in left segment (a.ans)
    // 2. Maximum subarray in right segment (b.ans)
    // 3. Maximum suffix of left + Maximum prefix of right (a.suff + b.pref)
    res.ans = std::max({a.ans, b.ans, a.suff + b.pref});

    res.len = a.len + b.len;
    return res;
}

Now for CustomInfo, which appears to be designed for a problem involving positions and values:

    Structure Fields:

cpp

static const i64 INF = 1e18;  // Large value for initialization
i64 len;                      // Length of segment
i64 maxl;                     // Maximum of (value + position)
i64 maxr;                     // Maximum of (value - position)
i64 minl;                     // Minimum of (value - position)
i64 minr;                     // Minimum of (value + position)
i64 ans;                      // Answer for this segment

Constructors :

    cpp

    // Default constructor - used for empty/invalid segments
    CustomInfo() : len(0), maxl(-INF), maxr(-INF), minl(INF), minr(INF), ans(0)
{
}

// Constructor for a single element at position i with value x
CustomInfo(int x, int i) : len(1),
                           maxl(x + i), // Maximum of value + position
                           maxr(x - i), // Maximum of value - position
                           minl(x - i), // Minimum of value - position
                           minr(x + i), // Minimum of value + position
                           ans(0)
{
}

Merge Operation :

    cpp

    friend CustomInfo
    operator+(const CustomInfo &a, const CustomInfo &b)
{
    CustomInfo c;
    c.len = a.len + b.len; // Total length is sum of lengths

    // Take maximum/minimum of respective values
    c.maxl = std::max(a.maxl, b.maxl); // Max of (value + position)
    c.maxr = std::max(a.maxr, b.maxr); // Max of (value - position)
    c.minl = std::min(a.minl, b.minl); // Min of (value - position)
    c.minr = std::min(a.minr, b.minr); // Min of (value + position)

    // Answer is maximum of:
    // 1. Best answer in left segment (a.ans)
    // 2. Best answer in right segment (b.ans)
    // 3. Best possible combining left and right:
    //    - maxl from left - minr from right (a.maxl - b.minr)
    //    - maxr from right - minl from left (b.maxr - a.minl)
    c.ans = std::max({a.ans, b.ans, a.maxl - b.minr, b.maxr - a.minl});
    return c;
}

Key Points:

    Both structures implement a way to combine two segments (operator+)
    They maintain necessary information to compute their respective answers
    The merge operations ensure that combining any two segments produces correct results
    They handle both single elements and ranges properly

Example usage for ComplexInfo:

cpp

// Array: [-2, 1, -3, 4]
// Single elements:
ComplexInfo e1(-2);  // sum=-2, pref=-2, suff=-2, ans=-2
ComplexInfo e2(1);   // sum=1,  pref=1,  suff=1,  ans=1

// Combining them:
ComplexInfo combined = e1 + e2;
// sum = -1 (total sum)
// pref = 1 (max of -2 or -2+1)
// suff = 1 (max of 1 or 1-2)
// ans = 1 (max of {-2, 1, -2+1})

Would you like me to explain any specific part in more detail or show how these structures handle different example cases ? Claude can make mistakes.Please double - check responses.
*/