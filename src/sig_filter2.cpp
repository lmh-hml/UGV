#include <ros/ros.h>
#include <ugv/Int16Array.h>
#include <array>


class SigFilter
{
    public:

        SigFilter();

        std::array< ugv::Int16Array, 10 > buffer;
        int oldest, newest, size;
        const int MAX;
        ugv::Int16Array msg;

        void increment(int& index);
        void insertData(const ugv::Int16Array& data);
        void removeData();
        ugv::Int16Array filter();

        ros::NodeHandle nh;
        ros::Subscriber listener;
        ros::Publisher  Array_pub;
        void collectArray(const ugv::Int16Array::ConstPtr& array);

};

SigFilter::SigFilter():oldest(0), newest(0),size(0), MAX(10){

    listener=nh.subscribe<ugv::Int16Array>("ultrasonicArray",10,&SigFilter::collectArray,this);
    Array_pub=nh.advertise<ugv::Int16Array>("filteredArray",1);

}

void SigFilter::collectArray(const ugv::Int16Array::ConstPtr& array)
{    
    insertData(*array);
}

void SigFilter::increment(int& index)
{
    index++;
    if( index >= MAX) index= index% MAX;
}

void SigFilter::insertData(const ugv::Int16Array& data)
{
    if( size!=0 && newest == oldest )
    {
        increment(oldest);
    }

    buffer[newest]=data;
    increment(newest);
    size++;
}

void SigFilter::removeData()
{
    buffer[ oldest ].data= {0.0,0.0,0.0};
    increment(oldest);
    size--;
}

ugv::Int16Array SigFilter::filter()
{
    ugv::Int16Array toReturn; 

    int dividend = buffer.size(); //the dividing number for average

    if(buffer.size()>=MAX)  //if buffer reached full capacity
    {
      int16_t temp[]={ 0,0,0 };

    for(int count=0; count<buffer.size(); ++count)
    {

        temp[0] += buffer[count].data[0];
        temp[1] += buffer[count].data[1];
        temp[2] += buffer[count].data[2];
	
	
        ROS_INFO("during additon: (+ %d) %d", buffer[count].data[1],temp[1]);
    }

    ROS_INFO("before division: %d", temp[1]);

    temp[0] = (int16_t) temp[0]/dividend;
    temp[1] = (int16_t) temp[1]/dividend;
    temp[2] = (int16_t) temp[2]/dividend;

    ROS_INFO("after division: %d", temp[1]);

    toReturn.data[0]=temp[0];
    toReturn.data[1]=temp[1];
    toReturn.data[2]=temp[2];
  }
  else if(buffer.size()<MAX )
  {
    toReturn=buffer.back();
  }

    return toReturn;

}


int main(int argc, char** argv)
{
  ros::init(argc,argv,"SigFig");
  SigFilter sf;
  ROS_INFO("SigFig ready:");

  while(ros::ok())
  {
      sf.msg=sf.filter();
      sf.Array_pub.publish(sf.msg);
      ros::spinOnce();
  }

}
