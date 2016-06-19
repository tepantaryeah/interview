#include "ini_parser.h"
#include <vector>
using namespace std;

namespace qh
{

    INIParser::INIParser()
    {

    }
    INIParser::~INIParser()
    {

    }

    bool INIParser::Parse(const std::string& ini_file_path)
    {
        return true;
    }

    bool INIParser::Parse(const char* ini_data, size_t ini_data_len, const std::string& line_seperator = "\n", const std::string& key_value_seperator = "=")
    {
        string sData = "";
        for(int i=0; i<ini_data_len; ）
        {
            sData += ini_data[i];
        }

        vector<string> vData = strSplit(sData, line_seperator);
       
        for (int i = 0; i < vData.size(); ++i)
        {
            vector<string> strSub =  strSplit(vData[i], key_value_seperator);
            if(strSub.size() != 2)
                return false;

            mINI[strSub[0]] = strSub[1];
        }
        /*
        for(int i=0; i<ini_data_len; ）
        {
            string key = "", value = "";
            while(key_value_seperator != ini_data[i])
            {
                key += ini_data[i++];
            }
            i++;
            while(i<ini_data_len || line_seperator != ini_data[i])
            {
                value += ini_data[i++];
            }
            mINI[key]=value;
            if(i<ini_data_len)
                i++;
        }
        */
        return true;
    }

    const std::string& INIParser::Get(const std::string& key, bool* found)
    {
        map<string,string> :: iterator it = mINI.begin();
        for(;it!=mINI.end();it++)
        {
            if(key == it->first)
            {
                if(found != NULL)
                    found = true;
                return it->second;
            }
        }
        if(found != NULL)
            found = false;
        return "";
    }

    const std::string& INIParser::Get(const std::string& section, const std::string& key, bool* found)
    {
        return "";
    }

    std::vector<std::string> strSplit(const  std::string& s, const std::string& delim)
    {
        std::vector<std::string> elems;
        size_t pos = 0;
        size_t len = s.length();
        size_t delim_len = delim.length();
        if (delim_len == 0) return elems;
        while (pos < len)
        {
            int find_pos = s.find(delim, pos);
            if (find_pos < 0)
            {
                elems.push_back(s.substr(pos, len - pos));
                break;
            }
            elems.push_back(s.substr(pos, find_pos - pos));
            pos = find_pos + delim_len;
        }
        return elems;
    }

}
