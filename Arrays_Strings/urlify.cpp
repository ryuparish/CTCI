#include <string>
#include <iostream>

void urlify(std::string& url2b){
    for(int i = 0; i < url2b.length(); ++i){
        if(url2b[i] == ' '){
            url2b.insert(i, "%20");
            url2b.erase(i+3,1);
        }
    }
}

int main(){
    std::string url2b;
    std::getline (std::cin, url2b);
    urlify(url2b);
    std::cout << url2b << "\n";
    return 0;
}
