#include <ros/ros.h>
#include <serial/serial.h>
#include <iostream>

int main(int argc, char *argv[])
{
    /* code */
    ros::init(argc,argv,"serial_set");
    ros::NodeHandle n;

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
        return -1;
    }
    
    //判断串口是否打开成功
    if(sp.isOpen())
    {
        ROS_INFO_STREAM("/dev/ttyUSB0 is opened.");
    }
    else{
        return -1;
    }
    
    ros::Rate loop_rate(1);
    uint8_t buffer[1024];

    //从主机通过串口发送的内容
    unsigned char all_data[1] = {0xA0};
    double volt,current;
    double percent_battery , percent_battery2;
    double temperature1, temperature2;
    bool battery_state;
    while (ros::ok())
    {
        /* code */
        //获取缓冲区内的字节数
        size_t n = sp.available();
        //发送内容
        sp.write(all_data,1);
        if(n!=0)
        {
            //读出数据
            n = sp.read(buffer,n);//读取串口返回的数据

            for(int i=0; i<n;i++)
            {
                //16进制的方式打印到屏幕
                //std::cout<<std::hex<<(buffer[i] & 0xff) << " ";
                std::cout<<(buffer[i] ) << " ";
            }
            std::cout<<std::endl;
            //把数据发回去
        }
    }
        //关闭串口
     sp.close();
    return 0;
}
