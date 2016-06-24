#include "Camera.h"

// Constructor
Camera::Camera(GLfloat distance, glm::vec3 aim, glm::vec3 up) : m_zoom(ZOOM)
{
#ifdef DEBUG
    qWarning() << "Camera::Camera(glm::vec3 aim, glm::vec3 position, glm::vec3 up) : Zoom(ZOOM)";
#endif
    m_lightColor = glm::vec3(1.0f, 1.0f, 1.0f);
    m_theta = THETA;
    m_phi = PHI;
    m_distance = distance;
    m_aim = aim;
    m_worldup = up;
    updateCameraVectors();
}

void Camera::rotateCam(float phi, float theta)
{
#ifdef DEBUG
    qWarning() << "Camera::rotateCam(float phi, float theta)";
#endif

    m_theta += theta;
    m_phi += phi;

    if(m_theta > 360.0 || m_theta < 360 )
    {
        m_theta = (int) m_theta % 360 + (m_theta - (m_theta / 1));
        if(m_theta > 269.0f)
        {
            m_theta = 269.0f;
        }
        if(m_theta < 91.0f)
        {
            m_theta = 91.0f;
        }
    }
    if(m_phi > 360.0 || m_phi < 360 )
    {
       m_phi = (int) m_phi % 360 + (m_phi - (m_phi / 1));
    }

    updateCameraVectors();
}

void Camera::setZoom(GLfloat zoom)
{
    if(zoom < 0.0f || zoom > 180.0f)
    {
        return;
    }
    m_zoom = zoom;
    updateCameraVectors();
}

GLfloat Camera::getDistance()
{
    return m_distance;
}

void Camera::setDistance(GLfloat distance)
{
    m_distance = distance;
    updateCameraVectors();
}

GLfloat Camera::getZoom()
{
    return m_zoom;
}

// Calculates vectors for lookAt() function
void Camera::updateCameraVectors()
{
#ifdef DEBUG
    qWarning() << "void Camera::updateCameraVectors()";
#endif
    glm::vec3 pos;

    pos.x = m_distance * cos(glm::radians(m_theta)) * cos(glm::radians(m_phi));
    pos.y = m_distance * sin(glm::radians(-m_theta));
    pos.z = m_distance * cos(glm::radians(m_theta)) * sin(glm::radians(m_phi));

    m_position = pos;
    glm::vec3 front;
    front = m_aim - m_position;
    m_front = glm::normalize(front);

    m_right = glm::normalize(glm::cross(m_front, m_worldup));  // Normalize vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    m_up = glm::normalize(glm::cross(m_right, m_front));
#ifdef DEBUG
    qWarning() << "m_theta: " << m_theta;
    qWarning() << "m_phi: " << m_phi;
    qWarning() << "Position: "; qWarning()  << (glm::to_string(this->m_position)).c_str();
    qWarning() << "Front: "; qWarning()  << (glm::to_string(this->m_front)).c_str();
    qWarning() << "Right: "; qWarning()  << (glm::to_string(this->m_right)).c_str();
    qWarning() << "Up: " ;   qWarning()  << (glm::to_string(this->m_up)).c_str();
    qWarning() << "Aim: " ;  qWarning()  << (glm::to_string(this->m_aim)).c_str();
#endif
}

// Returns the view matrix calculated using Eular Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
#ifdef DEBUG
    qWarning() << "glm::mat4 Camera::GetViewMatrix()";
#endif
    return glm::lookAt(m_position, m_position + m_front, m_up);
}
