#include <vector>
#include <algorithm>

class BIT
{
private:
    std::vector<int> bit;
    int size;

public:
    // Constructor
    BIT(int n) : size(n)
    {
        bit.resize(n + 1, 0); // 1-based indexing
    }

    // Query sum from index 1 to index
    int query_sum(int index)
    {
        int ans = 0;
        while (index > 0)
        {
            ans += bit[index];
            index -= (index & (-index));
        }
        return ans;
    }

    // Update value at index
    void update(int index, int value)
    {
        while (index <= size)
        {
            bit[index] += value;
            index += (index & (-index));
        }
    }

    // Get range sum from l to r
    int range_query(int l, int r)
    {
        return query_sum(r) - query_sum(l - 1);
    }

    // Count inversions in an array using BIT
    static int count_inversions(std::vector<int> &arr)
    {
        int n = arr.size();
        std::vector<int> temp = arr;

        // Coordinate compression
        std::sort(temp.begin(), temp.end());
        for (int i = 0; i < n; i++)
        {
            arr[i] = std::lower_bound(temp.begin(), temp.end(), arr[i]) - temp.begin() + 1;
        }

        // Count inversions using BIT
        int inv_count = 0;
        BIT bit(n);

        for (int i = n - 1; i >= 0; i--)
        {
            inv_count += bit.query_sum(arr[i] - 1);
            bit.update(arr[i], 1);
        }

        return inv_count;
    }
};
// BIT bit(n);