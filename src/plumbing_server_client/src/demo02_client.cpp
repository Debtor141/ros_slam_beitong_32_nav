#include "ros/ros.h"
#include "plumbing_server_client/Addints.h"
/*
客户端：提交两个整数，并处理响应的结果
        1.包含的头文件
        2.初始化ros节点
        3.创建节点句柄
        4.创建客户端对象
        5.提交请求并处理响应

        实现参数的动态提交：
                1.格式：rosrun xxxxx   xxxx   12 34
                2.节点执行时，需要获取命令中的参数，并组织进request
                3.

*/

int main(int argc, char *argv[]) //argc代表传入参数的个数 ，argv代表传的参数，第一个为文件名
{
    setlocale(LC_ALL,"");
    // 优化实现，获取命令中的参数
    if (argc != 3){
        ROS_INFO("提交参数个数不对");
        return 1;
    }
//         1.包含的头文件
//         2.初始化ros节点
    ros::init(argc,argv,"dabao");
//         3.创建节点句柄
    ros::NodeHandle nh; //节点句柄对象，内有函数
//         4.创建客户端对象
    ros::ServiceClient client = nh.serviceClient<plumbing_server_client::Addints>("addints" );
//         5.提交请求并处理响应
    plumbing_server_client::Addints ai ;
    //5.1 组织请求
    ai.request.num1 = atoi(argv[1]);
    ai.request .num2 = atoi(argv[2]);
    //5.2处理响应
    bool flag = client.call(ai);
    if (flag)
    {
        ROS_INFO("响应成功！");
        // 获取结果
        ROS_INFO("响应结果 = %d",ai.response.sum);
    }  else{
        ROS_INFO( "处理失败。。");
    }

    return 0;
 }