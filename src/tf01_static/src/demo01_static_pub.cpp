#include "ros/ros.h"
#include "tf2_ros/static_transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"
    /* code
    需求：该节点需要发布两个坐标系的相对关系

    1.包含头文件
    2.编码，节点初始化 nh；
    3.创建发布对象
    4.组织被发布的消息
    5.发布消息
    6.spin（）
    
    
    
    */


int main(int argc, char  *argv[])
{

    // 1.包含头文件
    // 2.编码，节点初始化 nh；
    setlocale(LC_ALL,"");
    // 3.创建发布对象
    ros::init(argc,argv,"static_pub");
    ros::NodeHandle nh;
    tf2_ros::StaticTransformBroadcaster pub;
    // 4.组织被发布的消息
    geometry_msgs::TransformStamped tfs;
    tfs.header.stamp = ros::Time::now();
    tfs.header.frame_id = "base_link"; // 相对坐标系中被参考的一个
    tfs.child_frame_id = "laser";
    tfs.transform.translation.x = 0.2;
    tfs.transform.translation.y = 0.0;
    tfs.transform.translation.z = 0.5;
    //需要参考欧拉角转换
    tf2::Quaternion qtn;// 创建四元数对象
    //向该对象设置欧拉角，将欧拉角转换成四元数
    qtn.setRPY(0,0,0); // 弧度

    tfs.transform.rotation.x = qtn.getX();
    tfs.transform.rotation.y = qtn.getY();
    tfs.transform.rotation.z = qtn.getZ();
    tfs.transform.rotation.w = qtn.getW();
    // 5.发布消息
    pub.sendTransform(tfs);
    // 6.spin（）
    ros::spin( );

    return 0;
}
