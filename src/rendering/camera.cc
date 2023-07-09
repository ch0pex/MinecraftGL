#include "camera.h"
#include "../game_engine.h"


Camera::Camera(f32 fov, f32 width, f32 height, f32 near_plane, f32 far_plane, glm::vec3 position) {
    fov_ = fov;
    width = width;
    height = height;
    near_plane_ = near_plane;
    far_plane_ = far_plane;
    position_ = position;
    movement_speed_ = 0.5f;
    camera_front_ = glm::vec3(0.0f, 0.0f, -1.0f);
    camera_up_ = glm::vec3(0.0f, 1.0f, 0.0f);
    camera_right_ = glm::normalize(glm::cross(camera_up_, camera_front_));
    first_mouse_ = true;
    yaw_ = 0;
    pitch_ = 0;
    movement_dir_ = Camera::kStatic;
    projection_matrix_ = glm::perspective(fov_, width / height, near_plane_, far_plane_);
    CalculateViewProj();
}

Camera::~Camera() {

}

void Camera::CalculateViewProj() {
    view_matrix_ = glm::lookAt(position_, position_ + camera_front_, camera_up_);
    view_matrix_ += glm::translate(view_matrix_, -position_);
    view_proj_matrix_ = projection_matrix_ * view_matrix_;
}

glm::mat4 Camera::GetView() {
    return view_matrix_;
}

glm::mat4 Camera::GetProjection() {
    return projection_matrix_;
}

glm::vec3 Camera::GetPosition() {
    return position_;
}

void Camera::SetPosition(glm::vec3 position) {
    position = position;
}

float *Camera::GetViewProjValuePtr() {
    return glm::value_ptr(view_proj_matrix_);
}

void Camera::Update() {
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    switch (movement_dir_) {
        case Camera::kFront:
            position_ += movement_speed_ * camera_front_;
            break;
        case Camera::kBack:
            position_ -= movement_speed_ * camera_front_;
            break;
        case Camera::kRight:
            position_ += glm::normalize(glm::cross(camera_front_, camera_up_)) * movement_speed_;
            break;
        case Camera::kLeft:
            position_ -= glm::normalize(glm::cross(camera_front_, camera_up_)) * movement_speed_;
            break;
        case Camera::kUp:
            position_ += movement_speed_ * camera_up_;
            break;
        case Camera::kDown:
            position_ -= movement_speed_ * camera_up_;
            break;
        default:
            break;
    }
    CalculateViewProj();
    frustum_.Update(view_proj_matrix_);
    //std::cout << position_.x << ", " << position_.y << ", " << position_.z << "\n";
}


void Camera::Move(Direction direction) {
    movement_dir_ = direction;
}


void Camera::MousePosToFront(double xpos, double ypos) {

    if (first_mouse_) {

        last_x_ = xpos;
        last_y_ = ypos;
        first_mouse_ = false;
    }

    double xoffset = xpos - last_x_;
    double yoffset = last_y_ - ypos;
    last_x_ = xpos;
    last_y_ = ypos;

    double sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw_ += xoffset;
    pitch_ += yoffset;

    if (pitch_ > 89.0f)
        pitch_ = 89.0f;
    if (pitch_ < -89.0f)
        pitch_ = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    direction.y = sin(glm::radians(pitch_));
    direction.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));


    camera_front_ = glm::normalize(direction);
    //camera_right_ = glm::normalize(glm::cross(camera_front_, camera_up_));
    //camera_up_ = glm::normalize(glm::cross(camera_right_, camera_front_));
    CalculateViewProj();
    frustum_.Update(view_proj_matrix_);
}

bool Camera::InFrustum(Chunklet &chunklet) {
    glm::vec3 chunklet_center = chunklet.GetPosition() + glm::vec3(8.f, 8.f, 8.f);
    return frustum_.IsPointInside(chunklet_center) || glm::distance(chunklet_center, position_) < 64.f;
}
