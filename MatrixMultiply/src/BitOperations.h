
inline void swap(int& x, int &y) {
    x = x^y;
    y = x^y;
    x = x^y;
}
inline int min(int x, int y) {
    return y ^ ((x^y) & -(x<y));
}
inline int least_significant_bit(int x) {
    return x & (-x);
}
