// # prime_factorisation_stored_in_a_map(int,int)_in_O(sqrt(n))
map<int,int> primeFactorsiation(int n)
{
    map<int,int> m;
    while (n % 2 == 0)
    {
        m[2]++;
        n = n / 2;
    }
    for (int i = 3; i <= sqrt(n); i = i + 2)
    {
        while (n % i == 0)
        {
            m[i]++;
            n = n / i;
        }
    }
    if (n > 2)
        m[n]++;
        return m;
}
// marking all prime numbers upto n in a vector of bools
// in O(nloglog(sqrt(n)) + n) time
vector<bool> mysieve(ll n){
    vector<bool>arr(n+1,true);
    arr[1]=false;
    for(int i=2;i*i<=n;i++){
        if(arr[i]==true){
            for(int j=i*i;j<=n;j+=i){
                arr[j]=false;
            }
        }
    }
    return arr;
}
// marking all primes upto n and storing prime numbers in a vector
std::vector<int> minp, primes;
// Linear sieve -> O(n)
void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}

ll binMultiply(ll a, ll b, ll m)
{
    // will be useful if MOD=1e18
    // will convert b into binary form to perform multiplication
    // operation in O(log(n)) time instead of O(n) time
    if (a > b)
    {
        swap(a, b);
    }
    ll ans = 0, binsum = b;
    while (b)
    {
        if (b & 1)
        {
            ans = (ans + a) % m;
        }
        a = (a + a) % m;
        b >>= 1;
    }
    return ans;
}
// to calculate (a^b^c)%m use binExpIter(a,binExpIter(b,c,phi(m)),m), where phi(m)= m-1 if m is prime
ll binExpIter(ll a, int b, ll m)
{
    // now this function takes O(log^2(n)) time due to binMultiply fxn
    // which takes O(log(n)) time
    a %= m;
    int ans = 1;
    while (b > 0) // O(log(b))
    {
        if (b & 1)
        {
            ans = binMultiply(ans, a, m);
        }
        a = binMultiply(a, a, m);
        b = b >> 1;
    }
    return ans;
}
// Function for extended Euclidean Algorithm
int gcdExtended(ll a, ll b, int* x, int* y){
    // Base Case
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    // To store results of recursive call
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
 
    // Update x and y using results of recursive
    // call
    *x = y1 - (b / a) * x1;
    *y = x1; 
    return gcd;
}
 
ll modInverse(ll A, int M){         //pass MOD for M usually
    int x, y;
    ll g = gcdExtended(A, M, &x, &y);
    if (g != 1){
//      cout << "Inverse doesn't exist";
        return -1;
    }else {
//      m is added to handle negative x
        ll res = (x % M + M) % M;
//      cout << "Modular multiplicative inverse is " << res;
        return res;
    }
}
int fact[N], invfact[N],inv[N];

ll nCr(int n, int r)
{
    if (r > n)
        return 0;
    return fact[n] * invfact[r] % MOD * invfact[n - r] % MOD;
}
    // use this in main function for precomputation
    // fact[0] =fact[1]= 1;
    // invfact[0] =invfact[1]= 1;
    // inv[1]=1;
    // repl(i, 2, N)
    // {
    //     fact[i] = fact[i - 1] * i % MOD;
    //     inv[i] = MOD-1LL*(MOD/i)*inv[MOD%i]%MOD;
    //     invfact[i] = 1LL*invfact[i - 1] * inv[i] % MOD;
    // }