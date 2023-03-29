#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include <serial/serial.h>
#include <iostream>
#include <geometry_msgs/Twist.h>

class  TeleopTurtle
{
    public:
    TeleopTurtle();

    private:
    // 处理手柄发送的信息
    void callback(const sensor_msgs::Joy::ConstPtr &joy);
    // 实例化ros句柄
    ros::NodeHandle nh;
    //定义订阅者，订阅手柄的数据
    ros::Subscriber sub;
    //定义发布者对象，将手柄数据发布到乌龟控制话题上
    ros::Publisher pub;
    // 用来接受launch文件中设置的参数，绑定手柄摇杆，轴的映射
    int axis_linear , axis_angular;
};

TeleopTurtle::TeleopTurtle()
{
    //从参数服务器读取参数
    nh.param<int>("axis_linear",axis_linear,1);//第三个参数为，取不到参数时的值
    nh.param<int>("axis_angular",axis_angular,2);
    //订阅手柄信息
    sub = nh.subscribe<sensor_msgs::Joy>("joy",10,&TeleopTurtle::callback,this);
}

void TeleopTurtle::callback(const sensor_msgs::Joy::ConstPtr &joy)
{
    float v_duo,v_dian;
    //定义串口
     serial::Serial sp;
    serial::Timeout to = serial::Timeout::simpleTimeout(1000);
    //设置要打开串口的名称
    sp.setPort("/dev/ttyUSB0");
    //设置波特率
    sp.setBaudrate(115200);
    //串口设置timeout
    sp.setTimeout(to);
    try
    {
        //打开串口
        sp.open();
    }
    catch(serial::IOException& e)
    {
        ROS_ERROR_STREAM("unable to open port.");
        
    }
    
    //判断串口是否打开成功
    if(sp.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyUSB0 is opened.");
    }

    ros::Rate loop_rate(1);
    uint8_t buffer[2048];

    //从主机通过串口发送的内容
    //unsigned char all_data[2] = {v_duo,v_dian};
    /* code */
    v_dian = joy->axes[axis_linear];
    v_duo = joy->axes[axis_angular];
    char v_duo_250 =(v_duo+1)*250;
    ROS_INFO("角速度为：%.3f",v_duo);
    struct data_pro{
        unsigned char start;
        unsigned char type;
        unsigned char data;
       unsigned char end;
    };
    data_pro angle = {
        's',
        'a',
        v_duo_250,
        'e'
    };
    data_pro velocity= {
        's',
        'a',
        v_dian,
        'e'
    };
    // unsigned char v_duo_250 ='p';
    // unsigned char start = 's';
    // unsigned char type_a = 'a';
    // unsigned char type_v = 'v';
    // unsigned char end = 'e';

    // char str[3]={0};
    // sprintf(str,"%03d",v_duo_2500);
    //unsigned char all_data[2] = {v_duo_180,v_dian};
    unsigned char all_data_a[4] = {angle.start,angle.type,angle.data,angle.end};
    //unsigned char all_data_v[4] = {start,type_v,v_dian,end};
    ROS_INFO("当前线速度为：%.3f 角速度为：%c",v_dian,v_duo_250);
    //获取缓冲区内的字节数
    size_t n = sp.available();
    //发送内容
    sp.write(all_data_a,4);
    //sp.write(all_data_v,4);
    if(n!=0)
    {
        //读出数据
        n = sp.read(buffer,n);//读取串口返回的数据

        for(int i=0; i<n;i++)
        {
            //16进制的方式打印到屏幕
            //std::cout<<std::hex<<(buffer[i] & 0xff) << " ";
            std::cout<<(buffer[i] ) ;
        }
        std::cout<<std::endl;
        //把数据发回去
        // sp.write(buffer, n);
    
    }
        //关闭串口
    sp.close();
}

int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");
    //初始化ros节点
    ros::init(argc,argv,"control_duo");
    TeleopTurtle teleopTurtle;
    ros::spin();
    return 0;
}
