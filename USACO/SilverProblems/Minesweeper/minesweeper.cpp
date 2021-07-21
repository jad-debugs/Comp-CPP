#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define f first
#define s second
#define pii pair<int, int>

int dx[9] = {1, 1, -1, -1, 1, -1, 0, 0, 0};
int dy[9] = {1, -1, -1, 1, 0, 0, 1, -1, 0};

int cnt = 0, k, n, m; 
bool found = 0;
int grid[31][31] = {0};
vector<bool> mines(31*31);

bool check(int r, int c)
{
    // check if all zeros two above (if possible)
    bool ok = false;
    if (r-2 < 0)
        ok = true;
    if (r-1 >= 0 && c-1 >= 0 && grid[r-1][c-1]-1 > 0) {
        return false;
    }
    if (!ok) {
        ok = 1;
        for (int i = 0; i < m; i++) {
            if (grid[r-2][i] != 0)
                ok = 0;
        }   
    }
    // were not all zeros
    if (!ok)
        return false;
    // check squares (even our own) around to see if any arent supposed to have a mine
    for (int i = 0; i < 9; i++) {
        int r2 = r+dx[i];
        int c2 = c+dy[i];

        if (r2 < 0 || r2 >= n || c2 < 0 || c2 >= m)
            continue;
        if (grid[r2][c2]-1 <= -1)
            return false;
    }

    return true;
}

bool lastCheck()
{
    for (int i = n-1; i >= 0; i--) {
        for (int j = m-1; j >= 0; j--) {
            if (grid[i][j] >= 1)
                return false;
        }
    }
    return true;
}

void go(int pos)
{
    if (found || pos > n*m)
        return;
    if (cnt == k) {
        found = lastCheck();
        if (found) {
            for (int i = 0; i < n*m; i++) {
                if (mines[i]) {
                    cout << i/m+1 << ' ' << i%m+1 << '\n';
                }
            }
        }
        return;
    }
    int r = pos/m;
    int c = pos%m;

    if (check(r, c)) {
        for (int i = 0; i < 9; i++) {
            int r2 = r+dx[i];
            int c2 = c+dy[i];

            if (r2 < 0 || r2 >= n || c2 < 0 || c2 >= m)
                continue;
            grid[r2][c2]--;
        }

        mines[pos] = 1;
        cnt++;
        go(pos+1);

        for (int i = 0; i < 9; i++) {
            int r2 = r+dx[i];
            int c2 = c+dy[i];

            if (r2 < 0 || r2 >= n || c2 < 0 || c2 >= m)
                continue;
            grid[r2][c2]++;
        }

        cnt--;
    }
    mines[pos] = 0;
    go(pos+1);
}

int main()
{
    cin >> n >> m >> k;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
        }
    }

    go(0);

    if (!found) {
        cout << "NO SOLUTION!";
    }

    return 0;
}

