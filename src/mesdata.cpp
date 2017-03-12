#include "mesdata.h"

Log objLog;

std::vector<std::string> split(const  std::string& s, const std::string& delim)  
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


MesData::MesData()
{
	iter = Params.begin();
}

bool MesData::SetClientFd(int clientfd)
{
	ClientFd = clientfd;
}

bool MesData::SetMesId(string mesid)
{
	MesId = mesid;
}

bool MesData::SetUserId(string userid)
{
	UserId = userid;
}

bool MesData::SetLbmId(string lbmid)
{
	LbmId = lbmid;
}

bool MesData::SetParams(string params)
{
	int i;
	vector<string> maplist;	
	vector<string> kv;
	maplist = split(params, ",");
	for(i = 0;i<maplist.size();i++)
	{
		kv.clear();
		kv = split(maplist.at(i), ":");
		if(kv.at(0) == "MesId")
			SetMesId(kv.at(1));
		else if(kv.at(0) == "UserId")
			SetUserId(kv.at(1));
		else if(kv.at(0) == "LbmId")
			SetLbmId(kv.at(1));
		else
			SetValue(kv.at(0), kv.at(1));
	}
}

bool MesData::SetValue(string paramname, string paramvalue)
{
	Params[paramname] = paramvalue;
}

bool MesData::ExistInMap(string key)
{
	iter = Params.find(key);
	if(Params.end() == iter)
		return false;
	else
		return true;
}

bool MesData::CleanMapParams()
{
	Params.clear();
}

int MesData::GetClientFd()
{
	return ClientFd;
}

string MesData::GetMesId()
{
	return MesId;
}
string MesData::GetUserId()
{
	return UserId;
}
string MesData::GetLbmId()
{
	return LbmId;
}
string MesData::GetParams()
{
	string ret;
	ret += "MesId:" + MesId + "," + "UserId:" + UserId + "," + "LbmId:" + LbmId + "," ;
	iter = Params.begin();
	int i = 1;
	for(;iter != Params.end();i++, iter++)
	{
		ret += iter->first + ":" + iter->second;
		if(i < Params.size())
			ret += ",";
	}
	return ret;
}
void MesData::GetValue(string &value, string paramname)
{
	if(ExistInMap(paramname))
		value = iter->second;
}
void MesData::GetValue(int &value, string paramname)
{
	if(ExistInMap(paramname)){
		istringstream strResult(iter->second);
		strResult>>value;
	}
}

void MesData::GetValue(double &value, string paramname)
{	
	if(ExistInMap(paramname)){
		istringstream strResult(iter->second);
		strResult>>value;
	}
}

void MesData::AddLog(string strLog)
{
	vLog.push_back(strLog);
}

vector<string> MesData::GetVlog()
{
	return vLog;
}

Log::Log()
{
	fileName = "debugger.log";
	//outfile.open(fileName, ios::out);
}

void Log::WriteLog(vector<string> vecLog)
{

	if(vecLog.empty())
		return;
	outfile.open(fileName);
	int i;
	int veclen;
	veclen = vecLog.size();
	for(i=0;i<veclen;i++)
	{
		cout<<"log claass"<<vecLog.at(i)<<endl;
		outfile<<vecLog.at(i)<<"\n";
	}
	outfile.close();
}

