#include "ros/ros.h"


/*
演示参数查询
 实现：
                        ros::NodeHandle-------------------------------------

                        ros::param --------------------------------------
              

*/
int main(int argc, char *argv[])
{
    /* code */
    //设置编码
    setlocale(LC_ALL,"");
    //初始化ros节点
    ros::init(argc,argv,"get_param_c");
    //创建节点句柄
    ros::NodeHandle nh;
    //ros::NodeHandle
    //1.param 查询key为radius的值，如果没有返回0.5
    double radius = nh.param("radius",0.5);
    ROS_INFO("radius = %.2f",radius);
    //2.getParam
    //double radius2 = 0.0;
    //bool result = nh.getParam("radius",radius2);
   /* if (result)
    {
        ROS_INFO("获取的半径是： %.2f",radius2);
    }
    else{
        ROS_INFO("被查询的变量不存在。");
    }
    */
    //3.getParamCached ----提高变量获取的参数
    double radius2 = 0.0;
    bool result = nh.getParamCached("radius",radius2);
    if (result)
    {
        ROS_INFO("获取的半径是： %.2f",radius2);
    }
    else{
        ROS_INFO("被查询的变量不存在。");
    }

 
    return 0;
}
