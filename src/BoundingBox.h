 #ifndef BoundingBox_H
#define BoundingBox_H


class BoundingBox
{

private:
std::shared_ptr<glm::

public:

BoundingBox(			glm::vec3 x_y_z_pos,
		glm::vec3 translate,
        glm::vec3 animate,
        glm::vec3 rotate,
        glm::vec3 scale););
virtual ~ BoundingBox();

void translate(glm::vec3);


};


#endif
