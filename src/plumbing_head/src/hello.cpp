#include "ros/ros.h"
#include "plumbing_head/hello.h"


namespace hello_ns {
    void Myhello::run(){
        ROS_INFO("run函数执行.......");
    }
}
int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");
    /* code */
    ros::init(argc,argv,"hello_head");
    hello_ns::Myhello myhello;
    myhello.run();
    return 0;
}
