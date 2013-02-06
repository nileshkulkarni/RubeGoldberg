/*
* Copyright (c) 2006-2009 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

/* 
 * Base code for CS 296 Software Systems Lab 
 * Department of Computer Science and Engineering, IIT Bombay
 * Instructor: Parag Chaudhuri
 */


#ifndef _CS296BASE_HPP_
#define _CS296BASE_HPP_

#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>

#define	RAND_LIMIT 32767

namespace cs296
{

  //! What is the difference between a class and a struct in C++?
  /*
  Members of a class are private by default, whereas members of a struct are public by default. 
  Inheritance between classes is also private by default, and inheritance between structs is public by default
  */
  class base_sim_t;
  struct settings_t;
  
  //! Why do we use a typedef
  /*
  typedef is used when we want to replace one set of string by another which is usually smaller and convenient
  */
  typedef base_sim_t* sim_create_fcn(); 

  //! Simulation settings. Some can be controlled in the GUI.
  struct settings_t 
    {
    //! Notice the initialization of the class members in the constructor
    //! How is this happening?
    /*
    Constructor is called at the time of object creation and so values are initialized by default
    */
    settings_t() :
      view_center(0.0f, 20.0f), //set the center of gui as (0.0f, 20.0f)
      hz(60.0f), 
      velocity_iterations(8),//Default no of velocity iterations is set to 8 :One solver iteration is a single pass over all the constraints
      position_iterations(3),//Default no of position iterations set to 3
      draw_shapes(1),//Set draw_shapes property to 1 which enables drawing of shapes
      draw_joints(1),//Set draw_joints property to 1 which enables drawing of joints
      draw_AABBs(0),//Set draw_AABBs property to 0 which disables drawing AABBs :AABBs is axis-aligned bounding boxes
      draw_pairs(0),//Set draw_pairs to 0 disabling 
      draw_contact_points(0),//Set draw_contact_points to 0 to disable contact points from showing
      draw_contact_normals(0),//Set draw_contact_normals to 0 to disable contact normals from showing
      draw_contact_forces(0),//Set draw_contact_forces to 0 to disable contact forces from showing
      draw_friction_forces(0),//Set draw_friction_forces to 0 to disable friction forces from showing
      draw_COMs(0),//Disable showing of COM
      draw_stats(0),//Disable statistics(no of bodies,contacts,joints,etc) from showing
      draw_profile(0),//Disable profile(step,collide ,solve ,init value) from showing
      enable_warm_starting(1),//Enable warm starting property 
      enable_continuous(1),//enable continuous property for continuous collision detection
      enable_sub_stepping(0),//disables sub stepping
      pause(0),//Disables pause
      //!Disable single step 
      single_step(0)
    {}
    //!this center defines center of the view of gui
    b2Vec2 view_center; 
    //!Sets the frequency of time step in Hertz
    float32 hz; 
    //!Stores number of velocity iterations which is number of pass over velocity constraints in a single time step
    int32 velocity_iterations; 
    //!Stores number of position iterations which is number of pass over position constraints in a single time step
    int32 position_iterations; 
    //!Stores whether to draw shapes in the gui or not : 0 disables showing 1 enables showing
    int32 draw_shapes; 
    //!Stores whether to draw joints in the gui or not : 0 disables showing 1 enables showing
    int32 draw_joints; 
    //!Stores whether to draw AABBs in the gui or not : 0 disables showing 1 enables showing
    int32 draw_AABBs;
    //!Stores whether to draw pairs in the gui or not : 0 disables showing 1 enables showing
    int32 draw_pairs; 
    //!Stores whether to draw contact points in the gui or not : 0 disables showing 1 enables showing
    int32 draw_contact_points;  
    //!Stores whether to draw contact normals in the gui or not : 0 disables showing 1 enables showing
    int32 draw_contact_normals; 
     //!Stores whether to draw contact forces in the gui or not : 0 disables showing 1 enables showing
    int32 draw_contact_forces;
    //!Stores whether to draw frictional forces in the gui or not : 0 disables showing 1 enables showing
    int32 draw_friction_forces; 
    //!Stores whether to draw COMs (Centre of Mass) in the gui or not : 0 disables showing 1 enables showing
    int32 draw_COMs; 
    //!Stores whether to write statistics(no of bodies,contacts,joints,etc) in the gui or not : 0 disables showing 1 enables showing
    int32 draw_stats; 
    //!Stores whether to write profile (current velocity,position,etc) in the gui or not : 0 disables showing 1 enables showing
    int32 draw_profile;
     //!Stores whether to enable or disable warm starting(warm starting: assigning the previous frames values for the accumulated impulse at the start of the frame. ) : 1 enable it 0 disables it
    int32 enable_warm_starting;
    //!Stores whether to enable continous collision detection,etc :1 enables it 0 disables it
    int32 enable_continuous; 
    //!Stores whether to enable sub stepping (there is a sub-stepping solver that moves bodies to their first time of impact and then resolves the collision.) :1 enables it 0 disables it
    int32 enable_sub_stepping; 
    //!Store whether to pause or not:  1 pause it 0 plays it
    int32 pause; 
    //!Used to take a single step :stores 1 whenever a single step is called
    int32 single_step; 
  };
  
  
  //! Struct to hold information of simulation and it's name
  struct sim_t
  {
  //! name of the simulation
    const char *name; 
    //! To create a simulation
    sim_create_fcn *create_fcn; 

//! set the initial value in the constructor to _name and _create_fcn
    sim_t(const char *_name, sim_create_fcn *_create_fcn): 
      name(_name), create_fcn(_create_fcn) {;}
  };
  
  extern sim_t *sim;
  
  
  const int32 k_max_contact_points = 2048;  
  //!Defines a single contact point 
  struct contact_point_t 
  {
  //!Defines one of the fixture in contact
    b2Fixture* fixtureA; 
    //!Defines another fixture in contact
    b2Fixture* fixtureB; 
    //!Defines the normal of the contact point
    b2Vec2 normal; 
    //!Defines position of the contact point 
    b2Vec2 position; 
    //!Stores state of points of contact
    b2PointState state; 
  };
  
  
  //!Class base_sim_t which is the base simulation inherited from b2ContactListener class to get contact information and holds all the information of the world
  class base_sim_t : public b2ContactListener 
  {
  public:
    
    base_sim_t();

    
    //!Virtual destructors to virtually destroy objects so that no further contraints are solved for that body
    virtual ~base_sim_t();
    
    //!Set the max number of lines used when showing profile or statistics
    void set_text_line(int32 line) { m_text_line = line; } 
    
    //!To write the title in given x and y coordinate of a particular name(string)
    void draw_title(int x, int y, const char *string); 
    
    //!Function called for taking a single step with parameters as settings of the simulation
    virtual void step(settings_t* settings); 

    //!To label that key is not used in the simulation otherwise compiler would complain of the unsued value
    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); } 
    //!To label that key is not used in the simulation otherwise compiler would complain of the unsued value
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); } 

    //!To label that shift_mouse_down is not used in the simulation otherwise compiler would complain of the unsued value
    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); } 
    
    //!To label that mouse_down is not used in the simulation otherwise compiler would complain of the unsued value
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); } 
    //!To label that mouse_up is not used in the simulation otherwise compiler would complain of the unsued value
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); } 
    
    
    //!To label that mouse_move is not used in the simulation otherwise compiler would complain of the unsued value
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); } 

    
    //! Let derived tests know that a joint was destroyed.
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); } 
        
    // Callbacks for derived classes.
    
    //!To set that begin_contact function does not calculate anything
    virtual void begin_contact(b2Contact* contact) { B2_NOT_USED(contact); } 
    
    //!To label that end_contact function does not do anything
    virtual void end_contact(b2Contact* contact) { B2_NOT_USED(contact); } 
    //!To pre-solve a contact event with parameters as the contact event and manifold which stores information of contacting points , normal , local point and number of points of contact
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold); 
    
    //!Post-solve event of contact usually used to gather collision impulse results but not used int his since we do not care about impulses
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse) 
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    }

  //!Protected members : Different from private members as private function of this class is inaccesible to the inheriters of the classes which inherit this function
  protected:

    //! defined as friend class to access private and protected members of this class
    friend class contact_listener_t; 
    
    //! defines the ground of the world of simulation
    b2Body* m_ground_body;
    
    //! defines the world of AABBs
    b2AABB m_world_AABB;
    
    //!Variable to store all the possible contact points of the world
    contact_point_t m_points[k_max_contact_points];
    
    //! stores the count of contact points of the world
    int32 m_point_count; 

   //! To help be debug drawing
    debug_draw_t m_debug_draw;
    
    //! store the number of text lines in the world
    int32 m_text_line;
    //! Defines the world of the simulation
    b2World* m_world;

    //!Store the step counts of the world
    int32 m_step_count;
    
    //!Stores profilind data which is maximum time in milli seconds for each member eg. step,collide ,solve ,init
    b2Profile m_max_profile; 
    //!stores current profiling data which is current time in milli seconds for each member eg. step,collide,solve,etc.
    b2Profile m_total_profile;
  };
}

#endif
