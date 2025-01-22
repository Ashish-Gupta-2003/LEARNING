vector<vector<int>> ManachersAlgo(string s)
{
    int n = s.length();
    vector<vector<int>> dp(2, vector<int>(n, 0));
    // dp[0] marks for even length palindromes starting from middle of 0th and 1st character and
    // centers at middle of two characters
    // dp[1] marks for odd length palindromes starting from 1 to n th character and
    // centers at the character itself
    // z=0:even
    for (int z = 0, l = 0, r = 0; z < 2; z++, l = 0, r = 0)
        for (int i = 0; i < n; i++)
        {
            if (i < r)
                dp[z][i] = min(r - i + !z, dp[z][l + r - i + !z]);
            int L = i - dp[z][i], R = i + dp[z][i] - !z;
            while (L - 1 >= 0 && R + 1 < n && s[L - 1] == s[R + 1])
                dp[z][i]++, L--, R++;
            if (R > r)
                l = L, r = R;
        }
    return dp;
}
string LPS(string s)
{
    vector<vector<int>> dp = ManachersAlgo(s);
    int n = s.length();
    int len = 0, pos = 0;
    // z=0:even
    for (int z = 0; z < 2; z++)
    {
        for (int i = 0; i < n; i++)
        {
            if (2 * dp[z][i] + z > len)
                len = 2 * dp[z][i] + z, pos = i - dp[z][i];
        }
    }
    return s.substr(pos, len);
}

vector<int> ZAlgo(string s)
{
    int n = s.length();
    vector<int> Z(n, 0);
    for (int i = 1, l = 0, r = 0; i < n; i++)
    {
        if (i < r)
            Z[i] = min(r - i, Z[i - l]);
        while (i + Z[i] < n && s[Z[i]] == s[i + Z[i]])
            Z[i]++;
        if (i + Z[i] > r)
            l = i, r = i + Z[i];
    }
    return Z;
}