#include "ros/ros.h"

    /* code 
    需求1：演示时间相关的操作
    实现：
    1.准备（头文件，节点初始化，nh）
    2.获取当前时刻
    3.设置制定时刻

    需求2：程序执行中停顿5s
    实现：
    1.先创建持续时间对象
    2.休眠

    需求3：已知程序开始运行的时刻，和程序运行的时间，求运行结束的时刻
    实现：
    1.获取开始执行的时刻
    2.模拟运行时间
    3.计算结束时刻 = 开始 + 持续时间

    需求4：每隔1s在控制台输出一段文本。
    实现：
    1.策略1：ros::rate ()
    策略2：定时器


    */

   //回调函数
void cb(const ros::TimerEvent& event){
    ROS_INFO("定时器启动");

}
int main(int argc, char  *argv[])
{
    // 1.准备（头文件，节点初始化，nh）
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"hello_time");
    ros::NodeHandle nh; // 注意：必须
    // 2.获取当前时刻:now被执行调用的那一刻
    // now函数会将当前时刻封装并返回
    //参考系：距离 1970年1月1日 00时00分00秒 东八区是8时 
    ros::Time right_now = ros::Time::now();
    ROS_INFO("当前时刻:%.2f",right_now.toSec( ));
    ROS_INFO("当前时刻:%d", right_now.sec);
    // 3.设置制定时刻
    ros::Time t1(20,312345678);
    ros::Time t2(100.35);
    ROS_INFO("t1=%.2f",t1.toSec());
    ROS_INFO("t2=%.2f",t2.toSec());
    //------------------------------------------------------------
    ROS_INFO("-----------------------------持续时间----------------------------------------");
    ROS_INFO("开始睡觉");
    ros::Duration du(4.5);
    du.sleep();
    ROS_INFO("醒了,已休眠4.5秒");
    //------------------------------------------------------------
    ROS_INFO("-----------------------------时间运算----------------------------------------");
      //  1.获取开始执行的时刻
      ros::Time begin = ros::Time::now();
    //2.模拟运行时间
    ros::Duration du1(5);
    //3.计算结束时刻 = 开始 + 持续时间
    ros::Time stop = begin + du1;
    ROS_INFO("开始时刻：%.2f",begin.toSec());
    ROS_INFO("结束时刻：%.2f",stop.toSec());
    ROS_INFO("-----------------------------定时器----------------------------------------");
    /*
        时间间隔 --- 1s
        回调函数 --- 封装业务
        是否一次性
        自动启动 false 需要手动调用timer.start（）
    */
    ros::Timer timer = nh.createTimer(ros::Duration(1),cb);
    ros::spin();
    return 0;
}
