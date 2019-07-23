本代码用于方便地读取配置文件。

------------------------------------------------------
**配置文件**

格式定义如下
```cpp
[MapLoader]
gridMap = /home/ugv2/CW/LidarMaps/BaotouLidarMaps/0513map/M_qianxun_c#hahaha

[LocCore]
calib_x = 12.09
calib_y=0.034
calib_yaw=0.0698
;Lidar to GPS calib
offset_x=66.6
offset_y=66.666
;GPS origin point shift with day, so need offset to fix. This value equal xdis and ydis in visulization window when loc is right
vis=1
zone=19

```
配置文件说明：
1. 代码由数据块和该数据块下的变量组成，如LocCore数据块下的变量calib_x。
2. 对变量的幅值必须用等号(=)，等号前后是否有空格没有影响
3. 井号(#)和分号(;)后面的内容被当做注释
4. 配置文件不需要以ini为后缀，其文件名可以任意

------------------------------------------------------

**函数使用**

函数使用示例如下


```cpp


#include <iostream>
#include "ConfigReader/inifile.h"

int main()
{
	inifile::IniFile configFile;//初始化IniFile类，用于读取配置文件
	std::string configFileName = "config.ini";//配置文件名字
	if (!configFile.load(configFileName))//使用load函数读取配置文件config.ini。如果配置文件存在且格式正确，返回true，否则返回false。建议返回false时停止程序，检查配置文件。
	{
		printf("config file %s error!\n", configFileName.c_str());
		return 0;
	}
	std::string tmp;

	//IniFile.getValue(string s1,string s2,string& s3)函数用于获取配置文件中的变量。如果成功获取到变量值，返回true，否则返回false
	//s1 是数据块的名字，s2为变量名,s3为变量的值，注意s3是string，如果变量是int或float的话需要调用atoi/atof转一下
	//读取MapLoader数据块
	if(configFile.getValue("MapLoader", "gridMap", tmp))//读取MapLoader数据块中gridMap变量的值，保存到tmp变量中。如果成功获得该变量值则返回true，否则返回false
		printf("gridmap =%s\n",tmp.c_str());//调用string.c_str()将string转为char*

	if (configFile.getValue("MapLoader", "roadMap", tmp))
		printf("roadMap =%s\n", tmp.c_str());

	//读取LocCore数据块
	if(configFile.getValue("LocCore", "calib_x", tmp))
		printf("calib_x = %f\n", atof(tmp.c_str()));//调用string.c_str()和atof将string转为float

	if (configFile.getValue("LocCore", "calib_y", tmp))
		printf("calib_y = %f\n", atof(tmp.c_str()));//调用string.c_str()和atof将string转为float

	if (configFile.getValue("LocCore", "calib_yaw", tmp))
		printf("calib_yaw = %f\n", atof(tmp.c_str()));//调用string.c_str()和atof将string转为float

	if (configFile.getValue("LocCore", "offset_x", tmp))
		printf("offset_x = %f\n", atof(tmp.c_str()));//调用string.c_str()和atof将string转为float

	if (configFile.getValue("LocCore", "offset_y", tmp))
		printf("offset_y = %f\n", atof(tmp.c_str()));//调用string.c_str()和atof将string转为float

	if (configFile.getValue("LocCore", "vis", tmp))
		printf("vis = %d\n", atoi(tmp.c_str()));//调用string.c_str()和atoi将string转为float

	if (configFile.getValue("LocCore", "zone", tmp))
		printf("zone = %d\n", atoi(tmp.c_str()));//调用string.c_str()和atoi将string转为float

}



```
函数调用说明：

1. getValue得到的变量值为string类型，可能需要转为char* 、int、float
2. getValue的返回值true/false表明是否成功得到该数据
3. 本段代码可以直接编译使用
------------------------------------------------------