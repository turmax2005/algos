    const int C = 1e7+7;
    vi pr, lp(C);
    for (int i = 2; i < C; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.app(i);
        }
        for (int j = 0; j < (int)pr.size() && pr[j] <= lp[i] && pr[j] * i < C; ++j) {
            lp[pr[j] * i] = pr[j];
        }
    }
