#include "ros/ros.h"
#include "tf2_ros/transform_listener.h"
#include  "geometry_msgs/PointStamped.h"
#include "tf2_ros/buffer.h"
#include  "tf2_geometry_msgs/tf2_geometry_msgs.h"

/* code
订阅方实现
1.计算son1和son2的相对关系
2.计算son1的某个点在son2的坐标
流程
1.包含头文件
2.编码初始化nh
3.创建订阅对象
4.编写解析逻辑
5.spinonce（）



 */

int main(int argc, char *argv[])
{
    /* code */

// 1.包含头文件
// 2.编码初始化nh
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"tfs_sub");
// 3.创建订阅对象 
    tf2_ros::Buffer buffer;
    tf2_ros::TransformListener sub(buffer);
// 4.编写解析逻辑
//创建坐标点
    geometry_msgs::PointStamped psATSon1;
    ros::Rate rate(10);
    while (ros::ok())
    {
        /* code */
        try
        {
            /* code */
            // 1.计算son1和son2的相对关系
            // 2.计算son1的某个点在son2的坐标

        }
        catch(const std::exception& e)
        {
            ROS_INFO("错误提示：%s",e.what());
        }
        
        rate.sleep();
        ros::spinOnce();
    }
    
// 5.spinonce（）

    return 0;
}
