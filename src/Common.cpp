#include<Common.h>
using namespace akcemu;
using namespace std;
vector<char> akcemu::readBin(const char* path){
    fstream fileStream(path,ios::in|ios::binary|ios::ate);
    if(fileStream.is_open()){
        int size=fileStream.tellg();
        vector<char> data;
        data.resize(size);
        fileStream.seekg(0,ios::beg);
        fileStream.read(data.data(),size);
        fileStream.flush();
        fileStream.close();
        return data;
    }else{
        LOG.error("Failed to open file at",false);
        LOG.error(path);
    }
}