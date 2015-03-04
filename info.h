#ifndef INFO_H
#define INFO_H

#include <QString>
typedef struct IpInfo
{
	QString ipv4_Ip; //ip地址
	QString macAdress; //mac地址
	double accurateTraffic; //该ip精确流量
}IpInfo;

typedef struct AccountInfo
{
	QString userName;
	double balance;//账户余额
	double totalAccurateTraffic;//总精确流量
	int onlineIpCount;//ip数量
	IpInfo *ipInfo;//ip信息
}AccountInfo;


class Info
{
public:
    Info();
    ~Info();
public:
	AccountInfo accountInfo;
};

#endif // INFO_H
