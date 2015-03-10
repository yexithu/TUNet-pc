#ifndef INFO_H
#define INFO_H

#include <QString>

struct IpInfo
{
    int ipv4_Ip[4];  //ip地址，
    QString onlineTimeString;//上线时间字符串,example  03-02 08:28
    int onlineTime[3];//上线时间
    QString macAdress;  //mac地址
    double accurateTraffic;  //该ip精确流量
    QString IpLogoutCookie; //下线ip用的cookie
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
    IpInfo ipInfo[3];  //ip信息
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
    AccountInfo accountInfo;//Currently all types of info are stored here.
};

#endif // INFO_H
