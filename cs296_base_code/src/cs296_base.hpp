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

#ifndef __APPLE__
#include "GL/glui.h"
#else
#include "GL/glui.h"
#endif
#include<string>
#include<iostream>
#include "render.hpp"
#include <Box2D/Box2D.h>
#include <cstdlib>
#include <unistd.h>
#define	RAND_LIMIT 32767
#include <thread>

extern "C"
{
#include<pthread.h>
}
namespace cs296
{

  //! What is the difference between a class and a struct in C++?
  /*!
  * - The structures are value types and the classes are reference types
  * - Classes are usually used for large amounts of data, whereas structs are usually used for smaller amount of data
  * - Classes could be inherited whereas structures no
  * - A structure couldn't be Null like a class
  * - A structure couldn't have a destructor such as class
  * - A structure can't be abstract, a class can
  * - You cannot override any methods within a structure except those belong to type of object
  * - Declared events within a class are automatically locked and then they are Thread safe, at the contrast of the structure type where event couldn't be locked.
  * - A structure must have always the default parameter less constructor be defined as public but a class might have one, so you can't define a private parameter less constructor
  * - A static constructor is trigged in case of class but not in case of structure 
  * - The strucutre can't conatain a volatile field wheatheas the class does
  * - You can't use sizeof with classes but you can with structures
  * - Fields are automatically initialized with classes to 0/false/null wheatheras in strucutres no
  * - Fields couldn't directley instanciated within structures but classes allow such operations
  * - Structure and class don't adopt the same aproach taward the System.Object.Equals() method
  */
  class base_sim_t;
  struct settings_t;


  //! Why do we use a typedef
  /*! - A typedef declaration introduces a name that, within its scope, becomes a synonym for the type given by the type-declaration portion of the declaration
  * - typedef is helpful for giving a short, sharp alias to complicated function pointer types
  * - typedef is necessary for many template metaprogramming tasks -- whenever a class is treated as a "compile-time type function", a typedef is used as a "compile-time type value" to obtain the resulting typ
  */
  typedef base_sim_t* sim_create_fcn(); 

  /*! Simulation settings. Some can be controlled in the GUI.
  - \c settings_t() : The constructor will set the required values of settings members. 
  - \c The members in the struct settings_t can be changed to configure the simulation in the world.
  - \c view_center : sets the position of the centre of the view.
/  - \c hz : It is the inverse of the time of an iteration.
  - \c velocity_iterations : the value in steps in which velocity changes.
  - \c position_iterations : the value in steps in which velocity changes. 
  - \c draw_shapes : if set 1,draws the shapes of bodies otherwise no.
  - \c draw_joints : if set 1,shows the wires which connect bodies in pulleyjoint etc. otherwise i.e if set 0 not drawn.
  - \c draw_AABBs : if set 1,the [axis aligned bounding boxes] of minimum size in which the body fits is shown otherwise i.e if set 0 not drawn.
  - \c draw_pairs : for enablling and disabling drawing of pairs
  - Similarly \c draw_contact_points, \c draw_contact_normals, \c draw_contact_forces, \c draw_friction_forces, 
    \c draw_COMs, \c draw_stats, \c draw_profile, \c enable_warm_starting, 
    \c enable_continuous, \c enable_sub_stepping, \c pause, \c single_step 
    all are set 0 or 1 as per requirements no description is given as their names are self-explanatory.
*/
  struct settings_t
  {
    //! Notice the initialization of the class members in the constructor\n
    //! How is this happening?\n
    //! A class constructor is a special member function of a class that is executed whenever we create new objects of that class.
    //! A constructor will have exact same name as the class and it does not have any return type at all, not even void. Constructors can be very useful for setting initial values for certain member variables 
    //! Data members of a class can be initialised using the constructor of class.
    
    settings_t() :
      view_center(0.0f, 20.0f),
      hz(60.0f),
      velocity_iterations(8),
      position_iterations(3),
      draw_shapes(1),
      draw_joints(1),
      draw_AABBs(0),
      draw_pairs(0),
      draw_contact_points(0),
      draw_contact_normals(0),
      draw_contact_forces(1),
      draw_friction_forces(1),
      draw_COMs(0),
      draw_stats(0),
      draw_profile(0),
      enable_warm_starting(1),
      enable_continuous(1),
      enable_sub_stepping(0),
      pause(0),
      single_step(0)
    {}
    
    b2Vec2 view_center;
    float32 hz;
    int32 velocity_iterations;
    int32 position_iterations;
    int32 draw_shapes;
    int32 draw_joints;
    int32 draw_AABBs;
    int32 draw_pairs;
    int32 draw_contact_points;
    int32 draw_contact_normals;
    int32 draw_contact_forces;
    int32 draw_friction_forces;
    int32 draw_COMs;
    int32 draw_stats;
    int32 draw_profile;
    int32 enable_warm_starting;
    int32 enable_continuous;
    int32 enable_sub_stepping;
    int32 pause;
    int32 single_step;
  };
  
  //! The Struct \a sim_t has 2 members
  //!   - \c name which is a string
  //!   - \c create_fcn which is a \a base_sim_t object which is the main object for simulation. 
  struct sim_t
  {
    const char *name;
    sim_create_fcn *create_fcn;

    sim_t(const char *_name, sim_create_fcn *_create_fcn): 
				  create_fcn(_create_fcn) {;}
  };
  
  extern sim_t *sim;
  
  const int32 k_max_contact_points = 2048;  
  //! Contact Point struct is used to store the fixtures of the 2 bodies which come into contact and the vectors of position and the normal of contact and the Position State
  struct contact_point_t
  {
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    b2Vec2 normal;
    b2Vec2 position;
    b2PointState state;
  };
  
  //! The Class \a base_sim_t
  //!   - It is an inherited class from \c b2ContactListener which is used to get the contact details whenever some bodies come into contact.\n
  //!   - It has the main world object as data member
  //!   - It has the PreSolve function which is things to be done after collision detection
 

 //!   - It has the Step function which is responsible for the motion of objects in the world!
class Ball
{
	private:
		bool m_contact	;
		b2World* my_world;
		std::thread musicThread;
	public:	
		Ball(b2World* m_world){
		m_contact = false;	

		b2Body* spherebody;
		b2CircleShape circle;
      	circle.m_radius = 2.0;
    
     
	  b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 1.0f;

    b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(0,20.0f);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);
	  spherebody->SetUserData(this);
		
		
		}
	void play1(int a){
		std::cout<<"threading is working";
		 system("mpg123 src/song.mp3");
		usleep(100*1000);
		return;
	}
	void startContact() { 
			std::cout<<"Detected\n";
			m_contact = true; }
  	void endContact() { m_contact = false; }
	void render(){
			pthread_t t1;
	
			std::string msg1 ("hello");
			std::thread thr(&Ball::play1, this,10);
			std::swap(thr,musicThread);
		/*	int a=1;
			std::cout<<"Called me\n";	
			int create1 = pthread_create( &t1, NULL,cs296::Ball::play1,reinterpret_cast<void*>(&msg1));
		*/	
	}
	void musicThreadjoin(){
	musicThread.join();
	}


	

};

class MyContactListener : public b2ContactListener
  {
    void BeginContact(b2Contact* contact) {
  
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData ){
        static_cast<Ball*>( bodyUserData )->startContact();
        static_cast<Ball*>( bodyUserData )->render();
	  }
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData ){
        static_cast<Ball*>( bodyUserData )->startContact(); 
	  
	    static_cast<Ball*>( bodyUserData )->render();
    
	  }
}
  
    void EndContact(b2Contact* contact) {
  
      //check if fixture A was a ball
      void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
      if ( bodyUserData ){
        static_cast<Ball*>( bodyUserData )->endContact();
		static_cast<Ball*>( bodyUserData )->musicThreadjoin();
	  }
      //check if fixture B was a ball
      bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
      if ( bodyUserData ){
        static_cast<Ball*>( bodyUserData )->endContact();
 		 
		static_cast<Ball*>( bodyUserData )->musicThreadjoin();
    }
	}
 
};

  class base_sim_t : public b2ContactListener
  {
  public:
    
    base_sim_t();

    //! Virtual destructors - amazing objects. Why are these necessary?
    /*! - Virtual destructors are useful when you can delete an instance of a derived class through a pointer to base class.
    * - Always make base classes' destructors virtual when they're meant to be manipulated polymorphically.
    * - If you want to prevent the deletion of an instance through a base class pointer, you can make the base class destuctor protected and nonvirtual; by doing so, the compiler won't let you call delete on a base class pointer.
    */
    virtual ~base_sim_t();
    
    void set_text_line(int32 line) { m_text_line = line; }
    void draw_title(int x, int y, const char *string);
    
    virtual void step(settings_t* settings);

    virtual void keyboard(unsigned char key) { B2_NOT_USED(key); }
    virtual void keyboard_up(unsigned char key) { B2_NOT_USED(key); }

    void shift_mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    virtual void mouse_down(const b2Vec2& p) { B2_NOT_USED(p); }
    virtual void mouse_up(const b2Vec2& p) { B2_NOT_USED(p); }
    void mouse_move(const b2Vec2& p) { B2_NOT_USED(p); }

    
    // Let derived tests know that a joint was destroyed.
    virtual void joint_destroyed(b2Joint* joint) { B2_NOT_USED(joint); }
    
    // Callbacks for derived classes.
    virtual void begin_contact(b2Contact* contact);
    virtual void end_contact(b2Contact* contact);
    virtual void pre_solve(b2Contact* contact, const b2Manifold* oldManifold);
    virtual void post_solve(const b2Contact* contact, const b2ContactImpulse* impulse)
    {
      B2_NOT_USED(contact);
      B2_NOT_USED(impulse);
    }

	inline b2World* get_world(void){
		return m_world;
	}
	
  //!How are protected members different from private memebers of a class in C++ ?
    /*! - Private members are only accessible within the class defining them.\n
          Protected members are accessible in the class that defines them and in classes that inherit from that class.
      * - Both are also accessible by friends of their class, and in the case of protected members, by friends of their derived classes.
    */


  protected:

    //! What are Friend classes?
    /*! - A friend class in C++, can access the "private" and "protected" members of the class in which it is declared as a friend.
     * - On declaration of friend class all member function of the friend class become friends of the class in which the friend class was declared.
     * - Friend status is not inherited; every friendship has to be explicitly declared.
     * - Friend classes can help in improving Encapsulation if used wisely.
    */
    friend class contact_listener_t;
    
    b2Body* m_ground_body;
    b2AABB m_world_AABB;
    contact_point_t m_points[k_max_contact_points];
    int32 m_point_count;

    debug_draw_t m_debug_draw;
    int32 m_text_line;
	MyContactListener mycontact;    
	b2World* m_world;

	

    int32 m_step_count;
    
    b2Profile m_max_profile;
    b2Profile m_total_profile;
  };

 

}

#endif
