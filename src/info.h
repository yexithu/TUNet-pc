#ifndef INFO_H
#define INFO_H

#include <QString>

struct IpInfo
{
    int ipv4_Ip[4];  //ip地址，
    int onlineTime[3];  //上线时间,时，秒，分
    QString macAdress;  //mac地址
    double accurateTraffic;  //该ip精确流量
};

struct AccountInfo
{
    QString error = "";  //Empty string when there's no error. Otherwise some description of the error.
    QString userName;
    double balance;  //账户余额
    double roughTraffic;  //粗略流量，B为单位
    double totalAccurateTraffic;  //总精确流量，B为单位
    int loginTime;  //Connected times in seconds
    int onlineIpCount;  //ip数量
    IpInfo *ipInfo;  //ip信息
};


class Info
{
public:
    Info();
    ~Info();

    enum InfoType
    {
        LoginInfo = 0,
        LogoutInfo,
        QueryInfo,
        CheckInfo
    };
    
    InfoType infoType;
    AccountInfo *accountInfo;//Currently all types of info are stored here.
};

#endif // INFO_H
