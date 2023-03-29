# include "ros/ros.h"
# include "plumbing_server_client/Addints.h"
/* 
服务端实现，解析客户端提交的数据，产生相应
        1.包含的头文件
        2.初始化ros节点
        3.创建节点句柄
        4.创建服务对象
        5.处理请求并产生相应
        6.spin（）处理回调函数
        测试 rosservice call addints "num1: 1
        num2: 5"



*/
// 回调函数返回布尔
bool donums( plumbing_server_client::Addints::Request &request,
plumbing_server_client::Addints::Response &response)
{
    //1.处理请求
    int num1 = request.num1;
    int num2 = request.num2;
    ROS_INFO("收到的请求数据:num1 =  %d, num2 = %d",num1, num2);
    //2.组织响应
    int sum = num1 +num2;
    response.sum = sum ;
    ROS_INFO("求和结果:sum = %d",sum);
    return true;
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    //2.初始化ros节点
    ros::init(argc,argv,"heishui"); // 节点名称需要唯一
      //  3.创建节点句柄
    ros::NodeHandle nh;
        //4.创建服务对象
    ros::ServiceServer server = nh.advertiseService("addints",donums);
    ROS_INFO("服务器端启动");
        //5.处理请求并产生相应
        //6.spin（）处理回调函数
    ros::spin();

    return 0;
}