#ifndef drc_poses_THREAD_H_
#define drc_poses_THREAD_H_

#include <GYM/control_thread.hpp>
#include <GYM/yarp_command_interface.hpp>
#include <GYM/yarp_status_interface.h>
#include <trajectory_generator/trajectory_generator.h>

namespace walkman
{
namespace drc
{
namespace poses
{
/**
 * @brief drc_poses control thread
 * 
 **/
class drc_poses_thread : public control_thread
{
private:
    walkman::yarp_command_interface cmd_interface;
    int cmd_seq_num=0;
    walkman::yarp_status_interface status_interface;
    int status_seq_num=0;

    bool busy=false;

    yarp::sig::Vector q_input;
    yarp::sig::Vector delta_q;
    yarp::sig::Vector q_output;
    yarp::sig::Vector q_initial;

    yarp::sig::Vector compute_delta_q();

    std::vector<std::string> commands;

    trajectory_generator joints_traj_gen;
    polynomial_coefficients poly;
    double initialized_time,next_time,final_time;
    std::map<std::string,yarp::sig::Vector> poses;
    yarp::sig::Vector q_desired;

    bool action_completed();
    void create_poses();
    void print_help();
public:
    
    /**
     * @brief constructor
     * 
     * @param module_prefix the prefix of the module
     * @param rf resource finderce
     * @param ph param helper
     */
     drc_poses_thread( std::string module_prefix, yarp::os::ResourceFinder rf, std::shared_ptr<paramHelp::ParamHelperServer> ph );
    
    
    /**
     * @brief drc_poses control thread initialization
     * 
     * @return true on succes, false otherwise
     */
    virtual bool custom_init();
    
    /**
     * @brief drc_poses control thread main loop
     * 
     */
    virtual void run();
    
};
}
}
}
#endif