#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include "tf2_ros/buffer.h"
#include "geometry_msgs/PointStamped.h"
#include "tf2_geometry_msgs/tf2_geometry_msgs.h"
    /* code
    订阅方实现：订阅发布的坐标系的相对关系，传入坐标点，调用tf实现转换
    流程
    1.包含头文件
    2.编码设置，初始化，nh（必须）；
    3.创建一个订阅对象；——————订阅坐标关系
    4.组织一个坐标点数据
    5.转换算法实现，调用tf内置实现。
    6.最后输出
    
     */
int main(int argc, char *argv[])
{
    // 1.包含头文件
    // 2.编码设置，初始化，nh（必须）；
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"static_sub");
    ros::NodeHandle nh;
    // 3.创建一个订阅对象；——————订阅坐标关系
    //3.1 创建一个buffer 缓存
    tf2_ros::Buffer buffer;
    //3.2创建一个监听对象
    tf2_ros::TransformListener listener(buffer);
    // 4.组织一个坐标点数据
    geometry_msgs::PointStamped ps;
    ps.header.frame_id = "laser";
    ps.header.stamp = ros::Time::now();
    ps.point.x = 2.0;
    ps.point.y = 3.0;
    ps.point.z = 5.0;
    //添加休眠
    ros::Duration(2).sleep();
    // 5.转换算法实现，调用tf内置实现。
    ros::Rate rate(10);
    while (ros::ok())
    {
        /* code *///核心代码实现------将ps转换成相对应base_link点
        geometry_msgs::PointStamped ps_out;
        ps_out = buffer.transform(ps,"base_link");
        //输出
        ROS_INFO("转换后的坐标(%.2f,%.2f,%.2f),参考坐标系%s",
        ps_out.point.x,
        ps_out.point.y
        ,ps_out.point.z,
        ps_out.header.frame_id.c_str());
        rate.sleep();
        ros::spinOnce();
    }
    
    // 6.最后输出
    return 0;
}
