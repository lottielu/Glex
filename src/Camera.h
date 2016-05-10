#ifndef SRC_CAMERA_H_
#define SRC_CAMERA_H_

#include <glm/ext.hpp>
#include "common.h" /*!< include the common.h file.*/

/**
 * A reasonable attempt at implementing a camera interface.
 * Purpose is to change camera position using uniform variables and
 * acceptance of keyboard input.
 * An attempt based on the tutorial www.opengl-tutorial.org/beginners-tutorials/tutorial-6-keyboard-and-mouse/
 */
class Camera {

public:

Camera();
glm::mat4 UpdateCameraPosition(Input input_Direction, int mouseX, int mouseY);

private:

glm::vec3 cameraPosition;
glm::vec3 direction;
glm::vec3 right;
glm::vec3 up;

float horizontalAngle;
float verticalAngle;

float mouseDeltaX;
float mouseDeltaY;

float cameraMovementSpeed;




};
#endif //CAMERA_H
