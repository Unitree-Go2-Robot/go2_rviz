#include "go2_rviz/Go2Services.hpp"

#include <QHBoxLayout>

namespace go2_rviz
{

Go2Services::Go2Services(rclcpp::Node::SharedPtr node, QWidget *parent)
: QWidget(parent), node_(node)
{
  body_height_client_ = node_->create_client<go2_interfaces::srv::BodyHeight>("/body_height");
  continuous_gait_client_ = node_->create_client<go2_interfaces::srv::ContinuousGait>("/continuous_gait");
  euler_client_ = node_->create_client<go2_interfaces::srv::Euler>("/euler");
  foot_raise_height_client_ = node_->create_client<go2_interfaces::srv::FootRaiseHeight>("/foot_raise_height");
  pose_client_ = node_->create_client<go2_interfaces::srv::Pose>("/pose");
  speed_level_client_ = node_->create_client<go2_interfaces::srv::SpeedLevel>("/speed_level");
  switch_gait_client_ = node_->create_client<go2_interfaces::srv::SwitchGait>("/switch_gait");
  switch_joystick_client_ = node_->create_client<go2_interfaces::srv::SwitchJoystick>("/switch_joystick");

  QVBoxLayout *layout = new QVBoxLayout(this);

  // Body Height Section
  QLabel *title_label = new QLabel("<h3 align='center'>Body Height</h3>");

  height_slider_ = new QSlider(Qt::Horizontal);
  height_slider_->setMinimum(-180);  // Representa -0.18
  height_slider_->setMaximum(30);    // Representa 0.03
  height_slider_->setValue(2);       // Valor inicial
  height_slider_->setTickInterval(10);
  height_slider_->setTickPosition(QSlider::TicksBelow);

  connect(height_slider_, &QSlider::valueChanged, this, &Go2Services::onHeightChanged);

  QGroupBox *body_height_group = new QGroupBox();
  QVBoxLayout *body_height_layout = new QVBoxLayout();
  body_height_layout->addWidget(title_label);
  body_height_layout->addWidget(height_slider_);
  body_height_group->setLayout(body_height_layout);

  layout->addWidget(body_height_group);

  // Continuous Gait Section
  QLabel *gait_label = new QLabel("<h3 align='center'>Continuous Gait</h3>");

  QPushButton* gait_true_button = new QPushButton("True");
  QPushButton* gait_false_button = new QPushButton("False");

  QHBoxLayout *gait_button_layout = new QHBoxLayout();
  gait_button_layout->addWidget(gait_true_button);
  gait_button_layout->addWidget(gait_false_button);

  connect(gait_true_button, &QPushButton::clicked, this, [this]() { onContinuousGaitClicked(true); });
  connect(gait_false_button, &QPushButton::clicked, this, [this]() { onContinuousGaitClicked(false); });

  QGroupBox *gait_group = new QGroupBox();
  QVBoxLayout *gait_layout = new QVBoxLayout();
  gait_layout->addWidget(gait_label);
  gait_layout->addLayout(gait_button_layout);
  gait_group->setLayout(gait_layout);

  layout->addWidget(gait_group);

  // Euler Section
  QLabel *euler_label = new QLabel("<h3 align='center'>Euler</h3>");

  roll_slider_ = new QSlider(Qt::Horizontal);
  roll_slider_->setMinimum(-750);
  roll_slider_->setMaximum(750);
  roll_slider_->setValue(0);
  roll_slider_->setTickInterval(100);
  roll_slider_->setTickPosition(QSlider::TicksBelow);

  pitch_slider_ = new QSlider(Qt::Horizontal);
  pitch_slider_->setMinimum(-750);
  pitch_slider_->setMaximum(750);
  pitch_slider_->setValue(0);
  pitch_slider_->setTickInterval(100);
  pitch_slider_->setTickPosition(QSlider::TicksBelow);

  yaw_slider_ = new QSlider(Qt::Horizontal);
  yaw_slider_->setMinimum(-750);
  yaw_slider_->setMaximum(750);
  yaw_slider_->setValue(0);
  yaw_slider_->setTickInterval(100);

  connect(roll_slider_, &QSlider::valueChanged, this, &Go2Services::onEulerChanged);
  connect(pitch_slider_, &QSlider::valueChanged, this, &Go2Services::onEulerChanged);
  connect(yaw_slider_, &QSlider::valueChanged, this, &Go2Services::onEulerChanged);

  QGroupBox *euler_group = new QGroupBox();
  QVBoxLayout *euler_layout = new QVBoxLayout();
  euler_layout->addWidget(euler_label);
  euler_layout->addWidget(roll_slider_);
  euler_layout->addWidget(pitch_slider_);
  euler_layout->addWidget(yaw_slider_);  
  euler_group->setLayout(euler_layout);

  layout->addWidget(euler_group);

  // Foot Raise Height Section
  QLabel *foot_raise_label = new QLabel("<h3 align='center'>Foot Raise Height</h3>");
  foot_raise_slider_ = new QSlider(Qt::Horizontal);
  foot_raise_slider_->setMinimum(-60);  // Representa -0.06
  foot_raise_slider_->setMaximum(30);   // Representa 0.03
  foot_raise_slider_->setValue(0);      // Valor inicial
  foot_raise_slider_->setTickInterval(10);
  foot_raise_slider_->setTickPosition(QSlider::TicksBelow);

  connect(foot_raise_slider_, &QSlider::valueChanged, this, &Go2Services::onFootRaiseHeightChanged);

  QGroupBox *foot_raise_group = new QGroupBox();
  QVBoxLayout *foot_raise_layout = new QVBoxLayout();
  foot_raise_layout->addWidget(foot_raise_label);
  foot_raise_layout->addWidget(foot_raise_slider_);
  foot_raise_group->setLayout(foot_raise_layout);

  layout->addWidget(foot_raise_group);

  // Pose Section
  QLabel *pose_label = new QLabel("<h3 align='center'>Pose</h3>");

  QPushButton *pose_true_button = new QPushButton("True");
  QPushButton *pose_false_button = new QPushButton("False");

  QHBoxLayout *pose_button_layout = new QHBoxLayout();
  pose_button_layout->addWidget(pose_true_button);
  pose_button_layout->addWidget(pose_false_button);

  connect(pose_true_button, &QPushButton::clicked, this, [this]() { onPoseClicked(true); }); 
  connect(pose_false_button, &QPushButton::clicked, this, [this]() { onPoseClicked(false); });

  QGroupBox *pose_group = new QGroupBox();
  QVBoxLayout *pose_layout = new QVBoxLayout();
  pose_layout->addWidget(pose_label);
  pose_layout->addLayout(pose_button_layout);
  pose_group->setLayout(pose_layout);

  layout->addWidget(pose_group);

  // Speed Level Section
  QLabel *speed_label = new QLabel("<h3 align='center'>Speed Level</h3>");

  speed_lvl_slider_ = new QSlider(Qt::Horizontal);
  speed_lvl_slider_->setMinimum(-1);
  speed_lvl_slider_->setMaximum(1);
  speed_lvl_slider_->setValue(0);
  speed_lvl_slider_->setTickInterval(1);
  speed_lvl_slider_->setTickPosition(QSlider::TicksBelow);

  connect(speed_lvl_slider_, &QSlider::valueChanged, this, &Go2Services::onSpeedLevelChanged);

  QGroupBox *speed_group = new QGroupBox();
  QVBoxLayout *speed_layout = new QVBoxLayout();
  speed_layout->addWidget(speed_label);
  speed_layout->addWidget(speed_lvl_slider_);
  speed_group->setLayout(speed_layout);

  layout->addWidget(speed_group);

  // Switch Gait Section
  QLabel *switch_gait_label = new QLabel("<h3 align='center'>Switch Gait</h3>");

  QPushButton *gait_idle_button = new QPushButton("Idle");
  QPushButton *gait_trot_button = new QPushButton("Trot");
  QPushButton *gait_trot_run_button = new QPushButton("Trot Run");
  QPushButton *gait_forward_climb_button = new QPushButton("Forward Climb");
  QPushButton *gait_reverse_climb_button = new QPushButton("Reverse Climb");

  connect(gait_idle_button, &QPushButton::clicked, this, [this]() { onSwitchGaitClicked(0); });
  connect(gait_trot_button, &QPushButton::clicked, this, [this]() { onSwitchGaitClicked(1); });
  connect(gait_trot_run_button, &QPushButton::clicked, this, [this]() { onSwitchGaitClicked(2); });
  connect(gait_forward_climb_button, &QPushButton::clicked, this, [this]() { onSwitchGaitClicked(3); });
  connect(gait_reverse_climb_button, &QPushButton::clicked, this, [this]() { onSwitchGaitClicked(4); });

  QHBoxLayout *gait_button_layout_01 = new QHBoxLayout();
  gait_button_layout_01->addWidget(gait_trot_button);
  gait_button_layout_01->addWidget(gait_trot_run_button);

  QHBoxLayout *gait_button_layout_02 = new QHBoxLayout();
  gait_button_layout_02->addWidget(gait_forward_climb_button);
  gait_button_layout_02->addWidget(gait_reverse_climb_button);

  QGroupBox *switch_gait_group = new QGroupBox();
  QVBoxLayout *switch_gait_layout = new QVBoxLayout();
  switch_gait_layout->addWidget(switch_gait_label);
  switch_gait_layout->addWidget(gait_idle_button);
  switch_gait_layout->addLayout(gait_button_layout_01);
  switch_gait_layout->addLayout(gait_button_layout_02);
  switch_gait_group->setLayout(switch_gait_layout);

  layout->addWidget(switch_gait_group);

  // Switch Joystick Section
  QLabel *switch_joystick_label = new QLabel("<h3 align='center'>Switch Joystick</h3>");

  QPushButton *joystick_true_button = new QPushButton("True");
  QPushButton *joystick_false_button = new QPushButton("False");

  connect(joystick_true_button, &QPushButton::clicked, this, [this]() { onSwitchJoystickClicked(true); });
  connect(joystick_false_button, &QPushButton::clicked, this, [this]() { onSwitchJoystickClicked(false); });

  QHBoxLayout *joystick_button_layout = new QHBoxLayout();
  joystick_button_layout->addWidget(joystick_true_button);
  joystick_button_layout->addWidget(joystick_false_button);

  QGroupBox *switch_joystick_group = new QGroupBox();
  QVBoxLayout *switch_joystick_layout = new QVBoxLayout();
  switch_joystick_layout->addWidget(switch_joystick_label);
  switch_joystick_layout->addLayout(joystick_button_layout);
  switch_joystick_group->setLayout(switch_joystick_layout);

  layout->addWidget(switch_joystick_group);

  setLayout(layout);
}

Go2Services::~Go2Services()
{
}

void Go2Services::onHeightChanged(int value)
{
  float height = static_cast<float>(value) / 1000.0f;  // Convertimos a metros
  
  auto request = std::make_shared<go2_interfaces::srv::BodyHeight::Request>();
  request->height = height;

  body_height_client_->async_send_request(request);
}

void Go2Services::onContinuousGaitClicked(bool flag)
{
  auto request = std::make_shared<go2_interfaces::srv::ContinuousGait::Request>();
  request->flag = flag;

  continuous_gait_client_->async_send_request(request);
}

void Go2Services::onEulerChanged()
{
  float roll = static_cast<float>(roll_slider_->value()) / 100.0f;
  float pitch = static_cast<float>(pitch_slider_->value()) / 100.0f;
  float yaw = static_cast<float>(yaw_slider_->value()) / 100.0f;

  auto request = std::make_shared<go2_interfaces::srv::Euler::Request>();
  request->roll = roll;
  request->pitch = pitch;
  request->yaw = yaw;

  euler_client_->async_send_request(request);
}

void Go2Services::onFootRaiseHeightChanged(int value)
{
  float height = static_cast<float>(value) / 1000.0f;  // Convertimos a metros
  
  auto request = std::make_shared<go2_interfaces::srv::FootRaiseHeight::Request>();
  request->height = height;

  foot_raise_height_client_->async_send_request(request);
}

void Go2Services::onPoseClicked(bool flag)
{
  auto request = std::make_shared<go2_interfaces::srv::Pose::Request>();
  request->flag = flag;

  pose_client_->async_send_request(request);
}

void Go2Services::onSpeedLevelChanged(int level)
{
  auto request = std::make_shared<go2_interfaces::srv::SpeedLevel::Request>();
  request->level = level;

  speed_level_client_->async_send_request(request);
}

void Go2Services::onSwitchGaitClicked(int gait)
{
  auto request = std::make_shared<go2_interfaces::srv::SwitchGait::Request>();
  request->d = gait;

  switch_gait_client_->async_send_request(request);
}

void Go2Services::onSwitchJoystickClicked(bool flag)
{
  auto request = std::make_shared<go2_interfaces::srv::SwitchJoystick::Request>();
  request->flag = flag;

  switch_joystick_client_->async_send_request(request);
}

}  // namespace go2_rviz
