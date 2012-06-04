//
// Example.hpp for  in /home/jochau_g//dev/gl-engine-42
// 
// Made by gael jochaud-du-plessix
// Login   <jochau_g@epitech.net>
// 
// Started on  Fri May 25 12:25:22 2012 gael jochaud-du-plessix
// Last update Thu May 31 19:50:35 2012 gael jochaud-du-plessix
//

#ifndef _EXAMPLE_HPP_
# define _EXAMPLE_HPP_

# include <string>
# include <vector>
# include <SFML/Window.hpp>

# include <Scene.hpp>
# include <PerspectiveCamera.hpp>
# include <Geometries.hpp>
# include <Material.hpp>
# include <Renderer.hpp>
# include <PointLight.hpp>
# include <Exception.hpp>

class Example {
public:
  enum CameraType {
    Flycam,
    Trackball,
    NoCamera
  };

  Example(int argc, char** argv, int winWidth=1280, int winHeight=720, int framerate=60, std::string const & name="glEngine");
  virtual ~Example();
  
  int		run();
  virtual void	initScene() = 0;
  virtual void	animate();
  virtual void	render();

  void printGPUMemInfo();

protected:
  std::vector<std::string>	_argv;

  int		_winWidth;
  int		_winHeight;
  int		_framerate;
  std::string	_name;

  sf::Window*	_window;
  sf::Clock	_time;

  bool		_showFramerate;
  bool		_limitFramerate;
  CameraType	_cameraType;

  bool		_recordVideo;

  gle::Scene*		_scene;
  gle::Camera*		_camera;
  gle::Renderer*	_renderer;
  
  GLint			_lastGPUMemUsed;
};

#endif