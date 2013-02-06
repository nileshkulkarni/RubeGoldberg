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


#include "cs296_base.hpp"
#include "render.hpp"

#ifdef __APPLE__
	#include <GLUT/glut.h>
#else
	#include "GL/freeglut.h"
#endif

#include <cstring>
using namespace std;

#include "dominos.hpp"

namespace cs296
{
  dominos_t::dominos_t()
  {
  
  /*!
		Creating body is a six-step Process\n
  1. Define a variable for it's shape \n
  2. Add properties to the shape \n
  3. Define a variable for it's body definition \n
  4. Add properties to b2BodyDef type variable \n 
  5. Create body by calling function CreateBody with parameters as b2BodyDef variable. \n 
  6. Add fixture that binds shape to the body. \n
   
*/
  
  
  
  //Ground
    
    /*! ******To create Ground***** */
 
    
    b2Body* b1;
    {
      /*!1.Define a b2EdgeShape type variable (shape)*/
      b2EdgeShape shape;
     /*!2.Set initial coordinates (-90.0f,0.0f) and end-coordinates(90.0f,0.0f) by calling shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f)).*/
      shape.Set(b2Vec2(-90.0f, 0.0f), b2Vec2(90.0f, 0.0f));
	  
      /*! 3.Define a b2Bodydef type variable (bd) for Body Definitions(Properties of body)  */
      b2BodyDef bd;
      
      /*!4. Create body(b1) in world by calling function CreateBody with parameters as b2BodyDef variable(bd). */
      b1 = m_world->CreateBody(&bd);
      /*! 5. Add fixture that binds shape(shape) to the body(ground) of density 0.0f.\n \n */
      b1->CreateFixture(&shape, 0.0f);
    }
      
      
      
      
    /*!  **********Top horizontal shelf*************** */
    
   /*!To create a top horizontal shelf */ 
    
    {
      /*!   1.Define a b2PolygonShape type variable (shape)\n*/
      b2PolygonShape shape;
     /*! 2.Set it's shape as box (by calling shape.SetAsBox(6.0f,0.25f) ) of width 12.0f(half-width 6.0f) and height 0.5f(half-height 0.25f).*/
      shape.SetAsBox(6.0f, 0.25f);
	  
	/*!  3.Define a b2Bodydef type variable (bd) for Body Definitions(Properties of body) */
      b2BodyDef bd;
      
      /*! 4. Set it's initial position by calling bd.position.Set(-31.0f, 30.0f). So, it's initial position set to (-31.0f,30.0f)*/
      bd.position.Set(-31.0f, 30.0f);
      
     /*!5. Create body(ground) in world by calling function CreateBody with parameters as b2BodyDef variable(bd). */
      b2Body* ground = m_world->CreateBody(&bd);
      
      /*! 6. Add fixture that binds shape(shape) to the body(ground) of density 0.0f. */
      ground->CreateFixture(&shape, 0.0f);
      
    }
    
    
    
    
    

    /*! **********To create Dominos************ */
    
    {
      /*!1.Define a b2PolygonShape type variable (shape) */
      b2PolygonShape shape;
     /*!2.Set it's shape as box (by calling shape.SetAsBox(0.1f,1.0f) ) of width  0.2f(half-width 0.1f) and height 2.0f(half-height 1.0f). */
      shape.SetAsBox(0.1f, 1.0f);
	
     /*! 3.Define a b2FixtureDef type variable (fd) for Fixture Definitions(Properties of fixture)  */ 
      b2FixtureDef fd; 
       
      /*!4. Set it's shape (fd.shape = &shape) , density as 20.0f (fd.density = 20.0f) , friction 0.1f (fd.friction = 0.1f) */
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
	/*! 5. Now run a loop to create 10 Dominoes.In a particular loop*/
		  for (int i = 0; i < 10; ++i)
		{
		  /*! a) Create a b2BodyDef type variable for body Definitions:Properties of the body. (bd)*/
		  b2BodyDef bd;
		  /*!b) Set it's type as Dynamic Body as they will be moving and not static. (bd.type = b2_dynamicBody) */
		  bd.type = b2_dynamicBody;
		  
		  /*!c) Set initial position of each Dominos which is different and dependent on i (bd.position.Set(-35.5f + 1.0f * i, 31.25f)) .X-coordinate :-35.5f + 1.0f * i and X-coordinate : 31.25f */
		  bd.position.Set(-35.5f + 1.0f * i, 31.25f);
		  
		 /*! d) Create body with body Definition(bd) in the world .*/
		  b2Body* body = m_world->CreateBody(&bd);
		  
		  /*!e) Add fixture fd to this pointer to Dominos(body). */
		  body->CreateFixture(&fd);
		}
    }
    
    
      
    /*!*************Another horizontal shelf**************** */
    
    
    {
     /*!  1.Define a b2PolygonShape type variable (shape)*/
      b2PolygonShape shape;
     /*! 2.Set it's shape as box (by calling shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f) ) of width 14.0f(half-width 7.0f), height 0.5f(half-height 0.25f), center point as b2Vec2(-20.f,20.f) and angle of rotation of ball in local co-ordinates as 0.0f . */
      shape.SetAsBox(7.0f, 0.25f, b2Vec2(-20.f,20.f), 0.0f);
	
	 /*!3.Define a b2Bodydef type variable (bd) for Body Definitions(Properties of body)  */
      b2BodyDef bd;
      /*! 4. Set it's initial position by calling bd.position.Set(1.0f, 6.0f). So, it's initial position set to (1.0f, 6.0f) */
      bd.position.Set(1.0f, 6.0f);
      /*!5. Create a body in world with body definition bd. */
      b2Body* ground = m_world->CreateBody(&bd);
      /*!6. Add fixture that binds shape(shape) to the body(ground) of density 0.0f. \n \n */
      ground->CreateFixture(&shape, 0.0f);
    }




    /*! *********The pendulum that knocks the dominos off********** */
 
   
    {
    	/*! i) Create a pendulum stick : b2Body* b2*/
		  b2Body* b2;
		  {
		  /*! 1.Define a b2PolygonShape type variable (shape) */
		  
			b2PolygonShape shape;
			/*! 2.Set it's shape as box (by calling shape.SetAsBox(0.25f, 1.5f) ) of width 0.5f(half-width 0.25f) and height 3.0f(half-height 1.5f).*/
			shape.SetAsBox(0.25f, 1.5f);
			 /*! 3.Define a b2Bodydef type variable (bd) for Body Definitions(Properties of body) */
			b2BodyDef bd;
			/*!4. Set it's initial position by calling b..position.Set(-36.5f, 28.0f). So, it's initial position set to (-36.5f, 28.0f) */
			bd.position.Set(-36.5f, 28.0f);
			/*!5. Create body(ground) by calling function CreateBody with parameters as b2BodyDef variable(bd). */
			b2 = m_world->CreateBody(&bd);
			/*!  6. Add fixture that binds shape(shape) to the body(ground) of density 0.0f.   */
			b2->CreateFixture(&shape, 10.0f);
		  }
	//To create a pendulum ball
	
	
		/*! ii) Create a Pendulum Ball : b2Body* b4;*/
		
		  b2Body* b4;
		  {
			/*! 1. Define a b2PolygonShape type variable (shape)*/
			b2PolygonShape shape;
			/*! 2. Set it's shape as box (by calling shape.SetAsBox(0.25f, 0.25f) ) of width 0.5f(half-width 0.25f) and height 0.5f(half-height 0.25f).*/
			shape.SetAsBox(0.25f, 0.25f);
			/*!3. Define a b2Bodydef type variable (bd) for Body Definitions(Properties of body) */
			b2BodyDef bd;
			/*!4. Set it's type as Dynamic Body as they will be moving and not static. (bd.type = b2_dynamicBody) */
			bd.type = b2_dynamicBody;
			/*! 5.Set it;s position to (-40.0f, 33.0f)*/
			bd.position.Set(-40.0f, 33.0f);
			/*! 6. Create body(b4) by calling function CreateBody with parameters as b2BodyDef variable(bd).*/
			b4 = m_world->CreateBody(&bd);
			/*! 7. Add fixture shape to b4 and set it's density to 2.0f(b4->CreateFixture(&shape, 2.0f))*/
			b4->CreateFixture(&shape, 2.0f);
		  }
		  
		   
			/*!iii). Create a joint between Pendulum Stick and Pendulum ball */
			 /*!1. Create a b2RevoluteJointDef type variable (jd) to store definitions(properties of a Revolute Type joint. */
		  b2RevoluteJointDef jd;
		 /*! 2. Create a b2Vec2 type variable (anchor) where the bodies are joined.*/
		  b2Vec2 anchor;
		  /*!3. Set the position of this anchor to (-37.0f , 40.0f) [anchor.Set(-37.0f, 40.0f)].So bodies b2 b4 are joined at the point(anchor). */
		  anchor.Set(-37.0f, 40.0f);
		  /*!4. Initialize bodies b2,b4 (bodies connected by joint) and anchor(anchor). */
		  jd.Initialize(b2, b4, anchor);
		  /*!5. Now create the joint by calling CreateJoint with parameters as b2RevoluteJointDef type variable (jd). */
		  m_world->CreateJoint(&jd);
    }
    
    
    
    
      
    //The train of small spheres
    /*! ******The train of small spheres************* */
   
    {
    /*! 1. Create a pointer to b2Body type variable named spherebody for the body of sphere. */
      b2Body* spherebody;
	  /*! 2. Create a b2CircleShape type variable (circle) for the shape of sphere*/
      b2CircleShape circle;
      /*! 3. Set the radiuse of circle variable to 0.5 */
      circle.m_radius = 0.5;
	  /*! 4. Create a b2FixtureDef type variable (ballfd) for storing Fixture Definitions(Properties of Fixture).*/
      b2FixtureDef ballfd;
      /*! 5. Set it's properties: shape as circle (ballfd.shape = &circle) , density as 1.0f , friction 0.0f and restitution 0.0f.*/
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      
	/*!6. Now Run a loop for creating 10 spheres of same body definition and same fixture definitions */
		  for (int i = 0; i < 10; ++i)
		  {
		  	  /*! a) Create a b2BodyDef type variable for body Definitions:Properties of the ball. (ballbd)*/
			  b2BodyDef ballbd;
			  /*!	b) Set it's type as Dynamic Body as they will be moving and not static. (ballbd.type = b2_dynamicBody) */
			  ballbd.type = b2_dynamicBody;
			  /*! c) Set initial position of each ball which is different and dependent on i (ballbd.position.Set(-22.2f + i*1.0, 26.6f)) .X-coordinate :-22.2f + i*1.0 and X-coordinate : 26.6f*/
			  ballbd.position.Set(-22.2f + i*1.0, 26.6f);
			  /*!d) Create the sphere(spherebody) of body definition ballbd. */
			  spherebody = m_world->CreateBody(&ballbd);
			  /*!e) Add fixture ballfd to this ball(spherebody). */
			  spherebody->CreateFixture(&ballfd);
		   }
    }
    
    
    
    
    

    
    /*! *********The pulley system********** */
   

    /*!Bar---->*/
    
    {
    /*!1. Create a pointer to b2BodyDef type variable bd. */
      b2BodyDef *bd = new b2BodyDef;
      /*!2. Set it's type to dynamic (bd->type = b2_dynamicBody) */
      bd->type = b2_dynamicBody;
      /*!  3. Set position property of bd to (-10,15) (bd->position.Set(-10,15))*/
      bd->position.Set(-10,15);
      /*!  4. Set the fixedRotaion property true which will enable body to have fixed rotation.\n \n \n */
      bd->fixedRotation = true;
      
     
      /*! The open box---> */
      /*
      
      
     
      
      
      */
      
      /*! First Base*/
      
      /*!1. Create fisture definition for first base:: Create a pointer to b2FixtureDef type variable fd1 to set the properties of fixture of the open box */
      b2FixtureDef *fd1 = new b2FixtureDef;
      /*!2. Set it's friction to 10.0 , friction=0.5,restitution = 0.f, shape as b2PolygonShape. */
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      
      
      /*!  3. Now create shape for first base :: Create a b2PolygonShape variable bs1 and set it as box with 4 width(2 half-width), 0.4 height (0.2 half-height) , center at b2Vec2(0.f,-1.9f) and 0 angle of rotation of box in local coordinates*/
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      /*!4. Now set shape for first base in the fixture (fd1->shape = &bs1) */
      fd1->shape = &bs1;
      
      
     /*! Second base */
      /*! 5. Similarly do this for second base and Third base.*/
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;
      
      
      //Third base
      
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2, b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       
       
      /*! Box---->*/
      /*! 1. Create the body with body definition bd and add fixture Definitions fd1,fd2,fd3 to it */
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);



      /*! **********The bar************ */

      /*!  1. Set the position of bar to (10,15)*/
      bd->position.Set(10,15);	
      /*! 2. Use the same fixture definition fd1 for rotating bar with density 34.0 */
      fd1->density = 34.0;	  
      /*! 3.Create pointer of b2Body type variable denoting the bar with body definition same as bd */
      b2Body* box2 = m_world->CreateBody(bd);
      /*! 4. Add fixture definition fd1 to it.*/
      box2->CreateFixture(fd1);



      /*! ********The pulley joint************* */
     
      /*! 1. Create a pointer to b2PulleyJointDef type variable for Pulley type joint(myjoint) */
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      
      /*!2.Anchor point on body 1,body 2 in world axis */
      b2Vec2 worldAnchorOnBody1(-10, 15);  
      b2Vec2 worldAnchorOnBody2(10, 15); 
      
      /*!3.Anchor point for ground 1,ground 2 in world axis */
      b2Vec2 worldAnchorGround1(-10, 20); // 
      b2Vec2 worldAnchorGround2(10, 20); // Anchor point for ground 2 in world axis
      /*!4.Define pulley ratio */
      float32 ratio = 1.0f;
      /*!5. Initialize the pulley with two bodies, 2 ground anchors and two body anchors(which is center of their bodies) and a pulley ratio. */
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      /*!6.Create a joint in world with myjoint as definition. */
      m_world->CreateJoint(myjoint);
    }



    /*! *********The revolving horizontal platform************ */
   
    {
    /*!  LeftMost part of Platform --------->*/
    /*!1.Create a b2PolygonShape type variable shape and set it as box of 4.4f width(2.2f half-width) and 0.4f height(0.2f half-height). */
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
	/*!2.Create a b2BodyDef variable bd for body definitions(Properties) */
      b2BodyDef bd;
      /*! 3.Set it's initial position as (14.0f, 14.0f) , type as dynamic as it will be moving  */
      bd.position.Set(14.0f, 14.0f);
      bd.type = b2_dynamicBody;
      /*!4. Create body in platform(body) with bd as Body definition */
      b2Body* body = m_world->CreateBody(&bd);
      /*! 5. Create a b2FixtureDef variable fd with density 1.f shape of b2PolygonShape type and set to shape defined earlier. */
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      /*!  6.Now add fixture definition fd to body.*/
      body->CreateFixture(fd);


	  /*!Second flat part of platform-----> */
	  
	  
	  /*! 1.Create a variable of type b2PolygonShape named shape2*/
      b2PolygonShape shape2;
      /*! 2.Set shape2 as box of 0.2f half-width and 2.0f half-height*/
      shape2.SetAsBox(0.2f, 2.0f);
      /*!3.Create a variable of type b2BodyDef named bd2 which is body definition for second part of platform(static part) */

      b2BodyDef bd2;
      /*!4. Set position of this part to (14.0f, 16.0f) */
      bd2.position.Set(14.0f, 16.0f);
      /*!5. Add this part to world. */
      b2Body* body2 = m_world->CreateBody(&bd2);


	
	/*! 1.Create a b2RevoluteJointDef type variable jointDef for create a Revolute Joint in the pulley joint.*/
      b2RevoluteJointDef jointDef;
      /*!2.Initialize bodyA to be body,bodyB to be body2, set of two local anchors at (0,0) that is origin of two bodies. */
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      /*!3.Set collideConnected to false which means that the two bodies doesnot collide */
      jointDef.collideConnected = false;
      /*!4.Add this joint to the world */
      m_world->CreateJoint(&jointDef);
    }

    /*! ******The heavy sphere on the platform********** */
   
    {
    /*!1.Create a b2Body variable sbody for sphere. */
      b2Body* sbody;
      /*! 2.Declare a b2CircleShape variable circle for the shape of sphere and set it's radius to 1.*/
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
	
	/*!3.Create a b2FixtureDef variable ballfd for fixture definitions of ball and set it's shape to circle,density = 50.0f,friction = 0.0f,restitution = 0.0f */
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      
      /*!4.Create a b2BodyDef variable bd for body definitions of sphere. */
      b2BodyDef ballbd;
      /*!5.Set it's type to dynamic as it will be moving and initial position to (14.0f, 18.0f) */
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(14.0f, 18.0f);
      /*!6.now add this body (sboody) to world with body definition ballbd and add fixture ballfd to it. */
      sbody = m_world->CreateBody(&ballbd);
      sbody->CreateFixture(&ballfd);
    }


    /*! ********The see-saw system at the bottom***********/
    {
      /*!The triangle wedge-----> */
      
      /*!1.Create a pointer to b2Body sbody and b2PolygonShape variable poly for setting shape of this body. */
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-1,0);
      vertices[1].Set(1,0);
      vertices[2].Set(0,1.5);
      poly.Set(vertices, 3);
      
      /*!2.Create an array of three vertices and set poly shape to this set of three vertices. */
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      
      /*!3.Create a  b2FixtureDef variable wedgefd for fixture definitions and set it's shape to poly,density = 10.0f,friction = 0.0f,restitution = 0.0f */
      b2BodyDef wedgebd;
      /*!4.Create a b2BodyDef variable wedgebd for bodydefinitions of this wedge and set it's initial position to (30.0f, 0.0f) */
      wedgebd.position.Set(30.0f, 0.0f);
      
      /*!5.Create a b2BodyDef variable wedgebd for bodydefinitions of this wedge and set it's initial position to (30.0f, 0.0f) */
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      /*! The plank on top of the wedge-------> */
     
      /*!1.Create a b2PolygonShape variable shape for setting shape of plankas box of 15.0f half-width and 0.2f half-height */
      b2PolygonShape shape;
      shape.SetAsBox(15.0f, 0.2f);
      /*!2.Create a b2BodyDef variable bd2 for body definitions of the plank and set it's type to dynamic as it will be moving. */
      b2BodyDef bd2;
      bd2.position.Set(30.0f, 1.5f);
      /*!3.Now create a body in the world with body Definition bd2. */
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      /*!4.Now create a fixture defintion fd2 and set it's density to 1f shape to be shape and add this fixture definition to the plank. */
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);


	 
	  /*!1.Create a b2RevoluteJointDef type variable jd and create anchor and set it's position to (30.0f, 1.5f) */
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(30.0f, 1.5f);
      /*!2.Now initialize joint jd with bodies sbody,body and anchor */
      jd.Initialize(sbody, body, anchor);
      /*! 3.Create this joint in the world. */
      m_world->CreateJoint(&jd);

      /*! ***********The light box on the right side of the see-saw************/
      
      /*! 1.Shape of Box: Create a b2PolygonShape shape2 and set this as box of 2.0 half-width and 2.0 half-height */
      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 2.0f);
      /*!2.Definition of box: Create a body Definition bd3 and set it's inital position to (40.0f, 2.0f) and type to dynamic body */
      b2BodyDef bd3;
      bd3.position.Set(40.0f, 2.0f);
      bd3.type = b2_dynamicBody;
      /*! 3.Create this body(body3) in world with body definition bd3.*/
      b2Body* body3 = m_world->CreateBody(&bd3);
      /*!4.Fixture of this body: Create a b2FixtureDef variable fd3 and set it's density = 0.01, shape to be shape2 and add this fixture to body body3. */
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 0.01f;
      fd3->shape = new b2PolygonShape;
      fd3->shape = &shape2;
      body3->CreateFixture(fd3);
    }
  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
