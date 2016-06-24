#ifndef CAMERA_H
#define CAMERA_H
#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <QOpenGLWidget>
#include <QDebug>
#include <vector>

// global constants for camera class
const GLfloat ZOOM = 45.0f;
const GLfloat PHI = -70;
const GLfloat THETA = 200;

// An abstract camera class
class Camera
{
    friend class Scene;
public:
    // camera position
    glm::vec3 m_position;
    glm::vec3 m_lightColor;
    // Constructor with vectors
    Camera(GLfloat distance = 29.0f, glm::vec3 aim = glm::vec3(0.0f, 0.0f, 0.0f),glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f));

    // Returns the view matrix calculated using Eular Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();

    // Rotate camera by phi and theta angles
    void rotateCam(float phi, float theta);
    void setZoom(GLfloat zoom);
    GLfloat getDistance();
    void setDistance(GLfloat distance);
    GLfloat getZoom();
private:
    // Camera zoom
    GLfloat m_zoom;
    // Camera Attributes
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_worldup;
    glm::vec3 m_aim;
    GLfloat m_phi;
    GLfloat m_theta;
    GLfloat m_distance;
    // Calculates the position vector from the Camera's (updated) Eular Angles
    void updateCameraVectors();
};
#endif
