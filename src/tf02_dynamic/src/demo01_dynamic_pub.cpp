#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/TransformStamped.h"
#include "tf2/LinearMath/Quaternion.h"
/* code 
            发布方实现：需要订阅乌龟的位姿信息，转换成相对于世界坐标系的关系，并发布
            准      备：
            1..乌龟位姿的话题  /turtle1/pose
            2.消息:turtlesim/Pose
            流程
            1.包含头文件
            2.初始化，编码，句柄
            3.创建一个订阅对象，订阅turtle1/pose
            4.通过回调函数处理订阅的消息，将位姿信息转换成坐标相对关系并发布
            5.spin（）




*/

void doPose(const turtlesim::Pose::ConstPtr& pose){

    //获取位姿信息，转换成坐标系相对关系（核心）,并发布
    //a.创建一个TF发布对象,static 每次回调都是同一个对象
    static tf2_ros::TransformBroadcaster pub;
    //b.组织被发布的数据；
    geometry_msgs::TransformStamped ts;
    ts.header.frame_id = "world";
    ts.header.stamp = ros::Time::now();
    ts.child_frame_id = "turtle1";
    //坐标偏移量
    ts.transform.translation.x = pose->x;
    ts.transform.translation.y = pose->y;
    ts.transform.translation.z = 0;
    //坐标四元数
    /* 
    位姿信息中没有四元数，有偏航角度,0,0,theta
    */
   tf2::Quaternion qtn;
   qtn.setRPY(0,0,pose->theta);
    ts.transform.rotation.x = qtn.getX();
    ts.transform.rotation.y = qtn.getY();
    ts.transform.rotation.z = qtn.getZ();
    ts.transform.rotation.w = qtn.getW();
    //c.发布
    pub.sendTransform(ts);


}

int main(int argc, char *argv[])
{
    /* code */
            //     1.包含头文件
            // 2.初始化，编码，句柄
            setlocale(LC_ALL,"");
            ros::init(argc,argv,"dynamic_pub");
            ros::NodeHandle nh;
            // 3.创建一个订阅对象，订阅turtle1/pose
            ros::Subscriber sub = nh.subscribe("/turtle1/pose",100,doPose);
            // 4.通过回调函数处理订阅的消息，将位姿信息转换成坐标相对关系并发布
            // 5.spin（）
            ros::spin();
    return 0;
}
