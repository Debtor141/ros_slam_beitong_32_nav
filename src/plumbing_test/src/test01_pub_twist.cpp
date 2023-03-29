#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
  /* code 
  需求：发布速度消息
  话题:/turtle/cmd_vel
  消息:geometry_msgs/Twist

  1.包含头文件
  2.初始化ros节点
  3.创建节点句柄
  4.创建发布对象
  5.发布逻辑实现
  6.spinOnce（）
  
  */

int main(int argc, char  *argv[])
{
      //1.包含头文件
  //2.初始化ros节点
/*
作用：ros初始化函数

参数：
argc ---------- 封装实参个数（n+1）传入n个参数
argv ----------  封装参数的数组
name ---------- 为节点命名（唯一性）
options --------- 节点启动选项

返回值为空

使用：
1.argc，argv使用
如果按照ros中的特定格式传入实参，ros可以使用，比如可以用来设置全局参数，给节点重命名
2.options使用
需求：特定场景下需要一个结点多次启动正常运行
每次启动加一个随即数，避免重名问题
解决：设置启动项：ros::init_options::AnonymousName
*/

  ros::init(argc,argv,"my_control");
  //3.创建节点句柄
ros::NodeHandle nh;
  //4.创建发布对象
  /*
  作用：创建发布者对象

  参数：1.话题名称
  2.队列长度
  3.latch（可选） 如果设置为true，会保存发布方的最后一条消息
  并且新的订阅对象连接到发布方时，发布方会将这条消息发送给订阅者
  使用
  latch设置为true的作用
  静态地图发布为例，方案1：可以使用固定频率发送地图数据，但是效率太低了；
  方案2：可以将地图发布对象的latch设置为true，并且发布方只发送一次数据，每当订阅者连接时，将地图数据发送给订阅者，只发送一次，提高了数据的发送效率。
  */
ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel",10);
  //5.发布逻辑实现
ros::Rate rate(10); // 设置发布频率
//组织被发布的消息
geometry_msgs::Twist twist;
twist.linear.x = 1.0;
twist.linear.y = 0.0;
twist.linear.z = 0.0;

twist.angular.x = 0.0;
twist.angular.y = 0.0;
twist.angular.z = 0.5;
//循环发布
while  (ros::ok())
{
    pub.publish(twist);
    //休眠
    rate.sleep();
    //回头
    ros::spinOnce();
    
}

  
    return 0;
}
