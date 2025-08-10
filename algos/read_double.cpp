double read_double() {
    string s;
    cin >> s;
    double sgn = 1, p10 = 0, num = 0;
    for (char c : s) {
        if (c == '-') {
            sgn = -1;
        } else if (c == '.') {
            p10 = 1;
        } else {
            p10 *= 10;
            num = (num * 10 + c - '0');
        }
    }
    if (p10 < 0.5) p10 = 1;
    return sgn * num / p10;
}
