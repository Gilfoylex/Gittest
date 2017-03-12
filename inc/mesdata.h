#ifndef MESDATA_H
#define MESDATA_H
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>

using namespace std;

std::vector<std::string> split(const  std::string& s, const std::string& delim);

class MesData{
	private:
		int ClientFd;
		string MesId;
		string UserId;
		string LbmId;
		map<string, string> Params;
		map<string, string>::iterator iter;
		vector<string> vLog;
	public:
		MesData();
		bool SetClientFd(int clientfd);
		bool SetMesId(string mesid);
		bool SetUserId(string userid);
		bool SetLbmId(string lbmid);
		bool SetParams(string params);
		bool SetValue(string paramname, string paramvalue);
		bool ExistInMap(string key);
		bool CleanMapParams();
		void AddLog(string strLog);
		vector<string> GetVlog();
		int GetClientFd();
		string GetMesId();
		string GetUserId();
		string GetLbmId();
		string GetParams();
		void GetValue(string &value, string paramname);
		void GetValue(int &value, string paramname);
		void GetValue(double &value, string paramname);
};

class Log{
	public:
		Log();
		void WriteLog(vector<string> vecLog);
	private:
		string fileName;
		ofstream outfile;
};

void WriteLog(string strLog);
void GetValue(string &value, string paramname);
void GetValue(int &value, string paramname);
void GetValue(double &value, string paramname);
void GetValue(int &a);
void MakeResult(string ret);
//static Data d;

#endif // BASE_H
