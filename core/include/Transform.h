#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/quaternion.hpp>

class Transform
{
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::quat rotation = glm::quat(glm::vec3(0.0, 0.0, 0.0));
    glm::vec3 scale   = glm::vec3(1.0f, 1.0f, 1.0f);

public:
    Transform(){}
    Transform(glm::vec3 position) { this->position = position; }

    //TODO: Something is wrong in the math for translate here...
    void translate(glm::vec2 vector) { position = glm::vec3(glm::translate(getModel(), glm::vec3(vector.x, vector.y, 0.0f))[3]);}
    void translate(glm::vec3 vector) { position = glm::vec3(glm::translate(getModel(), vector)[3]); }
    void translate(Transform other) { this->position = other.position; }
    void rotate(float angle, glm::vec3 axis) { this->rotation *= glm::angleAxis(glm::radians(angle), axis); }
    void scaleBy(glm::vec3 multiplier) { scale *= multiplier; }

    void scaleTo(glm::vec3 in_scale) { this->scale = in_scale; }

    glm::vec3 getForward() { return rotation * glm::vec3(0.0, 0.0, 1.0); }
    glm::vec3 getUp() { return rotation * glm::vec3(0.0, 1.0, 0.0); }
    glm::vec3 getRight() { return rotation * glm::vec3(1.0, 0.0, 0.0); }

    glm::vec3 getPosition() { return position; }
    glm::vec2 getPosition2() { return glm::vec2(position.x, position.y); }
    void setPosition(glm::vec3 position) { this->position = position; }
    void setPosition2(glm::vec2 position) { this->position = glm::vec3(position.x, position.y, this->position.z); }

    glm::vec3 getScale() { return scale; }

    glm::mat4 getModel() { 
        glm::mat4 model = glm::toMat4(rotation);
        model[3] = glm::vec4(position.x, position.y, position.z, 1);
//        model[0][0] = scale.x;
//        model[1][1] = scale.y;
//        model[2][2] = scale.z;
        model = glm::scale(model, scale);
        return model; 
    }

    Transform compose(Transform other)
    {
        Transform outTransform = Transform();
        outTransform.scale = this->scale * other.scale;
        outTransform.rotation = this->rotation * other.rotation;
        outTransform.position = this->position + other.position;
        return outTransform;
    }

    void lookAt(glm::vec3 target) { 
        // https://stackoverflow.com/questions/18172388/glm-quaternion-lookat-function
        // This needs work so it doesn't go parallel to the up vector
        glm::mat4 lookMat = glm::lookAt(position, target, glm::vec3(0.0f, 1.0f, 0.0f));
        rotation = glm::conjugate(glm::toQuat(lookMat));
    }
    // glm::mat4 setModel(glm::mat4 model) { rotation = glm::toQuat(model); position = glm::vec3(model[3]); }

    // Transform(glm::vec3 position) { translate(position); }

    // void translate(glm::vec3 vector) { model = glm::translate(model, vector); }
    // void translate(Transform other) { model = glm::translate(model, other.getPosition()); }
    // void rotate(float angle, glm::vec3 axis) { model = glm::rotate(model, glm::radians(angle), axis); };
    // void rotate(float yaw, float pitch, float roll) { model *= glm::yawPitchRoll(yaw, pitch, roll); };
    

    // glm::vec3 getPosition() { return glm::vec3(model[3]); }
    // void setPosition(glm::vec3 newPosition) { model[3][0] = newPosition.x;
    //                                           model[3][1] = newPosition.y;
    //                                           model[3][2] = newPosition.z; }
    // glm::vec3 getForward() { return glm::normalize(glm::vec3(model[2])); }
    // glm::vec3 getUp() { return glm::normalize(glm::vec3(model[1])); }
    // glm::vec3 getRight() { return glm::normalize(glm::vec3(model[0])); }

    // glm::mat4 getModel() { return model; };
    // void setModel(glm::mat4 model) { this->model = model; } 
};

#endif// TRANSFORM_H
