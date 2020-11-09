**
  * Multiples
  * Divisors
  * Primes
  * Goldbach's conjecture
  * Fundamental Theorem of Arithmetic
  * Factors
  * GCD (Greatest Common Divisor)
  * LCM (Least Common Multiple)
  * Co-primes
  * Factorial
  * Power
  * Modular Arithmetic
  */
 
#include <bits/stdc++.h>
 
using namespace std;
 
typedef long long lld;
 
const int N = 1e6 + 5;
 
vector<int> multiples;
void getMultiples(int n){
    for(int i = n; i <= N; i += n){ /// O(N/n)
        multiples.push_back(i);
    }
}
 
/**
1 * 36
2 * 18
3 * 12
4 * 9
6 * 6
9 * 4
12 * 3
18 * 2
36 * 1
**/
vector<int> divisors;
void getDivisors(int n){
    for(int i = 1; i * i <= n; ++i){    /// O(sqrt(n))
        if(n % i == 0){
            divisors.push_back(i);
            if(i * i != n)
                divisors.push_back(n/i);
        }
    }
}
 
bool is_Prime(int n){
    if(n == 2) return true;
    if(n % 2 == 0 || n == 1) return false;
 
    for(int i = 3; i * i <= n; i += 2){    /// O(sqrt(n))
        if(n % i == 0) return false;
    }
    return true;
}
 
/// sieve of Eratosthenes
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
//0 0 1 1 0 1 0 1 0 0  0  1  0  1  0  0  0  1  0  1  0
//Number of primes in range N ~ (N/ln(N))
 
//bool isPrime[N];
bitset<N> isPrime;
vector<int> primes;
void sieve(){
    /*for(int i = 2; i < N; ++i)
        isPrime[i] = 1;*/
    //fill(isPrime, isPrime + N, 1);
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    for(int i = 2; i < N; ++i){ /// O(N * log(log(N))) ~ O(N)
        if(isPrime[i]){
            primes.push_back(i);
            for(lld j = 1LL*i*i; j < N; j += i){
                isPrime[j] = 0;
            }
        }
    }
}
/*
Sieve complexity analysis:
    N/2 + N/3 + N/5 + N/7 + N/11 .....
    N * (1/2 + 1/3 + 1/5 + 1/7 + 1/11 .......)
    N * log(log(N)) ~ N
*/
 
/// Every even integer > 2 can be represented as the sum of two primes
void Goldbach(int n){
    /*for(int i = 2; i < n; ++i){
        if(isPrime[i] && isPrime[n-i]){
            cout << i << " " << n - i << endl;
            break;
        }
    }
    puts("");*/
    for(int p : primes){
        //if(p > n) break;
        if(isPrime[n-p]){
            cout << p << " " << n - p << endl;
            break;
        }
    }
}
 
/// FTA: every integer > 1 can be uniquely represented as the product of prime numbers
//120 = (2^3) * (3^1) * (5^1)
//2 = (2^1)
//n = (p1^e1) * (p2^e2) * (p3^e3) ..... * (pm^em), where m is the number of prime factors
// Number of divisors = (e1+1) * (e2+1) * (e3+1) .... * (em+1)
// (2^4) * (3^1) * (5^2)
//  2^0     3^0     5^0
//  2^1     3^1     5^1
//  2^2             5^2
//  2^3
//  2^4
vector<pair<int, int>> factors;
void getFactors(int n){
    int tmp = n, num_divisors = 1;
    for(int p = 2; p * p <= n; ++p){
        int e = 0;  // power
        while(tmp % p == 0){
            ++e;
            tmp /= p;
        }
        if(e){
            factors.push_back({p, e});
            num_divisors *= e + 1;
        }
    }
    if(tmp > 1){
        factors.push_back({tmp, 1});
        num_divisors *= 2;
    }
    cout << "number of divisors " << num_divisors << endl;
}
 
//(48, 36)
//48 ==> (2^4) * (3^1) * (5^1)
//36 ==> (2^2) * (3^3)
//
//(12, 8)
//12 ==> (2^2) * (3^1)
//8 ==> (2^3) * (3^0)
 
lld LCM(lld a, lld b){
    return a / __gcd(a, b) * b;
}
 
/// if GCD(a, b) == 1, then a and b are co-primes (or relatively primes)
bool coprimes(lld a, lld b){
    return __gcd(a, b) == 1;
}
 
//n! = n * (n-1) * (n-2) .... * 1
//n! = n * (n-1)!
lld fact[N];
void calcFactorial(){
    fact[0] = 1;
    for(int i = 1; i <= 10; ++i){
        fact[i] = i * fact[i-1];
    }
}
/// Number of trailing zeros in n! ?? (n <= 1e6)
/// Each zero comes from 10 (2 * 5)
/// Number of 2 = n/2 + n/4 + n/8 ...
/// Number of 5 = n/5 + n/25 + n/125 ...
/// ans = min(Number of 2, number of 5)
/// Observation? ans = Number of 5
/// Can you solve it in any base?
 
 
//3^8 ((3^2)^4) = 9^4 = 81^2 = (6561)^1
//3^9 = 3 * 9^4
//ret = 1
//3^9, ret = 3
//9^4, ret = 3
//81^2, ret = 3
//6561^1, ret = 3*6561
 
lld power(lld b, lld po, lld mod){       /// O(log(po))
    lld ret = 1;
    while(po){
        if(po & 1) ret = (ret * b) % mod;
        b = (b * b) % mod;
        po >>= 1;
    }
    return ret;
}
 
 
/**
(a + b) % m = ((a % m) + (b % m)) % m
(a - b) % m = ((a % m) - (b % m) + m) % m
(a * b) % m = ((a % m) * (b % m)) % m
(a ^ b) % m = ((a % m) ^ b) % m           (a and m aren't co-primes)
(a ^ b) % p = (a ^ (b % (p-1))) % p       (a and p are co-primes) // Derived from Fermat's Little Theorem: (a^(p-1)) % p = 1
(a / b) % m != ((a % m) / (b % m)) % m
(a / b) % m = ((a % m) * (mulInv(b) % m)) % m
**/
//1/3 is the multiplicative inverse of 3 (in Real Numbers)
//x * mulInv(x) = 1
//5 is the multiplicative inverse of 3 (mod 7), because (3 * 5) % 7 = 1
//(36 / 3) % 7 = 5
//(36 * 5) % 7 = 5
 
/// If x and mod aren't co-primes, then x has no multiplicative inverse in mod
lld mulInv(lld x, lld mod){			/// O(log(mod))
    return power(x, mod - 2, mod);  // Also derived from Fermat's Little Theorem
}
 
int main()
{
    /*
    getMultiples(3);
    for(int i = 0; i < multiples.size(); ++i){
        cout << multiples[i];
    }
    for(int x : multiples){
        cout << x << " ";
    }
    puts("");
    */
    /*
    getDivisors(36);
    for(int x : divisors){
        cout << x << " ";
    }
    puts("");
    */
    /*
    for(int i = 1; i <= N; ++i){ /// O(N*sqrt(n))
        cout << i << ": ";
        if(is_Prime(i)) cout << "prime\n";
        else cout << "not prime\n";
    }
    */
    /** Note:
          - is_Prime is a function that checks primality in O(sqrt(n))
          - isPrime is a boolean array (or bitset) that checks primality in O(1) after applying sieve
      */
    /*
    sieve();
    for(int i = 0; i < N; ++i){
        if(isPrime[i]) cout << i << " ";
    }
    puts("");
    for(int p : primes){
        cout << p << " ";
    }
    */
    /*
    sieve();
    Goldbach(770);
    */
    /*
    getFactors(120);
    for(pair<int, int> x : factors){
        cout << x.first << " " << x.second << "\n";
    }
    puts("");
    */
    /*
    cout << __gcd(10, 15) << endl;  // builtin
    cout << gcd(10, 15) << endl;    // builtin
    cout << lcm(10, 15) << endl;    // builtin
    cout << LCM(10, 15) << endl;
    cout << coprimes(4, 9) << endl;
    cout << coprimes(10, 15) << endl;
    */
    /*
    calcFactorial();
    cout << fact[5] << endl;
    cout << power(3, 8, 10000000) << endl;
    cout << power(3, 9, 10000000) << endl;
    cout << (36 / 3) % 7 << endl;
    cout << (36 * mulInv(3, 7)) % 7;
    */
    return 0;
}

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 #include <bits/stdc++.h>
 
using namespace std;
 
typedef long long lld;
 
const int N = 1e6 + 5;
 
vector<int> multiples;
void getMultiples(int n){
    for(int i = n; i <= N; i += n){ /// O(N/n)
        multiples.push_back(i);
    }
}
 
/**
1 * 36
2 * 18
3 * 12
4 * 9
6 * 6
9 * 4
12 * 3
18 * 2
36 * 1
**/
vector<int> divisors;
void getDivisors(int n){
    for(int i = 1; i * i <= n; ++i){    /// O(sqrt(n))
        if(n % i == 0){
            divisors.push_back(i);
            if(i * i != n)
                divisors.push_back(n/i);
        }
    }
}
 
bool is_Prime(int n){
    if(n == 2) return true;
    if(n % 2 == 0 || n == 1) return false;
 
    for(int i = 3; i * i <= n; i += 2){    /// O(sqrt(n))
        if(n % i == 0) return false;
    }
    return true;
}
 
/// sieve of Eratosthenes
//0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20
//0 0 1 1 0 1 0 1 0 0  0  1  0  1  0  0  0  1  0  1  0
//Number of primes in range N ~ (N/ln(N))
 
//bool isPrime[N];
bitset<N> isPrime;
vector<int> primes;
void sieve(){
    /*for(int i = 2; i < N; ++i)
        isPrime[i] = 1;*/
    //fill(isPrime, isPrime + N, 1);
    isPrime.set();
    isPrime[0] = isPrime[1] = 0;
    for(int i = 2; i < N; ++i){ /// O(N * log(log(N))) ~ O(N)
        if(isPrime[i]){
            primes.push_back(i);
            for(lld j = 1LL*i*i; j < N; j += i){
                isPrime[j] = 0;
            }
        }
    }
}
/*
Sieve complexity analysis:
    N/2 + N/3 + N/5 + N/7 + N/11 .....
    N * (1/2 + 1/3 + 1/5 + 1/7 + 1/11 .......)
    N * log(log(N)) ~ N
*/
 
/// Every even integer > 2 can be represented as the sum of two primes
void Goldbach(int n){
    /*for(int i = 2; i < n; ++i){
        if(isPrime[i] && isPrime[n-i]){
            cout << i << " " << n - i << endl;
            break;
        }
    }
    puts("");*/
    for(int p : primes){
        //if(p > n) break;
        if(isPrime[n-p]){
            cout << p << " " << n - p << endl;
            break;
        }
    }
}
 
/// FTA: every integer > 1 can be uniquely represented as the product of prime numbers
//120 = (2^3) * (3^1) * (5^1)
//2 = (2^1)
//n = (p1^e1) * (p2^e2) * (p3^e3) ..... * (pm^em), where m is the number of prime factors
// Number of divisors = (e1+1) * (e2+1) * (e3+1) .... * (em+1)
// (2^4) * (3^1) * (5^2)
//  2^0     3^0     5^0
//  2^1     3^1     5^1
//  2^2             5^2
//  2^3
//  2^4
vector<pair<int, int>> factors;
void getFactors(int n){
    int tmp = n, num_divisors = 1;
    for(int p = 2; p * p <= n; ++p){
        int e = 0;  // power
        while(tmp % p == 0){
            ++e;
            tmp /= p;
        }
        if(e){
            factors.push_back({p, e});
            num_divisors *= e + 1;
        }
    }
    if(tmp > 1){
        factors.push_back({tmp, 1});
        num_divisors *= 2;
    }
    cout << "number of divisors " << num_divisors << endl;
}
 
//(48, 36)
//48 ==> (2^4) * (3^1) * (5^1)
//36 ==> (2^2) * (3^3)
//
//(12, 8)
//12 ==> (2^2) * (3^1)
//8 ==> (2^3) * (3^0)
 
lld LCM(lld a, lld b){
    return a / __gcd(a, b) * b;
}
 
/// if GCD(a, b) == 1, then a and b are co-primes (or relatively primes)
bool coprimes(lld a, lld b){
    return __gcd(a, b) == 1;
}
 
//n! = n * (n-1) * (n-2) .... * 1
//n! = n * (n-1)!
lld fact[N];
void calcFactorial(){
    fact[0] = 1;
    for(int i = 1; i <= 10; ++i){
        fact[i] = i * fact[i-1];
    }
}
/// Number of trailing zeros in n! ?? (n <= 1e6)
/// Each zero comes from 10 (2 * 5)
/// Number of 2 = n/2 + n/4 + n/8 ...
/// Number of 5 = n/5 + n/25 + n/125 ...
/// ans = min(Number of 2, number of 5)
/// Observation? ans = Number of 5
/// Can you solve it in any base?
 
 
//3^8 ((3^2)^4) = 9^4 = 81^2 = (6561)^1
//3^9 = 3 * 9^4
//ret = 1
//3^9, ret = 3
//9^4, ret = 3
//81^2, ret = 3
//6561^1, ret = 3*6561
 
lld power(lld b, lld po, lld mod){       /// O(log(po))
    lld ret = 1;
    while(po){
        if(po & 1) ret = (ret * b) % mod;
        b = (b * b) % mod;
        po >>= 1;
    }
    return ret;
}
 
 
/**
(a + b) % m = ((a % m) + (b % m)) % m
(a - b) % m = ((a % m) - (b % m) + m) % m
(a * b) % m = ((a % m) * (b % m)) % m
(a ^ b) % m = ((a % m) ^ b) % m           (a and m aren't co-primes)
(a ^ b) % p = (a ^ (b % (p-1))) % p       (a and p are co-primes) // Derived from Fermat's Little Theorem: (a^(p-1)) % p = 1
(a / b) % m != ((a % m) / (b % m)) % m
(a / b) % m = ((a % m) * (mulInv(b) % m)) % m
**/
//1/3 is the multiplicative inverse of 3 (in Real Numbers)
//x * mulInv(x) = 1
//5 is the multiplicative inverse of 3 (mod 7), because (3 * 5) % 7 = 1
//(36 / 3) % 7 = 5
//(36 * 5) % 7 = 5
 
/// If x and mod aren't co-primes, then x has no multiplicative inverse in mod
lld mulInv(lld x, lld mod){			/// O(log(mod))
    return power(x, mod - 2, mod);  // Also derived from Fermat's Little Theorem
}
 
int main()
{
    /*
    getMultiples(3);
    for(int i = 0; i < multiples.size(); ++i){
        cout << multiples[i];
    }
    for(int x : multiples){
        cout << x << " ";
    }
    puts("");
    */
    /*
    getDivisors(36);
    for(int x : divisors){
        cout << x << " ";
    }
    puts("");
    */
    /*
    for(int i = 1; i <= N; ++i){ /// O(N*sqrt(n))
        cout << i << ": ";
        if(is_Prime(i)) cout << "prime\n";
        else cout << "not prime\n";
    }
    */
    /** Note:
          - is_Prime is a function that checks primality in O(sqrt(n))
          - isPrime is a boolean array (or bitset) that checks primality in O(1) after applying sieve
      */
    /*
    sieve();
    for(int i = 0; i < N; ++i){
        if(isPrime[i]) cout << i << " ";
    }
    puts("");
    for(int p : primes){
        cout << p << " ";
    }
    */
    /*
    sieve();
    Goldbach(770);
    */
    /*
    getFactors(120);
    for(pair<int, int> x : factors){
        cout << x.first << " " << x.second << "\n";
    }
    puts("");
    */
    /*
    cout << __gcd(10, 15) << endl;  // builtin
    cout << gcd(10, 15) << endl;    // builtin
    cout << lcm(10, 15) << endl;    // builtin
    cout << LCM(10, 15) << endl;
    cout << coprimes(4, 9) << endl;
    cout << coprimes(10, 15) << endl;
    */
    /*
    calcFactorial();
    cout << fact[5] << endl;
    cout << power(3, 8, 10000000) << endl;
    cout << power(3, 9, 10000000) << endl;
    cout << (36 / 3) % 7 << endl;
    cout << (36 * mulInv(3, 7)) % 7;
    */
    return 0;
