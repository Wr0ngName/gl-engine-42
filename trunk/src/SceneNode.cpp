//
// SceneNode.cpp for glengine in /home/michar_l//gl-engine-42/src
// 
// Made by loick michard
// Login   <michar_l@epitech.net>
// 
// Started on  Tue May 15 19:32:41 2012 loick michard
// Last update Thu May 24 17:13:54 2012 loick michard
//

#include <Scene.hpp>

gle::Scene::Node::Node(gle::Scene::Node::Type type) :
  _type(type), _parent(NULL), _hasTarget(false)
{

}

gle::Scene::Node::Node(const gle::Scene::Node& other) :
  _type(other._type), _name(other._name), 
  _children(), _parent(NULL), _position(other._position),
  _target(other._target), _hasTarget(other._hasTarget),
  _scaleMatrix(other._scaleMatrix), _rotationMatrix(other._rotationMatrix)
{
  for (gle::Scene::Node* const &child : other._children)
    {
      Node* newChild = child->duplicate();
      _children.push_back(newChild);
      newChild->setParent(this);
    }
}

gle::Scene::Node::~Node()
{

}

gle::Scene::Node::Type gle::Scene::Node::getType() const
{
  return (_type);
}

const std::string& gle::Scene::Node::getName() const
{
  return (_name);
}

void gle::Scene::Node::setName(const std::string& name)
{
  _name = name;
}

void gle::Scene::Node::addChild(gle::Scene::Node* child)
{
  //std::cout << _name << " -> " << child->_name << std::endl;
  _children.push_back(child);
  child->setParent(this);
  child->updateMatrix();
}

void gle::Scene::Node::removeChild(gle::Scene::Node* child)
{
  for (auto _child = _children.begin(); _child != _children.end(); ++_child)
    if (*_child == child)
      {
	_children.erase(_child);
	return;
      }
  for (gle::Scene::Node* &_child : _children)
    _child->removeChild(child);
}

const std::vector<gle::Scene::Node*>& gle::Scene::Node::getChildren() const
{
  return (_children);
}

gle::Scene::Node* gle::Scene::Node::getChildByName(std::string const& name)
{
  if (_name == name)
    return (this);
  for (gle::Scene::Node* &child : _children)
    if (child->_name == name)
      return (child);
  for (gle::Scene::Node* &child : _children)
    child->getChildByName(name);
}

void gle::Scene::Node::setParent(gle::Scene::Node* parent)
{
  _parent = parent;
}

void gle::Scene::Node::updateMatrix()
{
  if (_parent)
    _transformationMatrix = _parent->_transformationMatrix;
  else
    _transformationMatrix.identity();
  _transformationMatrix.translate(_position);
  _transformationMatrix *= _rotationMatrix;
  _transformationMatrix *= _scaleMatrix;
  _absolutePosition = _position;
  _absolutePosition *= _transformationMatrix;
  _absolutePosition.x -= _position.x;
  _absolutePosition.y -= _position.y;
  _absolutePosition.z -= _position.z;
  if (_hasTarget)
    {
      _transformationMatrix.translate(-_position.x, -_position.y, -_position.z);
      _transformationMatrix *= gle::Matrix4<GLfloat>::lookAt(_position,
							     _target,
							     Vector3<GLfloat>(0, 1, 0));
      _transformationMatrix.translate(-_position.x, -_position.y, -_position.z);
    }
  Matrix4<GLfloat> inverse(_transformationMatrix);
  inverse.inverse();
  _normalMatrix = inverse;
  _normalMatrix.transpose();

  for (gle::Scene::Node* &child : _children)
    child->updateMatrix();
  this->update();
}

void gle::Scene::Node::setMatrices(gle::Matrix4<GLfloat> &transformationMatrix,
				   gle::Matrix3<GLfloat> &normalMatrix)
{
  _transformationMatrix = transformationMatrix;
  _normalMatrix = normalMatrix;
}

const gle::Matrix4<GLfloat>& gle::Scene::Node::getTransformationMatrix()
{
  return (_transformationMatrix);
}

const gle::Matrix3<GLfloat>& gle::Scene::Node::getNormalMatrix()
{
  return (_normalMatrix);
}

void gle::Scene::Node::setPosition(const gle::Vector3<GLfloat>& pos)
{
  _position = pos;
  this->updateMatrix();
}

void gle::Scene::Node::setRotation(const gle::Quaternion<GLfloat>& rotation)
{
  _rotationMatrix = rotation.getMatrix();
  this->updateMatrix();
}

void gle::Scene::Node::setTarget(const gle::Vector3<GLfloat>& target)
{
  _target = target;
  _hasTarget = true;
  this->updateMatrix();
}

void gle::Scene::Node::setScale(GLfloat scale)
{
  this->setScale(scale, scale, scale);
  this->updateMatrix();
}

void gle::Scene::Node::setScale(GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ)
{
  _scaleMatrix = gle::Matrix4<GLfloat>::scale(scaleX, scaleY, scaleZ);
  this->updateMatrix();
}

const gle::Vector3<GLfloat>& gle::Scene::Node::getAbsolutePosition() const
{
  return (_absolutePosition);
}

const gle::Vector3<GLfloat>& gle::Scene::Node::getTarget() const
{
  return (_target);
}

void gle::Scene::Node::translate(const gle::Vector3<GLfloat>& vec)
{
  _position += vec;
  _target += vec;
  this->updateMatrix();
}

void gle::Scene::Node::rotate(const gle::Quaternion<GLfloat>& rotation)
{
  _rotationMatrix *= rotation.getMatrix();
  this->updateMatrix();
}

gle::Scene::Node* gle::Scene::Node::duplicate() const
{
  return (new Node(*this));
}

void gle::Scene::Node::update()
{

}
