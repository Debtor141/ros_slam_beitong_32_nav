#include "ros/ros.h"
/* code 
需求：修改参数服务器中，turtlesim 背景色相关的参数
1.初始化ros节点
2.不一定需要创建节点句柄；（和后续API有关）；
3.修改参数


*/
int main(int argc, char  *argv[])
{
   //1.初始化ros节点
   ros::init(argc,argv,"change_bgcolor");
    //2.不一定需要创建节点句柄；（和后续API有关）；
    ros::NodeHandle nh("turtlesim"); //里面是命名空间会和下面的名称加一起
    nh.setParam("background_r",255);
    nh.setParam("background_b",255);
    nh.setParam("background_g",255);
    //3.修改参数
    //如果调用ros：：param不需要nh
    // ros::param::set("/turtlesim/background_r",190);
    // ros::param::set("/turtlesim/background_g",70);
    // ros::param::set("/turtlesim/background_b",100);
    return 0;
}
