#include <bits/stdc++.h>
using namespace std;
vector<string> extractLinksFromFile() {
    ifstream file("1.html");
    vector<string> links;
    if (!file.is_open()) {
        puts ("File error");
        exit(2);
    }
    string content((istreambuf_iterator<char>(file)),
                        (istreambuf_iterator<char>()));
    file.close();
    regex link_regex(R"(<a\s+href="/problemset/problem/(\d+)/(\w+(?:\d+)?)/?">)"); // 定义正则表达式
    smatch matches; 
    while (regex_search(content, matches, link_regex)) {
        string link = matches.str(1) + matches.str(2);
        if (links.size() == 0 || link != links.back()) links.push_back(link);
        content = matches.suffix().str();
    }
    return links;
}
string generateURL(const string& problemCode) {
    string baseURL = "cd cf/contest/";
    size_t pos = problemCode.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    
    if (pos != string::npos) {
        string problemNumber = problemCode.substr(0, pos);
        string problemLetter = problemCode.substr(pos);
        if ('A' <= problemLetter[0] && problemLetter[0] <= 'Z') problemLetter[0] += 'a' - 'A'; 
        return baseURL + problemNumber + "/" + problemLetter + "/  && bash";
    }

    return "";
}

string GenerateURL(const string& problemCode) {
    string baseURL = "code cf/contest/";
    size_t pos = problemCode.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    
    if (pos != string::npos) {
        string problemNumber = problemCode.substr(0, pos);
        string problemLetter = problemCode.substr(pos);
        if ('A' <= problemLetter[0] && problemLetter[0] <= 'Z') problemLetter[0] += 'a' - 'A'; 
        return baseURL + problemNumber + "/" + problemLetter + "/" + problemLetter + ".cpp";
    }

    return "";
}
int main() {
    puts ("Connecting...");
    puts ("Crawling...");
    system("wget --header=\"Cookie: 39ce7=****; 70a7c28f3de=*****; JSESSIONID=******\" -qO- \"https://codeforces.com/problemset/page/1?tags=****-****\" > 1.html");
    puts("Crawl succeed.");
    
    vector <string> s = extractLinksFromFile();
    mt19937_64 Rand(random_device{}());
    string str = s[Rand() % s.size()];

    cout << "Problem Id:" << str << '\n';
    string cmd = "cf parse " + str;
    cout << cmd << '\n';
    system(cmd.c_str());
    cmd = GenerateURL(str);
    cout << cmd << '\n';
    system(cmd.c_str());
    cout << "rm 1.html" << '\n';
    system("rm 1.html");

    cmd = generateURL(str);
    cout << cmd << '\n';
    system(cmd.c_str());
    return 0;
}
