#ifndef GO2_RVIZ_GO2SERVICES_HPP_
#define GO2_RVIZ_GO2SERVICES_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QScrollArea>
#include <QGroupBox>
#include <rclcpp/rclcpp.hpp>
#include <go2_interfaces/srv/body_height.hpp>
#include <go2_interfaces/srv/continuous_gait.hpp>
#include <go2_interfaces/srv/euler.hpp>
#include <go2_interfaces/srv/foot_raise_height.hpp>
#include <go2_interfaces/srv/pose.hpp>
#include <go2_interfaces/srv/speed_level.hpp>
#include <go2_interfaces/srv/switch_gait.hpp>
#include <go2_interfaces/srv/switch_joystick.hpp>

namespace go2_rviz
{

class Go2Services : public QWidget
{
  Q_OBJECT

public:
  explicit Go2Services(rclcpp::Node::SharedPtr node, QWidget * parent = nullptr);
  ~Go2Services();

private slots:
  void onHeightChanged(int value);
  void onContinuousGaitClicked(bool flag);
  void onEulerChanged();
  void onFootRaiseHeightChanged(int value);
  void onPoseClicked(bool flag);
  void onSpeedLevelChanged(int level);
  void onSwitchGaitClicked(int gait);
  void onSwitchJoystickClicked(bool flag);

private:
  rclcpp::Node::SharedPtr node_;

  // Service clients
  rclcpp::Client<go2_interfaces::srv::BodyHeight>::SharedPtr body_height_client_;
  rclcpp::Client<go2_interfaces::srv::ContinuousGait>::SharedPtr continuous_gait_client_;
  rclcpp::Client<go2_interfaces::srv::Euler>::SharedPtr euler_client_;
  rclcpp::Client<go2_interfaces::srv::FootRaiseHeight>::SharedPtr foot_raise_height_client_;
  rclcpp::Client<go2_interfaces::srv::Pose>::SharedPtr pose_client_;
  rclcpp::Client<go2_interfaces::srv::SpeedLevel>::SharedPtr speed_level_client_;
  rclcpp::Client<go2_interfaces::srv::SwitchGait>::SharedPtr switch_gait_client_;
  rclcpp::Client<go2_interfaces::srv::SwitchJoystick>::SharedPtr switch_joystick_client_;

  // UI Elements
  QSlider * height_slider_;
  QLabel * body_height_current_value_label_;

  QPushButton * gait_true_button_;
  QPushButton * gait_false_button_;

  QSlider * roll_slider_;
  QSlider * pitch_slider_;
  QSlider * yaw_slider_;
  QLabel * roll_value_label_;
  QLabel * pitch_value_label_;
  QLabel * yaw_value_label_;

  QSlider * foot_raise_slider_;
  QLabel* foot_raise_current_value_label_;

  QPushButton * pose_true_button_;
  QPushButton * pose_false_button_;

  QSlider * speed_lvl_slider_;
  QLabel * speed_current_value_label_;

  QPushButton * gait_trot_button_;
  QPushButton * gait_trot_run_button_;
  QPushButton * gait_forward_climb_button_;
  QPushButton * gait_reverse_climb_button_;

  QPushButton * joystick_true_button_;
  QPushButton * joystick_false_button_;
};

}  // namespace go2_rviz

#endif  // GO2_RVIZ_GO2SERVICES_HPP_
