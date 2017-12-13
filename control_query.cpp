/*
 * control_q
 *
 *  Created on: May 29, 2017
 *      Author: Apratim Choudhury
 */

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <cstdlib>
#include <string>
#include "TCPAcceptor.h"
#include <math.h>

using namespace std;

  TCPStream* stream = NULL;
  TCPAcceptor* acceptor = NULL;
  char buf[100];
  int a=0;
// callback that'll be called everytime the oublisher publishes some data

void myCallback(const geometry_msgs::Twist::ConstPtr &msg)
{

	//cout<<ros::Time::now()<<endl; 
	
	  for (int i=0; i<100 ; i++)
	  {

	     buf[i] = 0;

	  }
	  buf[99] = '\0'; 
	//geometry_msgs::Twist new_vel = *msg;
	double linear_vel =msg->linear.x;
	double ang_vel = msg->angular.z;

	/*if (linear_vel==0 || ang_vel==0)
	{
		return;
	}    		

	double radius = linear_vel/ang_vel;
	double steer_angle = atan(2.9/radius); */
	//sprintf(buf, "%d \nTime:%f \nLinear:(%f,0.0,0.0) \nSteering Angle: %f \n", ++a, ros::Time::now().toSec(), linear_vel,steer_angle); */
        sprintf(buf,"Brake");
   	//cout << *msg << endl;
	stream -> send(buf, sizeof(buf));
}

int main(int argc, char **argv)
{
    //const double FORWARD_SPEED_MPS = 0.5;

    //string robot_name = string(argv[1]);

    // Initialize the node
    ros::init(argc, argv, "control_query");
    ros::NodeHandle node;

     if (argc < 2 || argc > 4) {
        printf("usage: server <port> [<ip>]\n");
        exit(1);
	 }

   
  
    int First_number;
    int Second_number;

    // code for creating a scoket, listening for connections and receiving the data from the C-code on Windows
    if (argc == 3) 
    {
        acceptor = new TCPAcceptor(atoi(argv[1]), argv[2]);
    }
    else 
    {
        acceptor = new TCPAcceptor(atoi(argv[1]));
    }

     

    	if (acceptor->start() == 0)
	{
		
			cout << "Start APO Code in Windows \n" ;
			stream = acceptor->accept();

			if (stream != NULL)
			{

				size_t length;
        			char buffer[50];
				
   				
				if((length=stream->receive(buffer, sizeof(buffer))) >0)
		    		{

				// Code for using the data in the buffer and placing them in two variables which will then be used to populate the srv.request.a and srv.request.b 		variables			
					cout << "before printing" << endl;								
					buffer[length]='\0';
					//char * pch = NULL;			
					
					//pch = strtok(buffer,",");
					//First_number = atoll(pch);

						
					//pch = strtok(NULL,",");	
					//Second_number = atoll(pch);					
					cout << buffer << endl;

				} // End of if (length = stream)
			} // End of if (stream != NULL)	


	} //End of if (acceptor->start() == 0) 

    // A listener for pose
    ros::Subscriber sub = node.subscribe("/catvehicle/cmd_vel_safe", 100, myCallback);

    // Drive forward at a given speed.  The robot points up the x-axis.
    // The default constructor will set all commands to 0
    //geometry_msgs::Twist msg;
    //msg.linear.x = FORWARD_SPEED_MPS;

    // Loop at 10Hz, publishing movement commands until we shut down
    ros::Rate rate(100);
    //ROS_INFO("Starting to move forward");
    while (ros::ok()) {
        //pub.publish(msg);
        ros::spinOnce(); // Allow processing of incoming messages
        rate.sleep();
    }
}




