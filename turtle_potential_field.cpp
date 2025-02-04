#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "turtlesim/Spawn.h"
#include <cmath>

class TurtlePotentialField
{
public:
    TurtlePotentialField()
    {
        
        vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
        pose_sub_ = nh_.subscribe("/turtle1/pose", 10, &TurtlePotentialField::poseCallback, this);

        
        goal_x_ = 9.0;
        goal_y_ = 9.0;

        obstacle_x_ = 7.6;
        obstacle_y_ = 7.5;

        spawnObstacleTurtle();

        ROS_INFO("Obstacle turtle placed at: (%.2f, %.2f)", obstacle_x_, obstacle_y_);
    }

    void poseCallback(const turtlesim::Pose::ConstPtr& msg)
    {
        
        turtle_x_ = msg->x;
        turtle_y_ = msg->y;
        turtle_theta_ = msg->theta;

        
        moveTurtle();
    }

    void spawnObstacleTurtle()
    {
        
        ros::ServiceClient spawn_client = nh_.serviceClient<turtlesim::Spawn>("/spawn");
        turtlesim::Spawn srv;

        
        srv.request.x = obstacle_x_;
        srv.request.y = obstacle_y_;
        srv.request.name = "obstacle_turtle"; 
        
        if (spawn_client.call(srv))
        {
            ROS_INFO("Successfully spawned obstacle turtle.");
        }
        else
        {
            ROS_ERROR("Failed to spawn obstacle turtle.");
        }
    }

    void moveTurtle()
    {
        
        double goal_diff_x = goal_x_ - turtle_x_;
        double goal_diff_y = goal_y_ - turtle_y_;
        double goal_distance = std::sqrt(goal_diff_x * goal_diff_x + goal_diff_y * goal_diff_y);

        
        double obstacle_diff_x = obstacle_x_ - turtle_x_;
        double obstacle_diff_y = obstacle_y_ - turtle_y_;
        double obstacle_distance = std::sqrt(obstacle_diff_x * obstacle_diff_x + obstacle_diff_y * obstacle_diff_y);

        
        double linear_gain = 1.0;
        double angular_gain = 4.0;

        
        double repulsive_gain = 1.6;             
        double obstacle_effective_range = 2.5;     

        
        double attractive_linear_vel = linear_gain * goal_distance;
        double attractive_angle = std::atan2(goal_diff_y, goal_diff_x);
        double attractive_angular_vel = angular_gain * (attractive_angle - turtle_theta_);

        
        double repulsive_force_x = 0.0;
        double repulsive_force_y = 0.0;

        if (obstacle_distance < obstacle_effective_range)
        {
            
            repulsive_force_x = repulsive_gain * (1.0 / obstacle_distance - 1.0 / obstacle_effective_range) * (1.0 / (obstacle_distance * obstacle_distance)) * (turtle_x_ - obstacle_x_);
            repulsive_force_y = repulsive_gain * (1.0 / obstacle_distance - 1.0 / obstacle_effective_range) * (1.0 / (obstacle_distance * obstacle_distance)) * (turtle_y_ - obstacle_y_);
        }

        
        double combined_force_x = goal_diff_x * linear_gain + repulsive_force_x;
        double combined_force_y = goal_diff_y * linear_gain + repulsive_force_y;

        
        double combined_distance = std::sqrt(combined_force_x * combined_force_x + combined_force_y * combined_force_y);
        double combined_angle = std::atan2(combined_force_y, combined_force_x);
        double linear_vel = std::min(combined_distance, 2.0); 
        double angular_vel = angular_gain * (combined_angle - turtle_theta_);

        
        if (goal_distance < 0.1)
        {
            ROS_INFO("Goal reached!");
            stopTurtle();
            return;
        }

        
        geometry_msgs::Twist vel_msg;
        vel_msg.linear.x = linear_vel;
        vel_msg.angular.z = angular_vel;

        
        vel_pub_.publish(vel_msg);
    }

    void stopTurtle()
    {
        
        geometry_msgs::Twist vel_msg;
        vel_msg.linear.x = 0.0;
        vel_msg.angular.z = 0.0;
        vel_pub_.publish(vel_msg);
    }

private:
    ros::NodeHandle nh_;
    ros::Publisher vel_pub_;
    ros::Subscriber pose_sub_;

    
    double turtle_x_, turtle_y_, turtle_theta_;
    double goal_x_, goal_y_;
    double obstacle_x_, obstacle_y_;
};

int main(int argc, char **argv)
{

    ros::init(argc, argv, "turtle_potential_field_with_fixed_obstacle_turtle");

    
    TurtlePotentialField turtle_pf;

    
    ros::spin();

    return 0;
}
