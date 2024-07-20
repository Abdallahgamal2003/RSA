using namespace std;
#include<bits/stdc++.h>
#include<iostream>
#include<string>
#include<vector>
#include<cmath>
//#define AboAlaa ios::sync_with_stdio(false);cout.tie(NULL);cin.tie(NULL);
#define FOR(i, a, b) for(int i = a; i < b; i++)
#define vll vector<long long>
#define vi vector<int>
#define vvi vector<vector<int>>
#define pii pair<int,int>
#define vpl vector<pair<long long,long long>>
#define maxim(a,b) a=std::max(a,b);

using ll = long long;
const ll MOD = 2e15 - 1;

int gcd(ll a, ll b)
{
    if (a < b)
        return gcd(b, a);
    else if (a % b == 0)
        return b;
    else return gcd(b, a % b);
}

ll SquareAndMultiply(ll x, ll H, ll n) {

    long h;
    unsigned long long r;
    int bin[32];
    int i;

    r = x;
    i = 0;

    while (H > 0) {

        if (H % 2 == 0) {
            bin[i] = 0;
        }
        else {
            bin[i] = 1;
        }
        H = H / 2;
        i++;

    }
    i--;
    while (i > 0) {

        r = (r * r) % n;

        if (bin[--i] == 1) {
            r = (r * x) % n;
        }
    }
    return r;
}

bool isPrimeWithFermate(ll n, ll k)
{
    // Corner cases
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;

    // Try k times
    while (k--)
    {
        ll a = 2 + rand() % (n - 2);
        if (gcd(n, a) != 1)
            return false;
        // Fermat's little theorem
        if (SquareAndMultiply(a, n - 1, n) != 1)
            return false;
    }
    return true;
}
ll gcdExtended(ll a, ll b) {
    ll  s0 = 1, t0 = 0,
        s1 = 0, t1 = 1;
    ll r = 0;
    while (r != 1) {
        ll q = b / a; r = b % a;
        ll m = t0 - t1 * q, n = s0 - s1 * q;
        b = a; a = r; t0 = t1; s0 = s1; t1 = m; s1 = n;
    }
    return t1;
}

void asciiToSentence(string str, int len)
{
    int num = 0;
    for (int i = 0; i < len; i++) {
        num = num * 10 + (str[i] - '0');
        if (num >= 32 && num <= 122) {

            char ch = (char)num;
            cout << ch;
            num = 0;
        }
    }
}
int main() {

    cout << "Enter the PlainText\n";
    string msg; getline(cin, msg);
    int siz = msg.size();
    vll ascMsg(siz);
    FOR(i, 0, siz) {
        ascMsg[i] = msg[i];
    }
    cout << "plainText(ASCII) = " << endl;
    FOR(i, 0, siz) {
        cout << msg[i] << " = " << ascMsg[i] << "\t";
    }
    cout << endl;
    ll max = *max_element(ascMsg.begin(), ascMsg.end());
    ll p = max + rand() % MOD;
    ll q = max + rand() % MOD;
    while (!isPrimeWithFermate(p, 100))
        p = max + rand() % MOD;
    while (!isPrimeWithFermate(q, 100))
        q = max + rand() % MOD;
    while (p == q && !isPrimeWithFermate(p, 100))
        p = max + rand() % MOD;


    cout << "P = " << p << " " << "q = " << q << endl;

    ll n = q * p;
    ll Fn = (p - 1) * (q - 1);
    cout << "n = " << n << " " << "Fn = " << Fn << endl;


    ll e = 1 + rand() % Fn;
    while (gcd(e, Fn) != 1) // get public key
        e = 1 + rand() % Fn;

    cout << "Public key = " << e << endl;

    ll d = gcdExtended(e, Fn);// get private key
    if (d < 0)
        d += Fn;
    cout << "Private key = " << d << endl;
    vll Enc;
    FOR(i, 0, siz) {
        Enc.push_back(SquareAndMultiply(ascMsg[i], e, n));
    }
    cout << "cipher text = ";
    FOR(i, 0, siz) {
        cout << Enc[i] << " ";
    }
    cout << endl;

    cout << "Decrybted Message(ASCII)= ";
    vll Dec;
    FOR(i, 0, msg.size())
    {
        ll yp = Enc[i] % p, yq = Enc[i] % q;
        ll dp = d % (p - 1), dq = d % (q - 1);
        ll xp = SquareAndMultiply(yp, dp, p), xq = SquareAndMultiply(yq, dq, q);
        ll cp = gcdExtended(q, p), cq = gcdExtended(p, q);
        if (cp < 0)cp += p;
        if (cq < 0)cq += q;
        ll y = ((q * cp) * xp + (p * cq) * xq) % n;
        cout << y << " ";
        Dec.push_back(y);
    }
    cout << endl << "Decrybted Message(TEXT)= ";
    string str = "";
    FOR(i, 0, siz)str += to_string(Dec[i]);
    asciiToSentence(str, str.size());


}


