//
// PerspectiveCamera.hpp for gle in /home/michar_l//glEngine
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Sat Feb 18 12:43:33 2012 loick michard
// Last update Thu May 24 14:21:28 2012 loick michard
//

#ifndef _PERSPECTIVE_CAMERA_HPP_
# define _PERSPECTIVE_CAMERA_HPP_

#include <Camera.hpp>

namespace gle {
  
  //! Class for perspective cameras.

  class PerspectiveCamera : public gle::Camera {
  public:

    //! Constructor with position.
    /*!
      \param position Camera position
      \param fovy Camera vertical Field of view in degrees
      \param aspect Camera aspect ratio
      \param near Distance to the near clipping plane
      \param far Distance to the far clipping plane
     */

    PerspectiveCamera(gle::Vector3<GLfloat> const& position,
		      GLfloat fovy=45.0, GLfloat aspect=1.0,
		      GLfloat near=3.0, GLfloat far=100.0);
    
    //! Constructor with position and target.
    /*!
      \param position Camera position
      \param target Camera target
      \param fovy Camera vertical Field of view in degrees
      \param aspect Camera aspect ratio
      \param near Distance to the near clipping plane
      \param far Distance to the far clipping plane
     */

    PerspectiveCamera(gle::Vector3<GLfloat> const& position,
		      gle::Vector3<GLfloat> const& target,
		      GLfloat fovy=45.0, GLfloat aspect=1.0,
		      GLfloat near=3.0, GLfloat far=100.0);

    //! Default destructor

    ~PerspectiveCamera(){}

    virtual void update();
  private:
    GLfloat _fovy;
    GLfloat _aspect;
    GLfloat _near;
    GLfloat _far;
  };
}

#endif // _PERSPECTIVE_CAMERA_HPP_