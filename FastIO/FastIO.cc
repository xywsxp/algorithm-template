#include <cstdio>
#include <string>

namespace FastIO {
const int maxbuff = 1 << 17;
char ibuff[maxbuff], obuff[maxbuff];

int auto_flush = 0;
int optr = 0;

inline void Flush() {
    fwrite(obuff, 1, optr, stdout);
    optr = 0;
}

inline char GetChar() {
    static char *p1 = ibuff, *p2 = ibuff;
    if (p1 == p2) {
        p1 = ibuff;
        p2 = ibuff + fread(ibuff, 1, maxbuff, stdin);
        if (p1 == p2) return -1;
    }
    return *p1++;
}

inline std::string &&GetLine() {
    std::string s;
    for (char c = GetChar(); c != -1; c = GetChar()) {
        if (c == '\n') break;
        s += c;
    }
    return std::move(s);
}

inline void PutChar(char c) {
    if (optr == maxbuff) {
        fwrite(obuff, 1, optr, stdout);
        optr = 0;
    }
    obuff[optr++] = c;
}

void Read(std::string &s) {
    s.clear();
    char c;
    while (c = GetChar(), c <= ' ') {
        if (c == -1) return;
    }
    s += c;
    while (c = GetChar(), c > ' ') {
        s += c;
    }
}

template <typename T>
void Read(T &x) {
    x = 0;
    char c;
    int f = 0;
    for (c = GetChar(); c != '-' && (c < '0' || c > '9'); c = GetChar())
        ;
    if (c == '-')
        f = 1;
    else
        x = c - '0';
    for (c = GetChar(); c >= '0' && c <= '9'; c = GetChar())
        x = x * 10 + c - '0';
    if (f) x = -x;
}

template <typename T, typename... Args>
void Read(T &x, Args &...args) {
    Read(x);
    Read(args...);
    Flush();
}

template <typename T>
void Write(const T &p) {
    int x = p;
    static int dec[20];
    int len = 0;
    if (x == 0) {
        PutChar('0');
        return;
    }
    if (x < 0) {
        PutChar('-');
        x = -x;
    }
    while (x) {
        dec[++len] = x % 10;
        x /= 10;
    }
    while (len) PutChar(dec[len--] + '0');
}

void Write(const std::string &s) {
    for (int i = 0; i < s.size(); ++i) PutChar(s[i]);
}

template <typename T, typename... Args>
void Write(const T &x, const Args &...args) {
    Write(x);
    PutChar(' ');
    Write(args...);
    Flush();
}

}  // namespace FastIO