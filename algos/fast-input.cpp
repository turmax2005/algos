const int buf_size = 4096;

int getChar() {
  static char buf[buf_size];
  static int len = 0, pos = 0;
  if (pos == len)
    pos = 0, len = fread(buf, 1, buf_size, stdin);
  if (pos == len)
    return -1;
  return buf[pos++];
}

int readChar() {
  while (1) {
    int c = getChar();
    if (c > 32) return c;
  }
}

int readInt() {
  int s = 1, c = readChar(), x = 0;
  if (c == '-')
    s = -1, c = getChar();
  while (isdigit(c))
    x = x * 10 + c - '0', c = getChar();
  return s * x;
}

