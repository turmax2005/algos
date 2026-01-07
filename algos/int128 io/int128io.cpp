/// https://codeforces.com/blog/entry/130566
/// by PROG666
using lll = __int128;
using ulll = unsigned __int128;

istream& operator>>(istream& in, __int128& a) {
    string s; in >> s;
    a = 0;
    if (s == "0") return in;
    for (short i = (s[0] == '-'); i < s.size(); i++)
        a = a * 10 + (s[i] - '0');
    if (s[0] == '-') a *= -1;
    return in;
}
istream& operator>>(istream& in, unsigned __int128& a) {
    string s; in >> s;
    a = 0;
    if (s == "0") return in;
    for (short i = 0; i < s.size(); i++)
        a = a * 10 + (s[i] - '0');
    return in;
}
ostream& operator<<(ostream& out, __int128 a) {
    __int128 b = a;
    if (b < 0)out << '-', b *= -1;
    string s;
    do {
        s.push_back(b % 10 + '0');
        b /= 10;
    } while (b > 0);
    for (int i = s.size() - 1; i >= 0; i--)
        out << s[i];
    return out;
}
ostream& operator<<(ostream& out, unsigned __int128 a) {
    unsigned __int128 b = a;
    string s;
    do {
        s.push_back(b % 10 + '0');
        b /= 10;
    } while (b > 0);
    for (int i = s.size() - 1; i >= 0; i--)
        out << s[i];
    return out;
}

string to_string(__int128 a){
    string s;
    bool bo = 0;
    if (a < 0) a *= -1, s.push_back('-'), bo = 1;
    do {
        s.push_back(a % 10 + '0');
        a /= 10;
    } while(a > 0);
    for(int i = 0; i < (s.size() - bo) / 2; i++)
        swap(s[i + bo], s[s.size() - i - 1]);
    return s;
}
string to_string(unsigned __int128 a){
    string s;
    do {
        s.push_back(a % 10 + '0');
        a /= 10;
    } while(a > 0);
    for(int i = 0; i < s.size() / 2; i++)
        swap(s[i], s[s.size() - i - 1]);
    return s;
}
__int128 stolll(string s){
    __int128 a = 0;
    if(s == "")return a;
    for (short i = (s[0] == '-'); i < s.size(); i++)
        a = a * 10 + (s[i] - '0');
    if (s[0] == '-') a *= -1;
    return a;
}
unsigned __int128 stoulll(string s){
    unsigned __int128 a = 0;
    if(s == "")return a;
    for (short i = 0; i < s.size(); i++)
        a = a * 10 + (s[i] - '0');
    return a;
}
