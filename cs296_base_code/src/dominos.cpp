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
#define PI 3.14159265

namespace cs296
{
  dominos_t::dominos_t()
 {
 

   //Ground
   /*!World Ground which is Edge shaped is created extending from (-90.0f, -20.0f) to (90.0f, -20.0f). */
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, -20.0f), b2Vec2(90.0f, -20.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }
      
    /*!Top horizontal shelf(box shaped) where the train of balls is placed.  */
    {
      b2PolygonShape shape;
      /*!Half Length of Top horizontal box is 6.0 and half width is 0.25 */
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      /*!Centre of Top Horizontal Shelf at (26.5f, 30.0f) */
      bd.position.Set(26.5f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
   
  /*! Another horizontal shelf which is inclined to left (left to the horizontal shelf containing train of balls)*/
    {
      b2PolygonShape shape;
       /*!Half Length of Left slant at the top is 12.0 and half width is 0.25 */
      shape.SetAsBox(12.0f, 0.25f, b2Vec2(-10.f,10.f), 0.0f);/////////////////////////////////////////////
	
      b2BodyDef bd;
      /*!Centre of Left slant at the top at (20.0f, 19.8f) inclined at an angle  0.04f * pi; */
      bd.position.Set(20.0f, 19.8f);
      bd.angle = 0.04f * b2_pi;
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

  /*!The pendulum that knocks the dominos off*/
    {
    /*!Component ball of pendulum is defined */
     b2Body* b2;
      {
			b2PolygonShape shape;
			 /*!Half Length of pendulum ball is 0.25 and half width is 0.5 */
			shape.SetAsBox(0.25f, 0.5f);
			  
			b2BodyDef bd;
			/*!Centre of Pendulum ball at (32.0f, 29.0f) */
			bd.position.Set(32.0f, 29.0f);
			b2 = m_world->CreateBody(&bd);
			b2->CreateFixture(&shape, 10.0f);
      }
      
      
	/*!Top Ball (which serves as hook where pendulum is attached) is made */
      b2Body* b4;//////////////////////////////////////////////////check if hook?
      {
			b2PolygonShape shape;
			/*!Half Length of pendulum hook is 0.5 and half width is 0.25 */
			shape.SetAsBox(0.5f, 0.5f);
			  
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			/*!Centre of Pendulum ball at (33.0f, 31.0f) with density  of 2.0 */
			bd.position.Set(33.0f, 31.0f);
			b4 = m_world->CreateBody(&bd);
			b4->CreateFixture(&shape, 2.0f);
      }
	/*!Revolute joint defined between hook and pendulum ball */
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(33.0f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

	/*!The large ball which is falling on the pulley box at top and serves as stimulus for the project */
    {
      b2Body* spherebody;
	/*!Ball defined as sphere of radius of 1.0 density 50.0 and centre of ball at (42.0f,35.0f) */
      b2CircleShape circle;
      circle.m_radius = 1.0;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 50.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      
      b2BodyDef ballbd;
	     ballbd.type = b2_dynamicBody;
	     ballbd.position.Set(42.0f,35.0f);
	     spherebody = m_world->CreateBody(&ballbd);
	   spherebody->CreateFixture(&ballfd);
     }
      
    /*!The train of small spheres at top horizontal shelf*/
    {
      b2Body* spherebody;
		/*!Each ball is circle shaped of radius 0.6 , density 3.0 and dynamic(can move) */
      b2CircleShape circle;
      circle.m_radius = 0.6;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 3.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i <4; ++i)
    	{
    	  b2BodyDef ballbd;
    	  ballbd.type = b2_dynamicBody;
    	  ballbd.position.Set(27.5f + i*1.0, 31.25f);
    	  spherebody = m_world->CreateBody(&ballbd);
    	  spherebody->CreateFixture(&ballfd);
    	}
    }
    
    
    /*!The hangings at top*/
    {
    
    	/*!Each hanging is box shaped with half length 0.2f and half height 3.5 and dynamic(can move) with density 0.2f */
		 for (int i=0;i<4;i++)
		 {
		   b2PolygonShape shape;
		   shape.SetAsBox(0.2f, 3.5);
	  
		   b2BodyDef bd;
		   bd.position.Set(19.5f-i*2, 34.25f);
		   bd.type = b2_dynamicBody;
		   b2Body* body = m_world->CreateBody(&bd);
		   b2FixtureDef *fd = new b2FixtureDef;
		   fd->density = 0.2f;
		   fd->shape = new b2PolygonShape;
		   fd->shape = &shape;
		   body->CreateFixture(fd);

		   b2BodyDef bd3;
		   bd3.position.Set(19.5f-i*2, 37.75f);
		   b2Body* body3 = m_world->CreateBody(&bd3);
		   //b2FixtureDef *fd3 = new b2FixtureDef;
	  
			/*!Each hanging has a Revolute joint attached to it with a ball lying at one of it's edges */
		   b2RevoluteJointDef jointDef;
		   jointDef.bodyA = body;
		   jointDef.bodyB = body3;
		   /*!Joint is defined at (0,3.5) of the hanging (in local coordinates) */
		   jointDef.localAnchorA.Set(0,3.5);
		   jointDef.localAnchorB.Set(0,0);
		   jointDef.collideConnected = false;
		   m_world->CreateJoint(&jointDef);
		   }
    }

    /*!The pulley system (near pendulum)*/
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(42,28);
      bd->fixedRotation = true;
      
      /*!Component open box of pendulum is defined */
      /*!It is composed of three edges each having density 10.0 friction 0.5 */
      //First Edge
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
	  /*!half length is 2 , half height is 0.2 f , centre in local coordinates is (0.f,-1.9f) */
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;

     //Second Edge
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);//half length is 0.2 , half height is 2 f , centre in local coordinates is (2.0f,0.f)
      fd2->shape = &bs2;

	//Third Edge
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2,b2Vec2(-2.0f,0.f), 0);//half length is 0.2 , half height is 2 f , centre in local coordinates is (-2.0f,0.f)
      fd3->shape = &bs3;
       
      //Three bodies added to the box
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      /*! Component Bar is defined is defined centre at (37,28) and density 34.0*/
      bd->position.Set(37,28);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      /*! Component pulley joint is defined with anchor on the open box and Bar*/
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(42, 35); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(37, 35); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

    /*!The revolving horizontal platform is defined*/
    {
      b2PolygonShape shape;
      shape.SetAsBox(3.05f, 0.2f);
	/*!Half Length of revolvong horizontal platform is 3.05 and half-width is 0.2 with its centre at (34.0,28.0) and density 1 */
      b2BodyDef bd;
      bd.position.Set(34.0f, 28.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

	/*!Small ball which is invisible and serves as hook for the pendulum */
      b2PolygonShape shape2; //////////////////////////////////////
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(34.0f, 28.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

	/*!Revolute joint defined for horizontal platform */
      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

	/*!The see-saw system at the bottom*/
    {
      /*!The triangle wedge is defined as a set of three vertices with density 10.0 and centre (29.0f, 3.0f)*/
      b2Body* sbody;
      b2PolygonShape poly;
      b2Vec2 vertices[3];
      vertices[0].Set(-2,0);
      vertices[1].Set(2,0);
      vertices[2].Set(0,3.2);
      poly.Set(vertices, 3);
      b2FixtureDef wedgefd;
      wedgefd.shape = &poly;
      wedgefd.density = 10.0f;
      wedgefd.friction = 0.0f;
      wedgefd.restitution = 0.0f;
      b2BodyDef wedgebd;
      wedgebd.position.Set(29.0f, 3.0f);
      sbody = m_world->CreateBody(&wedgebd);
      sbody->CreateFixture(&wedgefd);

      /*!The plank on top of the wedge with half width 5.8 and half length 0.1 and centre at (29.0f,6.0f) and centre 1.0f*/
      b2PolygonShape shape;
      shape.SetAsBox(5.8f, 0.1f);
      b2BodyDef bd2;
      bd2.position.Set(29.0f,6.0f);
      bd2.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd2);
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape;
      body->CreateFixture(fd2);
      
      
      /*!balls on see-saw system*/
      float posx=26.72 , posy=6.5;
      b2Body* spherebody;
	
	/*!Each ball has radius 0.6 and density 1.0 and its type is dynamic body */
      b2CircleShape circle;
      circle.m_radius = 0.6;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
	
      for (int i = 0; i < 4; ++i)
    	{
    	  b2BodyDef ballbd;
    	  ballbd.type = b2_dynamicBody;
    	  ballbd.position.Set(posx+i*(7.6)/5, posy);
    	  spherebody = m_world->CreateBody(&ballbd);
    	  spherebody->CreateFixture(&ballfd);
    	}
      
      /*!Revolute joint is defined at (29.0f, 6.0f) joint wedge and the middle of plank on its top */

      b2RevoluteJointDef jd;
      
      b2Vec2 anchor;
      anchor.Set(29.0f, 6.0f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
      }


	/*!slant where the other ball rolls and hits the first set of dominoes*/
	{
		b2PolygonShape horizshape;
		/*!Half height of this slant is 8.0 and half width 0.1  centre at (-4.0f, 34.5f) and angle  */
		horizshape.SetAsBox(8.0f, 0.1f, b2Vec2(-10.f,10.f), 0.0f);
	
		b2BodyDef bdh;
		bdh.position.Set(-4.0f, 34.5f);
		bdh.angle = 0.90f * b2_pi;
		b2Body* hground = m_world->CreateBody(&bdh);
		hground->CreateFixture(&horizshape, 0.0f);
	    }
	    
     /*! the ball which rolls and hits first set of dominoes*/
	 {
		b2Body* spherebody;
		
		/*!The ball is circle shaped with radius 0.6 and density 1 and centre at (-5.0, 25.5f) */
		b2CircleShape circle;
		circle.m_radius = 0.6;
	
		b2FixtureDef ballfd;
		ballfd.shape = &circle;
		ballfd.density = 1.0f;
		ballfd.friction = 0.0f;
		ballfd.restitution = 0.0f;
		
		b2BodyDef ballbd;
		ballbd.type = b2_dynamicBody;
		ballbd.position.Set(-5.0, 25.5f);
		spherebody = m_world->CreateBody(&ballbd);
		spherebody->CreateFixture(&ballfd);
	     }
	     
 
 
	 /*! this is the horizontal shelf containing first set of train of dominoes  with width 8 and height as 0.1 and center around (-10,10)*/
	{
		b2PolygonShape horizshape;
		horizshape.SetAsBox(4.0f, 0.05f, b2Vec2(-10.f,10.f), 0.0f);
	
		b2BodyDef bdh;
		bdh.position.Set( 24.0f, 7.45f);
		b2Body* hground = m_world->CreateBody(&bdh);
		hground->CreateFixture(&horizshape, 0.0f);
	    }

    /*! This creates an horizontal set of Dominos lined one after the other there are 4 dominos that area created */
	/*! These are at a higher level then the second set and the third set of dominos*/
	/*! each Domino has density 20 anf friction between them 0.1*/
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 4; ++i)
      {
      	  b2BodyDef bd;
      	  bd.type = b2_dynamicBody;
      	  bd.position.Set(12.0f + 1.0f * i, 18.6f);
      	  b2Body* body = m_world->CreateBody(&bd);
      	  body->CreateFixture(&fd);
      }
    }


	/*! the ball beside Dominos which is supposed to fall and trigger some more dominos to fall */
{
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.6;
	
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.0f;
      
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(17.0f, 18.60f);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);
     }



 	/*! the left slant shelf shelf beside the shelf having first set of dominos which gives path for the ball to collide with other balls */
{
      b2PolygonShape horizshape;
      horizshape.SetAsBox(4.0f, 0.05f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bdh;
      bdh.position.Set( -6.3f, 22.67f);
      bdh.angle = -0.9f * b2_pi;
      b2Body* hground = m_world->CreateBody(&bdh);
      hground->CreateFixture(&horizshape, 0.0f);
    }

	/*! this is the right slant shelf beside the shelf having first set of dominos the whole structure along with the left slant and the horizontal looks like a table with slanted legs.*/
    {
      b2PolygonShape horizshape;
      horizshape.SetAsBox(4.0f, 0.05f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bdh;
      bdh.position.Set( 19.0f, 29.0f);
      bdh.angle = 0.8f * b2_pi;
      b2Body* hground = m_world->CreateBody(&bdh);
      hground->CreateFixture(&horizshape, 0.0f);
    }

	/*! the horizontal shelf containing second set of dominos. These dominons are supposed to trigger some other set which is at a bit higher level form her*/
	/*! These body is set as a box with hight = 0.2f and widht = 6 */
{
      b2PolygonShape horizshape;
      horizshape.SetAsBox(3.0f, 0.1f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bdh;
      bdh.position.Set( 38.5f, 1.5f);
      b2Body* hground = m_world->CreateBody(&bdh);
      hground->CreateFixture(&horizshape, 0.0f);
    }
	/* This is the horizontal shelf containing the third set of dominos which are supposed to trigger a ball to fall upon the button to play song*/
{
      b2PolygonShape horizshape;
      horizshape.SetAsBox(3.0f, 0.1f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bdh;
      bdh.position.Set( 44.5f, 2.25f);
      b2Body* hground = m_world->CreateBody(&bdh);
      hground->CreateFixture(&horizshape, 0.0f);
    }

  /* The horizontal set of Dominos (second set) are created here each domino has a height of 2 and width 0.2 */
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 5; ++i)
    	{
    	  b2BodyDef bd;
    	  bd.type = b2_dynamicBody;
    	  bd.position.Set(27.0f + 1.0f * i, 12.5f);
    	  b2Body* body = m_world->CreateBody(&bd);
    	  body->CreateFixture(&fd);
    	}
    }


  /* The horizontal set of Dominos (third set) are created here each domino has a height of 2 and width 0.2 */
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
	/* There are supposed to be 4 dominos out there */	
      for (int i = 0; i < 3; ++i)
    	{
    	  b2BodyDef bd;
    	  bd.type = b2_dynamicBody;
    	  bd.position.Set(32.0f + 1.0f * i, 13.5f);
    	  b2Body* body = m_world->CreateBody(&bd);
    	  body->CreateFixture(&fd);
    	}
    }

/*! The  ball beside third set of dominos which has a b2Body type as spherebody and density = 1.0 friction = 0.0f coeffcient of restitution = 0.75 */
{
		
		
      b2Body* spherebody;
	
      b2CircleShape circle;
      circle.m_radius = 0.6;
      b2FixtureDef ballfd;
      ballfd.shape = &circle;
      ballfd.density = 1.0f;
      ballfd.friction = 0.0f;
      ballfd.restitution = 0.75f;
      
      b2BodyDef ballbd;
      ballbd.type = b2_dynamicBody;
      ballbd.position.Set(37.0f, 12.60f);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);
   
}
//****************************

/* this is the body which is created for the alarm that rings when a ball falls on it in the left part of the simulation */
/* It is a smaller body mounted on a bigger horizontal body to make it look like a button*/
	{
		b2BodyDef* bd = new b2BodyDef;
		bd->fixedRotation=true;
			
		b2FixtureDef *fd1 = new b2FixtureDef;

		fd1->shape = new b2PolygonShape;
		b2PolygonShape bs1;
		bs1.SetAsBox(5.5,0.2,b2Vec2(40,-1),0);
		fd1->shape= &bs1;
		b2Body * box2 = m_world->CreateBody(bd);
		box2->CreateFixture(fd1);
	
	}


	{
		b2BodyDef* bd = new b2BodyDef;
		bd->fixedRotation=true;
			
		b2FixtureDef *fd1 = new b2FixtureDef;

		fd1->shape = new b2PolygonShape;
		b2PolygonShape bs1;
		bs1.SetAsBox(2,1,b2Vec2(40,0),0);
		fd1->shape= &bs1;
		b2Body * box2 = m_world->CreateBody(bd);
		box2->CreateFixture(fd1);
//ends 	
	}		
	/*! This creates an object of the ball class(It is not actually a ball but a bar It is just a surface which is supposed to be but on the button's top so that it detect a collision with the ball plays the sound) with center as (40,1) */
	Ball *b= new Ball(m_world,38,1,42,1);
	


/*! These are to the right side of the simulation */
/*! Right Side Slants */
  
  b2EdgeShape shape;
  /*! right slant 1 */
  {	
      b2Body* rightslant1;
      shape.Set(b2Vec2(-7.0f, 26.0f), b2Vec2(-25.0f, 23.0f));
      
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2EdgeShape;
      fd->shape = &shape;
      fd->friction=1.0f;

	
      b2BodyDef bd;
      rightslant1 = m_world->CreateBody(&bd);
      rightslant1->CreateFixture(fd);
  }
  
  /*! right slant 2 from top  */
  {
      b2Body* rightslant2;
      
      shape.Set(b2Vec2(-6.0f, 18.0f), b2Vec2(-25.0f,15.0f));
	
      b2BodyDef bd;
      rightslant2 = m_world->CreateBody(&bd);
      rightslant2->CreateFixture(&shape, 0.0f);
  }
  
  /*! right slant 3 from top  */
 {
      b2Body* rightslant2;
    
      shape.Set(b2Vec2(-6.0f, 10.0f), b2Vec2(-25.0f, 7.0f));
	
      b2BodyDef bd;
      rightslant2 = m_world->CreateBody(&bd);
      rightslant2->CreateFixture(&shape, 0.0f);
  }
  
  /*! left slant 1 from top */
 
  {
      b2Body* leftslant1;
      
      shape.Set(b2Vec2(-45.0f, 28.0f), b2Vec2(-25.0f, 21.0f));
	
      b2BodyDef bd;
      leftslant1 = m_world->CreateBody(&bd);
      leftslant1->CreateFixture(&shape, 0.0f);
  }
  
  /*! left slant 1 from top */
  {
      b2Body* leftslant2;
      
      shape.Set(b2Vec2(-45.0f, 19.0f), b2Vec2(-25.0f, 13.0f));
	
      b2BodyDef bd;
      leftslant2 = m_world->CreateBody(&bd);
      leftslant2->CreateFixture(&shape, 0.0f);
  }
  

  /*! left slant 1 from top */
  {
      b2Body* leftslant3;
      
      shape.Set(b2Vec2(-45.0f, 10.0f), b2Vec2(-25.0f, 5.0f));
	
      b2BodyDef bd;
      leftslant3 = m_world->CreateBody(&bd);
      leftslant3->CreateFixture(&shape, 0.0f);
  }
  

  /*!Edge shaped shelf below slants*/
  {
      b2Body* shelf;
      
      shape.Set(b2Vec2(-23.0f, -5.0f), b2Vec2(10.0f, -2.0f));
	
      b2BodyDef bd;
      shelf = m_world->CreateBody(&bd);
      shelf->CreateFixture(&shape, 0.0f);
  }
  
     
     
     float shiftX=-12.0f;
     float shiftY=-10.0f;
  
  /*!Pulley System near ground*/
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(shiftX-16,shiftY-1);
      bd->fixedRotation = true;
      
      /*!The open box which is composed of three edges which are box shaped*/
      /*!First edge which constitutes box density is 10.0 , friction 0.5 half length 3.5 , half width 0.2 ,center of box at (0,3.2) */
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(3.5,0.2, b2Vec2(0.f,-3.2f), 0);
      fd1->shape = &bs1;
      
      /*!Second edge which constitutes box density is 10.0 , friction 0.5 , half length 0.2 , half width 3.5 ,center of box at (3.2,0) */
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,3.5, b2Vec2(3.2f,0.f), 0);
      fd2->shape = &bs2;
      
      /*!Second edge which constitutes box density is 10.0 , friction 0.5 , half length 0.2 , half width 3.5 ,center of box at (-3.2,0) */
      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,3.5, b2Vec2(-3.2f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      /*The bar attached to pulley is made with density 37*/
      bd->position.Set(shiftX+7,shiftY-1);	
      fd1->density = 37.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      /*! The pulley joint between box and the bar*/
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(shiftX-16, shiftY-2); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(shiftX+7, shiftY-1); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(shiftX-16, shiftY-1); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(shiftX+7, shiftY+4); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

	/*!Alarm system below is defined*/

    	/*!Shelf on top is defined with half width 5.5 and half height 0.2 with centre of box (0,-9)*/

	{
		b2BodyDef* bd = new b2BodyDef;
		bd->fixedRotation=true;
			
		b2FixtureDef *fd1 = new b2FixtureDef;

		fd1->shape = new b2PolygonShape;
		b2PolygonShape bs1;
		bs1.SetAsBox(5.5,0.2,b2Vec2(0,-9),0);
		fd1->shape= &bs1;
		b2Body * box2 = m_world->CreateBody(bd);
		box2->CreateFixture(fd1);
	
	}

	/*!shelf below that is defined with half width 2.5 and half height 1 with centre of box (0,-10.1)*/
	{
		b2BodyDef* bd = new b2BodyDef;
		bd->fixedRotation=true;
			
		b2FixtureDef *fd1 = new b2FixtureDef;

		fd1->shape = new b2PolygonShape;
		b2PolygonShape bs1;
		bs1.SetAsBox(2.5,1,b2Vec2(0,-10.1),0);
		fd1->shape= &bs1;
		b2Body * box2 = m_world->CreateBody(bd);
		box2->CreateFixture(fd1);

	}

	/*! This creates an object of the ball class(It is not actually a ball but a bar It is just a surface which is supposed to be but on the button's top so that it detect a collision with the ball plays the sound) with center as (0,-11.1) (Starts at (-2.5,-11.1) and ends at (2.5,-11.1)) */
	Ball * Alarm2 = new Ball(m_world,-2.5,-11.1,2.5,-11.1);
     
     float pi=3.14;
     float centrex=19.7f,centrey=3.0f,radius=4.5f;
     /*! Curve is made as a sequence of edges*/
     for(int i=0;i<50;i++)
     {
     	 shape.Set(b2Vec2(centrex+radius*cos(pi*i/100.0f),centrey-radius*sin(pi*i/100.0f)), b2Vec2(centrex+radius*cos(pi*(i+1)/100.0f), centrey-radius*sin(pi*(i+1)/100.0f)));
     	 b2Body* rightslant1;
     	  b2BodyDef bd;
      rightslant1 = m_world->CreateBody(&bd);
      rightslant1->CreateFixture(&shape, 0.0f);
     }
     
     {
     shape.Set(b2Vec2(centrex+radius*cos(pi*50/100.0f),centrey-radius*sin(pi*50/100.0f)), b2Vec2(centrex+radius*cos(pi*(50)/100.0f)-10, centrey-radius*sin(pi*(50)/100.0f)));
     b2Body* rightslant1;
     	  b2BodyDef bd;
      rightslant1 = m_world->CreateBody(&bd);
      rightslant1->CreateFixture(&shape, 0.0f);
      }


	/*! Plate near the slant and below part blocking ball falling on dominos*/
	/*!It comprises of a slant box which is dynamic and attached by a small body(which is invisible since it's fixture is not defined) and by a RevoluteJoint*/
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.2f, 1.7f);
  
      b2BodyDef bd;
      bd.position.Set(-3.5f, 26.0f);//set position
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.2f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(2.0f, 0.0f);
      b2BodyDef bd2;
      bd2.position.Set(-3.5f, 26.0f);//set position
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(-0.5,0);
      jointDef.localAnchorB.Set(-0.5,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }
    /*!Set of windmills is defined */
    /*!Each star (a windmill) is made of two box one horizontal and one vertical which is attached with a small shape(not visible to world) using a joint */
 	/*!The star left*/
    {
      /*!Center of body is at (-3.3f, 10.67f) */
  	/*!First component of star whose half-width is 2.2f and half-height 0.2f */
  	b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
      b2BodyDef bd;
      bd.position.Set(-3.3f, 10.67f);//Center of Body is set
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

	/*!Second component of star whose half-width is 0.2f and half-height 2.0f */
      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
       b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body->CreateFixture(fd2);


  	/*!Hook-The part to which star is attached and is invisible since fixture is not there with its position at centre of star*/
      b2BodyDef bd3;
      bd3.position.Set(-3.3f, 10.67f);
      b2Body* body3 = m_world->CreateBody(&bd3);
     
     /*!Revolute Joint defined between star and hook */
      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

	/*!The star at the top*/
    {
    
    /*!Center of body is at(1.5f, 0.2f) */
  	/*!First component of star whose half-width is 1f and half-height 10.2f,density 1 */
      b2PolygonShape shape;
      shape.SetAsBox(1.5f, 0.2f);
  
      b2BodyDef bd;
      bd.position.Set(1.0f, 10.2f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);
	
	/*!Second component of star whose half-width is 0.2f and half-height 1.5f */

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 1.5f);
       b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body->CreateFixture(fd2);


  	/*!Hook-The part to which star is attached and is invisible since fixture is not there with it's position at the centre of star*/
      b2BodyDef bd3;
      bd3.position.Set(1.0f, 10.2f);
      b2Body* body3 = m_world->CreateBody(&bd3);
      
  	/*!Revolute Joint between Star and the hook */

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);


    }
    
    
    
    
    /*!The star to the right*/
    {
    /*!Center of body is at(1.5f, 0.2f) */
  	/*!First component of star whose half-width is 1f and half-height 10.2f,density 1 */
      b2PolygonShape shape;
      shape.SetAsBox(1.5f, 0.2f);
  
      b2BodyDef bd;
      bd.position.Set(3.7f, 8.2f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

	/*!Second component of star whose half-width is 0.2f and half-height 1.5f and density 1f*/

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 1.5f);
       b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body->CreateFixture(fd2);


  	/*!Hook-The part to which star is attached and is invisible since fixture is not there with it's position at the centre of star*/
      b2BodyDef bd3;
      bd3.position.Set(3.7f, 8.2f);
      b2Body* body3 = m_world->CreateBody(&bd3);
      
	/*!Revolute Joint between Star and the hook */
      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);


    }
    
    
    
    /*!The star below(All attributes same as previous star with different coordinates)*/
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.5f, 0.2f);
  
      b2BodyDef bd;
      bd.position.Set(3.2f, 5.2f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);


      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 1.5f);
       b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body->CreateFixture(fd2);


  
      b2BodyDef bd3;
      bd3.position.Set(3.2f, 5.2f);
      b2Body* body3 = m_world->CreateBody(&bd3);
      

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);


    }
    
    
    
    
    /*!The star middle which drives other stars*/
    {
      b2PolygonShape shape;
      shape.SetAsBox(1.5f, 0.2f);
  
      b2BodyDef bd;
      bd.position.Set(1.0f, 7.5f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);


      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 1.5f,b2Vec2(0, 0),pi/2.0);
       b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body->CreateFixture(fd2);
      
      
  
      b2BodyDef bd3;
      bd3.position.Set(1.0f, 7.5f);
      b2Body* body3 = m_world->CreateBody(&bd3);
    
	
      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
     
     /*!Motor is enabled for this joint with motor speed 2*pi and Maximium Torque of motor 5 */
	jointDef.enableMotor = true;
	jointDef.motorSpeed = 2*pi;
	jointDef.maxMotorTorque = 5;
      m_world->CreateJoint(&jointDef);


    }

  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}
