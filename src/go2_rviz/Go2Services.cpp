#include "go2_rviz/Go2Services.hpp"

#include <QHBoxLayout>

namespace go2_rviz
{

Go2Services::Go2Services(rclcpp::Node::SharedPtr node, QWidget * parent)
: QWidget(parent), node_(node)
{
  body_height_client_ = node_->create_client<go2_interfaces::srv::BodyHeight>("/body_height");
  continuous_gait_client_ = node_->create_client<go2_interfaces::srv::ContinuousGait>(
    "/continuous_gait");
  euler_client_ = node_->create_client<go2_interfaces::srv::Euler>("/euler");
  foot_raise_height_client_ = node_->create_client<go2_interfaces::srv::FootRaiseHeight>(
    "/foot_raise_height");
  pose_client_ = node_->create_client<go2_interfaces::srv::Pose>("/pose");
  speed_level_client_ = node_->create_client<go2_interfaces::srv::SpeedLevel>("/speed_level");
  switch_gait_client_ = node_->create_client<go2_interfaces::srv::SwitchGait>("/switch_gait");
  switch_joystick_client_ = node_->create_client<go2_interfaces::srv::SwitchJoystick>(
    "/switch_joystick");

  QVBoxLayout * layout = new QVBoxLayout(this);
  QWidget * container = new QWidget();
  QScrollArea * scroll_area = new QScrollArea(this);
  scroll_area->setWidgetResizable(true);

  // Body Height Section
  QLabel * title_label = new QLabel("<h3 align='center'>Body Height</h3>");
  title_label->setStyleSheet("font-size: 10px;");

  height_slider_ = new QSlider(Qt::Horizontal);
  height_slider_->setRange(-180, 30);  // Representa -0.18 a 0.03
  height_slider_->setValue(0.02);        // Valor inicial
  height_slider_->setTickInterval(10);
  height_slider_->setTickPosition(QSlider::TicksBelow);

  QLabel * min_body_height_label = new QLabel("-0.18");
  QLabel * max_body_height_label = new QLabel("0.03");
  body_height_current_value_label_ = new QLabel(QString::number(0.02));

  QHBoxLayout * body_height_slider_layout = new QHBoxLayout();
  body_height_slider_layout->addWidget(min_body_height_label);
  body_height_slider_layout->addWidget(height_slider_);
  body_height_slider_layout->addWidget(max_body_height_label);

  QHBoxLayout * body_height_current_value_layout = new QHBoxLayout();
  body_height_current_value_layout->addStretch();
  body_height_current_value_layout->addWidget(body_height_current_value_label_);
  body_height_current_value_layout->addStretch();

  connect(height_slider_, &QSlider::valueChanged, this, &Go2Services::onHeightChanged);

  QVBoxLayout * body_height_layout = new QVBoxLayout();
  body_height_layout->setSpacing(1);
  body_height_layout->addWidget(title_label);
  body_height_layout->addLayout(body_height_current_value_layout);
  body_height_layout->addLayout(body_height_slider_layout);

  QGroupBox * body_height_group = new QGroupBox();
  body_height_group->setLayout(body_height_layout);
  body_height_group->setStyleSheet("margin: 5px; padding: 5px;");

  layout->addWidget(body_height_group);

  // Continuous Gait Section
  QLabel * gait_label = new QLabel("<h3 align='center'>Continuous Gait</h3>");
  gait_label->setStyleSheet("font-size: 10px;");

  gait_true_button_ = new QPushButton("True");
  gait_false_button_ = new QPushButton("False");
  gait_false_button_->setStyleSheet("background-color: green;");

  connect(
    gait_true_button_, &QPushButton::clicked, this,
    [this]() {onContinuousGaitClicked(true);});
  connect(
    gait_false_button_, &QPushButton::clicked, this,
    [this]() {onContinuousGaitClicked(false);});

  QHBoxLayout * gait_button_layout = new QHBoxLayout();
  gait_button_layout->addWidget(gait_true_button_);
  gait_button_layout->addWidget(gait_false_button_);

  QVBoxLayout * gait_layout = new QVBoxLayout();
  gait_layout->setSpacing(1);
  gait_layout->setContentsMargins(1, 1, 1, 1);
  gait_layout->addWidget(gait_label);
  gait_layout->addLayout(gait_button_layout);

  QGroupBox * gait_group = new QGroupBox();
  gait_group->setLayout(gait_layout);

  layout->addWidget(gait_group);

  // Euler Section
  QLabel * euler_label = new QLabel("<h3 align='center'>Euler</h3>");
  euler_label->setStyleSheet("font-size: 10px;");

  roll_slider_ = new QSlider(Qt::Horizontal);
  roll_slider_->setRange(-750, 750);
  roll_slider_->setValue(0);
  roll_slider_->setTickInterval(100);
  roll_slider_->setTickPosition(QSlider::TicksBelow);

  pitch_slider_ = new QSlider(Qt::Horizontal);
  pitch_slider_->setRange(-750, 750);
  pitch_slider_->setValue(0);
  pitch_slider_->setTickInterval(100);
  pitch_slider_->setTickPosition(QSlider::TicksBelow);

  yaw_slider_ = new QSlider(Qt::Horizontal);
  yaw_slider_->setRange(-600, 600);
  yaw_slider_->setValue(0);
  yaw_slider_->setTickInterval(100);
  yaw_slider_->setTickPosition(QSlider::TicksBelow);

  QLabel * min_euler_roll_lavel = new QLabel("-7.50");
  QLabel * max_euler_roll_label = new QLabel("7.50");
  QLabel * min_euler_pitch_label = new QLabel("-7.50");
  QLabel * max_euler_pitch_label = new QLabel("7.50");
  QLabel * min_euler_yaw_label = new QLabel("-6.00");
  QLabel * max_euler_yaw_label = new QLabel("6.00");

  QHBoxLayout * roll_slider_layout = new QHBoxLayout();
  roll_slider_layout->addWidget(min_euler_roll_lavel);
  roll_slider_layout->addWidget(roll_slider_);
  roll_slider_layout->addWidget(max_euler_roll_label);

  QHBoxLayout * pitch_slider_layout = new QHBoxLayout();
  pitch_slider_layout->addWidget(min_euler_pitch_label);
  pitch_slider_layout->addWidget(pitch_slider_);
  pitch_slider_layout->addWidget(max_euler_pitch_label);

  QHBoxLayout * yaw_slider_layout = new QHBoxLayout();
  yaw_slider_layout->addWidget(min_euler_yaw_label);
  yaw_slider_layout->addWidget(yaw_slider_);
  yaw_slider_layout->addWidget(max_euler_yaw_label);

  roll_value_label_ = new QLabel("Roll: " + QString::number(roll_slider_->value()));
  pitch_value_label_ = new QLabel("Pitch: " + QString::number(pitch_slider_->value()));
  yaw_value_label_ = new QLabel("Yaw: " + QString::number(yaw_slider_->value()));

  QHBoxLayout * euler_current_value_layout = new QHBoxLayout();
  euler_current_value_layout->addStretch();
  euler_current_value_layout->addWidget(roll_value_label_);
  euler_current_value_layout->addStretch();
  euler_current_value_layout->addWidget(pitch_value_label_);
  euler_current_value_layout->addStretch();
  euler_current_value_layout->addWidget(yaw_value_label_);
  euler_current_value_layout->addStretch();

  connect(roll_slider_, &QSlider::valueChanged, this, &Go2Services::onEulerChanged);
  connect(pitch_slider_, &QSlider::valueChanged, this, &Go2Services::onEulerChanged);
  connect(yaw_slider_, &QSlider::valueChanged, this, &Go2Services::onEulerChanged);

  QGroupBox * euler_group = new QGroupBox();
  QVBoxLayout * euler_layout = new QVBoxLayout();
  gait_layout->setSpacing(1);
  gait_layout->setContentsMargins(1, 1, 1, 1);
  euler_layout->addWidget(euler_label);
  euler_layout->addLayout(euler_current_value_layout);
  euler_layout->addLayout(roll_slider_layout);
  euler_layout->addLayout(pitch_slider_layout);
  euler_layout->addLayout(yaw_slider_layout);
  euler_group->setLayout(euler_layout);

  layout->addWidget(euler_group);

  // Foot Raise Height Section
  QLabel * foot_raise_label = new QLabel("<h3 align='center'>Foot Raise Height</h3>");
  foot_raise_label->setStyleSheet("font-size: 10px;");
  foot_raise_slider_ = new QSlider(Qt::Horizontal);
  foot_raise_slider_->setMinimum(-60);  // Representa -0.06
  foot_raise_slider_->setMaximum(30);   // Representa 0.03
  foot_raise_slider_->setValue(0);      // Valor inicial
  foot_raise_slider_->setTickInterval(10);
  foot_raise_slider_->setTickPosition(QSlider::TicksBelow);

  QLabel * min_foot_raise_label = new QLabel("-0.06");
  QLabel * max_foot_raise_label = new QLabel("0.03");

  foot_raise_current_value_label_ = new QLabel(QString::number(static_cast<float>(0)));

  connect(foot_raise_slider_, &QSlider::valueChanged, this, &Go2Services::onFootRaiseHeightChanged);

  QHBoxLayout * foot_raise_slider_layout = new QHBoxLayout();
  foot_raise_slider_layout->addWidget(min_foot_raise_label);
  foot_raise_slider_layout->addWidget(foot_raise_slider_);
  foot_raise_slider_layout->addWidget(max_foot_raise_label);

  QHBoxLayout * foot_raise_current_value_layout = new QHBoxLayout();
  foot_raise_current_value_layout->addStretch();
  foot_raise_current_value_layout->addWidget(foot_raise_current_value_label_);
  foot_raise_current_value_layout->addStretch();

  QGroupBox * foot_raise_group = new QGroupBox();
  QVBoxLayout * foot_raise_layout = new QVBoxLayout();
  foot_raise_layout->setSpacing(1);
  foot_raise_layout->setContentsMargins(1, 1, 1, 1);
  foot_raise_layout->addWidget(foot_raise_label);
  foot_raise_layout->addLayout(foot_raise_current_value_layout);
  foot_raise_layout->addLayout(foot_raise_slider_layout);
  foot_raise_group->setLayout(foot_raise_layout);

  layout->addWidget(foot_raise_group);

  // Pose Section
  QLabel * pose_label = new QLabel("<h3 align='center'>Pose</h3>");
  pose_label->setStyleSheet("font-size: 10px;");

  pose_true_button_ = new QPushButton("True");
  pose_false_button_ = new QPushButton("False");
  pose_false_button_->setStyleSheet("background-color: green;");

  QHBoxLayout * pose_button_layout = new QHBoxLayout();
  pose_button_layout->addWidget(pose_true_button_);
  pose_button_layout->addWidget(pose_false_button_);

  connect(pose_true_button_, &QPushButton::clicked, this, [this]() {onPoseClicked(true);});
  connect(pose_false_button_, &QPushButton::clicked, this, [this]() {onPoseClicked(false);});

  QGroupBox * pose_group = new QGroupBox();
  QVBoxLayout * pose_layout = new QVBoxLayout();
  pose_layout->setSpacing(1);
  pose_layout->setContentsMargins(1, 1, 1, 1);
  pose_layout->addWidget(pose_label);
  pose_layout->addLayout(pose_button_layout);
  pose_group->setLayout(pose_layout);

  layout->addWidget(pose_group);

  // Speed Level Section
  QLabel * speed_label = new QLabel("<h3 align='center'>Speed Level</h3>");
  speed_label->setStyleSheet("font-size: 10px;");

  speed_lvl_slider_ = new QSlider(Qt::Horizontal);
  speed_lvl_slider_->setMinimum(-1);
  speed_lvl_slider_->setMaximum(1);
  speed_lvl_slider_->setValue(0);
  speed_lvl_slider_->setTickInterval(1);
  speed_lvl_slider_->setTickPosition(QSlider::TicksBelow);

  QLabel * min_speed_label = new QLabel("-1");
  QLabel * max_speed_label = new QLabel("1");
  speed_current_value_label_ = new QLabel(QString::number(0));

  connect(speed_lvl_slider_, &QSlider::valueChanged, this, &Go2Services::onSpeedLevelChanged);

  QHBoxLayout * speed_slider_layout = new QHBoxLayout();
  speed_slider_layout->addWidget(min_speed_label);
  speed_slider_layout->addWidget(speed_lvl_slider_);
  speed_slider_layout->addWidget(max_speed_label);

  QHBoxLayout * speed_current_value_layout = new QHBoxLayout();
  speed_current_value_layout->addStretch();
  speed_current_value_layout->addWidget(speed_current_value_label_);
  speed_current_value_layout->addStretch();

  QGroupBox * speed_group = new QGroupBox();
  QVBoxLayout * speed_layout = new QVBoxLayout();
  speed_layout->setSpacing(1);
  speed_layout->setContentsMargins(1, 1, 1, 1);
  speed_layout->addWidget(speed_label);
  speed_layout->addLayout(speed_current_value_layout);
  speed_layout->addLayout(speed_slider_layout);
  speed_group->setLayout(speed_layout);

  layout->addWidget(speed_group);

  // Switch Gait Section
  QLabel * switch_gait_label = new QLabel("<h3 align='center'>Switch Gait</h3>");
  switch_gait_label->setStyleSheet("font-size: 10px;");

  gait_trot_button_ = new QPushButton("Trot");
  gait_trot_run_button_ = new QPushButton("Trot Run");
  gait_forward_climb_button_ = new QPushButton("Forward Climb");
  gait_reverse_climb_button_ = new QPushButton("Reverse Climb");
  gait_trot_button_->setStyleSheet("background-color: green;");

  connect(gait_trot_button_, &QPushButton::clicked, this, [this]() {onSwitchGaitClicked(1);});
  connect(gait_trot_run_button_, &QPushButton::clicked, this, [this]() {onSwitchGaitClicked(2);});
  connect(
    gait_forward_climb_button_, &QPushButton::clicked, this,
    [this]() {onSwitchGaitClicked(3);});
  connect(
    gait_reverse_climb_button_, &QPushButton::clicked, this,
    [this]() {onSwitchGaitClicked(4);});

  QHBoxLayout * gait_button_layout_01 = new QHBoxLayout();
  gait_button_layout_01->addWidget(gait_trot_button_);
  gait_button_layout_01->addWidget(gait_trot_run_button_);

  QHBoxLayout * gait_button_layout_02 = new QHBoxLayout();
  gait_button_layout_02->addWidget(gait_forward_climb_button_);
  gait_button_layout_02->addWidget(gait_reverse_climb_button_);

  QGroupBox * switch_gait_group = new QGroupBox();
  QVBoxLayout * switch_gait_layout = new QVBoxLayout();
  switch_gait_layout->setSpacing(1);
  switch_gait_layout->setContentsMargins(1, 1, 1, 1);
  switch_gait_layout->addWidget(switch_gait_label);
  switch_gait_layout->addLayout(gait_button_layout_01);
  switch_gait_layout->addLayout(gait_button_layout_02);
  switch_gait_group->setLayout(switch_gait_layout);

  layout->addWidget(switch_gait_group);

  // Switch Joystick Section
  QLabel * switch_joystick_label = new QLabel("<h3 align='center'>Switch Joystick</h3>");
  switch_joystick_label->setStyleSheet("font-size: 10px;");

  joystick_true_button_ = new QPushButton("True");
  joystick_false_button_ = new QPushButton("False");
  joystick_false_button_->setStyleSheet("background-color: green;");

  connect(
    joystick_true_button_, &QPushButton::clicked, this, [this]() {
      onSwitchJoystickClicked(true);
    });
  connect(
    joystick_false_button_, &QPushButton::clicked, this, [this]() {
      onSwitchJoystickClicked(false);
    });

  QHBoxLayout * joystick_button_layout = new QHBoxLayout();
  joystick_button_layout->addWidget(joystick_true_button_);
  joystick_button_layout->addWidget(joystick_false_button_);

  QGroupBox * switch_joystick_group = new QGroupBox();
  QVBoxLayout * switch_joystick_layout = new QVBoxLayout();
  switch_joystick_layout->setSpacing(1);
  switch_joystick_layout->setContentsMargins(1, 1, 1, 1);
  switch_joystick_layout->addWidget(switch_joystick_label);
  switch_joystick_layout->addLayout(joystick_button_layout);
  switch_joystick_group->setLayout(switch_joystick_layout);

  layout->addWidget(switch_joystick_group);

  container->setLayout(layout);
  scroll_area->setWidget(container);

  QVBoxLayout * main_layout = new QVBoxLayout(this);
  main_layout->addWidget(scroll_area);

  setLayout(main_layout);
}

Go2Services::~Go2Services()
{
}

void Go2Services::onHeightChanged(int value)
{
  float height = static_cast<float>(value) / 1000.0f;
  body_height_current_value_label_->setText(QString::number(height));

  auto request = std::make_shared<go2_interfaces::srv::BodyHeight::Request>();
  request->height = height;

  body_height_client_->async_send_request(request);
}

void Go2Services::onContinuousGaitClicked(bool flag)
{
  auto request = std::make_shared<go2_interfaces::srv::ContinuousGait::Request>();
  request->flag = flag;

  if (flag) {
    gait_true_button_->setStyleSheet("background-color: green;");
    gait_false_button_->setStyleSheet("");
  } else {
    gait_true_button_->setStyleSheet("");
    gait_false_button_->setStyleSheet("background-color: green;");
  }

  continuous_gait_client_->async_send_request(request);
}

void Go2Services::onEulerChanged()
{
  float roll = static_cast<float>(roll_slider_->value()) / 100.0f;
  float pitch = static_cast<float>(pitch_slider_->value()) / 100.0f;
  float yaw = static_cast<float>(yaw_slider_->value()) / 100.0f;

  roll_value_label_->setText("Roll: " + QString::number(roll));
  pitch_value_label_->setText("Pitch: " + QString::number(pitch));
  yaw_value_label_->setText("Yaw: " + QString::number(yaw));

  auto request = std::make_shared<go2_interfaces::srv::Euler::Request>();
  request->roll = roll;
  request->pitch = pitch;
  request->yaw = yaw;

  euler_client_->async_send_request(request);
}

void Go2Services::onFootRaiseHeightChanged(int value)
{
  float height = static_cast<float>(value) / 1000.0f;
  foot_raise_current_value_label_->setText(QString::number(height));

  auto request = std::make_shared<go2_interfaces::srv::FootRaiseHeight::Request>();
  request->height = height;

  foot_raise_height_client_->async_send_request(request);
}

void Go2Services::onPoseClicked(bool flag)
{
  auto request = std::make_shared<go2_interfaces::srv::Pose::Request>();
  request->flag = flag;

  if (flag) {
    pose_true_button_->setStyleSheet("background-color: green;");
    pose_false_button_->setStyleSheet("");
  } else {
    pose_true_button_->setStyleSheet("");
    pose_false_button_->setStyleSheet("background-color: green;");
  }

  pose_client_->async_send_request(request);
}

void Go2Services::onSpeedLevelChanged(int level)
{
  speed_current_value_label_->setText(QString::number(level));

  auto request = std::make_shared<go2_interfaces::srv::SpeedLevel::Request>();
  request->level = level;

  speed_level_client_->async_send_request(request);
}

void Go2Services::onSwitchGaitClicked(int gait)
{
  auto request = std::make_shared<go2_interfaces::srv::SwitchGait::Request>();
  request->d = gait;

  if (gait == 1) {
    gait_trot_button_->setStyleSheet("background-color: green;");
    gait_trot_run_button_->setStyleSheet("");
    gait_forward_climb_button_->setStyleSheet("");
    gait_reverse_climb_button_->setStyleSheet("");
  } else if (gait == 2) {
    gait_trot_button_->setStyleSheet("");
    gait_trot_run_button_->setStyleSheet("background-color: green;");
    gait_forward_climb_button_->setStyleSheet("");
    gait_reverse_climb_button_->setStyleSheet("");
  } else if (gait == 3) {
    gait_trot_button_->setStyleSheet("");
    gait_trot_run_button_->setStyleSheet("");
    gait_forward_climb_button_->setStyleSheet("background-color: green;");
    gait_reverse_climb_button_->setStyleSheet("");
  } else if (gait == 4) {
    gait_trot_button_->setStyleSheet("");
    gait_trot_run_button_->setStyleSheet("");
    gait_forward_climb_button_->setStyleSheet("");
    gait_reverse_climb_button_->setStyleSheet("background-color: green;");
  }

  switch_gait_client_->async_send_request(request);
}

void Go2Services::onSwitchJoystickClicked(bool flag)
{
  auto request = std::make_shared<go2_interfaces::srv::SwitchJoystick::Request>();
  request->flag = flag;

  if (flag) {
    joystick_true_button_->setStyleSheet("background-color: green;");
    joystick_false_button_->setStyleSheet("");
  } else {
    joystick_true_button_->setStyleSheet("");
    joystick_false_button_->setStyleSheet("background-color: green;");
  }

  switch_joystick_client_->async_send_request(request);
}

}  // namespace go2_rviz
