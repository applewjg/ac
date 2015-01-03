1. 把string数组合并成一个string，并且能复原!

string itostr(int num) {
    string res(4,0);
    int i = 3;
    while (i >= 0 && num != 0) {
        res[i--] = num % 256;
        num = num / 256;
    }
    return res;
}
int strtoi(string str) {
    int res = 0, i = 0;
    while (i < 4) {
        res = res*256 + (int)(unsigned char)str[i++];
    }
    return res;
}
string encode(vector<string> src) {
    if (src.empty()) return "";
    string res;
    for (int i = 0; i < src.size(); ++i) {
        res += itostr(src[i].length()) + src[i];
    }
    return res;
}
vector<string> decode(string src) {
    std::vector<string> res;
    int i = 0;
    while (i + 4 <= src.size()) {
        int num = strtoi(src.substr(i,4));
        string now = src.substr(i+4, num);
        res.push_back(now);
        i += 4 + num;
    }
    return res;
}
int main(int argc, char const *argv[])
{
    cout << "hello world!" << endl;
    vector<string> src;
    src.push_back("hello");
    src.push_back("world");
    src.push_back("hell");
    string res = encode(src);
    vector<string> ans = decode(res);
    for (int i = 0; i < ans.size(); ++i)
        cout << ans[i] << " ";
    cout << endl;
    return 0;
}

2. given k, n, find all lists of k positive integers which sum up to n


void findKNRe(vector<vector<int> > &res, int k, int n, vector<int> &path) {
    if (path.size() == k && n == 0) {
        res.push_back(path);
        return;
    }
    int i = path.empty() ? 1 : path.back();
    for (; i <= n; ++i) {
        path.push_back(i);
        findKNRe(res, k, n - i, path);
        path.pop_back();
    }
}
vector<vector<int> > findKN(int k, int n) {
    vector<vector<int> > res;
    if (k > n) return res;
    if (k == n) {
        res.push_back(vector<int>(n, 1));
        return res;
    }
    vector<int> path;
    findKNRe(res, k, n, path);
    return res;
}
int main(int argc, char const *argv[])
{
    cout << "hello world!" << endl;
    vector<vector<int> > res = findKN(4, 8);
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i].size(); j++) {
            cout << res[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
    return 0;
}

