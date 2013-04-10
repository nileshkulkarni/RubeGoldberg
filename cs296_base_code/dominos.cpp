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
    b2Body* b1;
    {
      b2EdgeShape shape;
      shape.Set(b2Vec2(-90.0f, -20.0f), b2Vec2(90.0f, -20.0f));
	
      b2BodyDef bd;
      b1 = m_world->CreateBody(&bd);
      b1->CreateFixture(&shape, 0.0f);
    }
      
    //Top horizontal shelf where the train of balls's are placed. 
    {
      b2PolygonShape shape;
      shape.SetAsBox(6.0f, 0.25f);
	
      b2BodyDef bd;
      bd.position.Set(26.5f, 30.0f);
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }
   
  //  Another horizontal shelf which is inclined to left part (left to the train of balls)
    {
      b2PolygonShape shape;
      shape.SetAsBox(12.0f, 0.25f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bd;
      bd.position.Set(20.0f, 19.8f);
      bd.angle = 0.04f * b2_pi;
      b2Body* ground = m_world->CreateBody(&bd);
      ground->CreateFixture(&shape, 0.0f);
    }

//The pendulum that knocks the dominos off
    {
     b2Body* b2;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.25f, 0.5f);
	  
	b2BodyDef bd;
	bd.position.Set(32.0f, 29.0f);
	b2 = m_world->CreateBody(&bd);
	b2->CreateFixture(&shape, 10.0f);
      }
      
      
	
      b2Body* b4;
      {
	b2PolygonShape shape;
	shape.SetAsBox(0.5f, 0.5f);
	  
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	bd.position.Set(33.0f, 31.0f);
	b4 = m_world->CreateBody(&bd);
	b4->CreateFixture(&shape, 2.0f);
      }
	
      b2RevoluteJointDef jd;
      b2Vec2 anchor;
      anchor.Set(33.0f, 40.0f);
      jd.Initialize(b2, b4, anchor);
      m_world->CreateJoint(&jd);
    }

// the large ball which is falling
    {
      b2Body* spherebody;
	
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
      
    //The train of small spheres
    {
      b2Body* spherebody;
	
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
    
    
    
    //hangings at top
    
    //The hanging
    {
    
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
  

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,3.5);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
      }
    }

    //The pulley system (near pendulum)
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(42,28);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(2,0.2, b2Vec2(0.f,-1.9f), 0);
      fd1->shape = &bs1;

      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,2, b2Vec2(2.0f,0.f), 0);
      fd2->shape = &bs2;

      b2FixtureDef *fd3 = new b2FixtureDef;
      fd3->density = 10.0;
      fd3->friction = 0.5;
      fd3->restitution = 0.f;
      fd3->shape = new b2PolygonShape;
      b2PolygonShape bs3;
      bs3.SetAsBox(0.2,2,b2Vec2(-2.0f,0.f), 0);
      fd3->shape = &bs3;
       
      b2Body* box1 = m_world->CreateBody(bd);
      box1->CreateFixture(fd1);
      box1->CreateFixture(fd2);
      box1->CreateFixture(fd3);

      //The bar
      bd->position.Set(37,28);	
      fd1->density = 34.0;	  
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(10, 15); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(10, 15); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(42, 35); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(37, 35); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

    //The revolving horizontal platform
    {
      b2PolygonShape shape;
      shape.SetAsBox(3.05f, 0.2f);
	
      b2BodyDef bd;
      bd.position.Set(34.0f, 28.0f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);

      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
      b2BodyDef bd2;
      bd2.position.Set(34.0f, 28.0f);
      b2Body* body2 = m_world->CreateBody(&bd2);

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body2;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

//The see-saw system at the bottom
    {
      //The triangle wedge
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

      //The plank on top of the wedge
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
      
      
      //balls on see-saw system
      float posx=26.72 , posy=6.5;
      b2Body* spherebody;
	
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
      
      

      b2RevoluteJointDef jd;
      
      b2Vec2 anchor;
      anchor.Set(29.0f, 6.0f);
      jd.Initialize(sbody, body, anchor);
      m_world->CreateJoint(&jd);
      }


//slant where the other balls rolls and hitsthe first set of dominoes
{
      b2PolygonShape horizshape;
      horizshape.SetAsBox(8.0f, 0.1f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bdh;
      bdh.position.Set(-4.0f, 34.5f);
      bdh.angle = 0.90f * b2_pi;
      b2Body* hground = m_world->CreateBody(&bdh);
      hground->CreateFixture(&horizshape, 0.0f);
    }
    
     //the ball which rolls and hits first set of dominoes
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
      ballbd.position.Set(-5.0, 25.5f);
      spherebody = m_world->CreateBody(&ballbd);
      spherebody->CreateFixture(&ballfd);
     }
     
 
 
 // the horizontal shelf containing first set of train of dominoes
{
      b2PolygonShape horizshape;
      horizshape.SetAsBox(4.0f, 0.05f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bdh;
      bdh.position.Set( 24.0f, 7.45f);
      b2Body* hground = m_world->CreateBody(&bdh);
      hground->CreateFixture(&horizshape, 0.0f);
    }

    //horizontal Dominos (first set)
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


// the ball beside Dominos(first set)
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



 // the left slant shelf shelf beside the shelf having first set of dominos
{
      b2PolygonShape horizshape;
      horizshape.SetAsBox(4.0f, 0.05f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bdh;
      bdh.position.Set( -6.3f, 22.67f);
      bdh.angle = -0.9f * b2_pi;
      b2Body* hground = m_world->CreateBody(&bdh);
      hground->CreateFixture(&horizshape, 0.0f);
    }

//the right slant shelf beside the shelf having first set of dominos
    {
      b2PolygonShape horizshape;
      horizshape.SetAsBox(4.0f, 0.05f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bdh;
      bdh.position.Set( 19.0f, 29.0f);
      bdh.angle = 0.8f * b2_pi;
      b2Body* hground = m_world->CreateBody(&bdh);
      hground->CreateFixture(&horizshape, 0.0f);
    }

//horizontal shelf containing second set of dominos
{
      b2PolygonShape horizshape;
      horizshape.SetAsBox(3.0f, 0.1f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bdh;
      bdh.position.Set( 38.5f, 1.5f);
      b2Body* hground = m_world->CreateBody(&bdh);
      hground->CreateFixture(&horizshape, 0.0f);
    }
//horizontal shelf containing third set of dominos
{
      b2PolygonShape horizshape;
      horizshape.SetAsBox(3.0f, 0.1f, b2Vec2(-10.f,10.f), 0.0f);
	
      b2BodyDef bdh;
      bdh.position.Set( 44.5f, 2.25f);
      b2Body* hground = m_world->CreateBody(&bdh);
      hground->CreateFixture(&horizshape, 0.0f);
    }

  //horizontal Dominos (second set)
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


//horizontal Dominos (third set)
    {
      b2PolygonShape shape;
      shape.SetAsBox(0.1f, 1.0f);
	
      b2FixtureDef fd;
      fd.shape = &shape;
      fd.density = 20.0f;
      fd.friction = 0.1f;
		
      for (int i = 0; i < 3; ++i)
    	{
    	  b2BodyDef bd;
    	  bd.type = b2_dynamicBody;
    	  bd.position.Set(32.0f + 1.0f * i, 13.5f);
    	  b2Body* body = m_world->CreateBody(&bd);
    	  body->CreateFixture(&fd);
    	}
    }

// the ball beside third set of dominos
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

//Alarms 	
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
	Ball *b= new Ball(m_world,38,1,42,1);
	
//bar below dominos to which the ball will collide and produce sound



//Right Side Slants
  b2EdgeShape shape;
  
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
  
  //right slant 2
  {
      b2Body* rightslant2;
      
      shape.Set(b2Vec2(-6.0f, 18.0f), b2Vec2(-25.0f,15.0f));
	
      b2BodyDef bd;
      rightslant2 = m_world->CreateBody(&bd);
      rightslant2->CreateFixture(&shape, 0.0f);
  }
  
  //right slant 3
 {
      b2Body* rightslant2;
    
      shape.Set(b2Vec2(-6.0f, 10.0f), b2Vec2(-25.0f, 7.0f));
	
      b2BodyDef bd;
      rightslant2 = m_world->CreateBody(&bd);
      rightslant2->CreateFixture(&shape, 0.0f);
  }
  
  //left slant 1
 
  {
      b2Body* leftslant1;
      
      shape.Set(b2Vec2(-45.0f, 28.0f), b2Vec2(-25.0f, 21.0f));
	
      b2BodyDef bd;
      leftslant1 = m_world->CreateBody(&bd);
      leftslant1->CreateFixture(&shape, 0.0f);
  }
  
  //left slant 2
  {
      b2Body* leftslant2;
      
      shape.Set(b2Vec2(-45.0f, 19.0f), b2Vec2(-25.0f, 13.0f));
	
      b2BodyDef bd;
      leftslant2 = m_world->CreateBody(&bd);
      leftslant2->CreateFixture(&shape, 0.0f);
  }
  

  //left slant 3
  {
      b2Body* leftslant3;
      
      shape.Set(b2Vec2(-45.0f, 10.0f), b2Vec2(-25.0f, 5.0f));
	
      b2BodyDef bd;
      leftslant3 = m_world->CreateBody(&bd);
      leftslant3->CreateFixture(&shape, 0.0f);
  }
  

  //shelf below slants
  {
      b2Body* shelf;
      
      shape.Set(b2Vec2(-23.0f, -5.0f), b2Vec2(10.0f, -2.0f));
	
      b2BodyDef bd;
      shelf = m_world->CreateBody(&bd);
      shelf->CreateFixture(&shape, 0.0f);
  }
  
     
     
     float shiftX=-12.0f;
     float shiftY=-10.0f;
  
  //The pulley system
    {
      b2BodyDef *bd = new b2BodyDef;
      bd->type = b2_dynamicBody;
      bd->position.Set(shiftX-16,shiftY-1);
      bd->fixedRotation = true;
      
      //The open box
      b2FixtureDef *fd1 = new b2FixtureDef;
      fd1->density = 10.0;
      fd1->friction = 0.5;
      fd1->restitution = 0.f;
      fd1->shape = new b2PolygonShape;
      b2PolygonShape bs1;
      bs1.SetAsBox(3.5,0.2, b2Vec2(0.f,-3.2f), 0);
      fd1->shape = &bs1;
      
      b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 10.0;
      fd2->friction = 0.5;
      fd2->restitution = 0.f;
      fd2->shape = new b2PolygonShape;
      b2PolygonShape bs2;
      bs2.SetAsBox(0.2,3.5, b2Vec2(3.2f,0.f), 0);
      fd2->shape = &bs2;
      
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

      //The bar attached to pulley
      bd->position.Set(shiftX+7,shiftY-1);	
      fd1->density = 37.0;	  //Can set this
      b2Body* box2 = m_world->CreateBody(bd);
      box2->CreateFixture(fd1);

      // The pulley joint
      b2PulleyJointDef* myjoint = new b2PulleyJointDef();
      b2Vec2 worldAnchorOnBody1(shiftX-16, shiftY-2); // Anchor point on body 1 in world axis
      b2Vec2 worldAnchorOnBody2(shiftX+7, shiftY-1); // Anchor point on body 2 in world axis
      b2Vec2 worldAnchorGround1(shiftX-16, shiftY-1); // Anchor point for ground 1 in world axis
      b2Vec2 worldAnchorGround2(shiftX+7, shiftY+4); // Anchor point for ground 2 in world axis
      float32 ratio = 1.0f; // Define ratio
      myjoint->Initialize(box1, box2, worldAnchorGround1, worldAnchorGround2, box1->GetWorldCenter(), box2->GetWorldCenter(), ratio);
      m_world->CreateJoint(myjoint);
    }

//Alarm system below

    //shelf on top

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

//shelf below that
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

	//no adding the second alarm thing here;
	//
	Ball * Alarm2 = new Ball(m_world,-2.5,-11.1,2.5,-11.1);
     
     float pi=3.14;
     float centrex=19.7f,centrey=3.0f,radius=4.5f;
     
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


// plate near the slant and below part blocking ball falling on dominos
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
 //The star left
    {
      b2PolygonShape shape;
      shape.SetAsBox(2.2f, 0.2f);
  
      b2BodyDef bd;
      bd.position.Set(-3.3f, 10.67f);
      bd.type = b2_dynamicBody;
      b2Body* body = m_world->CreateBody(&bd);
      b2FixtureDef *fd = new b2FixtureDef;
      fd->density = 1.f;
      fd->shape = new b2PolygonShape;
      fd->shape = &shape;
      body->CreateFixture(fd);


      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 2.0f);
       b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body->CreateFixture(fd2);


  
      b2BodyDef bd3;
      bd3.position.Set(-3.3f, 10.67f);
      b2Body* body3 = m_world->CreateBody(&bd3);
      //b2FixtureDef *fd3 = new b2FixtureDef;
  

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);
    }

//The star top
    {
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


      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 1.5f);
       b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body->CreateFixture(fd2);


  
      b2BodyDef bd3;
      bd3.position.Set(1.0f, 10.2f);
      b2Body* body3 = m_world->CreateBody(&bd3);
      //b2FixtureDef *fd3 = new b2FixtureDef;
  

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);


    }
    
    
    
    
    //The star right
    {
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


      b2PolygonShape shape2;
      shape2.SetAsBox(0.2f, 1.5f);
       b2FixtureDef *fd2 = new b2FixtureDef;
      fd2->density = 1.f;
      fd2->shape = new b2PolygonShape;
      fd2->shape = &shape2;
      body->CreateFixture(fd2);


  
      b2BodyDef bd3;
      bd3.position.Set(3.7f, 8.2f);
      b2Body* body3 = m_world->CreateBody(&bd3);
      //b2FixtureDef *fd3 = new b2FixtureDef;
  

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);


    }
    
    
    
    //The star below
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
      //b2FixtureDef *fd3 = new b2FixtureDef;
  

      b2RevoluteJointDef jointDef;
      jointDef.bodyA = body;
      jointDef.bodyB = body3;
      jointDef.localAnchorA.Set(0,0);
      jointDef.localAnchorB.Set(0,0);
      jointDef.collideConnected = false;
      m_world->CreateJoint(&jointDef);


    }
    
    
    
    
    //The star middle
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
     
	jointDef.enableMotor = true;
	jointDef.motorSpeed = 2*pi;
	jointDef.maxMotorTorque = 5;
      m_world->CreateJoint(&jointDef);


    }

  }

  sim_t *sim = new sim_t("Dominos", dominos_t::create);
}