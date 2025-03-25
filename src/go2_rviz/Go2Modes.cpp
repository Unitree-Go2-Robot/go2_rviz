#include "go2_rviz/Go2Modes.hpp"

#include <QHBoxLayout>

namespace go2_rviz
{

Go2Modes::Go2Modes(rclcpp::Node::SharedPtr node, QWidget *parent)
: QWidget(parent), node_(node)
{
  mode_client_ = node_->create_client<go2_interfaces::srv::Mode>("/mode");

  QPushButton* damp_button_ = new QPushButton("Damp");
  QPushButton* balance_stand_button_ = new QPushButton("BalanceStand");
  QPushButton* stop_move_button_ = new QPushButton("StopMove");
  QPushButton* stand_up_button_ = new QPushButton("StandUp");
  QPushButton* stand_down_button_ = new QPushButton("StandDown");
  QPushButton* recovery_stand_button_ = new QPushButton("RecoveryStand");
  QPushButton* euler_button_ = new QPushButton("Euler");
  QPushButton* move_button_ = new QPushButton("Move");
  QPushButton* sit_button_ = new QPushButton("Sit");
  QPushButton* rise_sit_button_ = new QPushButton("RiseSit");
  QPushButton* switch_gait_button_ = new QPushButton("SwitchGait");
  QPushButton* trigger_button_ = new QPushButton("Trigger");
  QPushButton* body_height_button_ = new QPushButton("BodyHeight");
  QPushButton* foot_raise_height_button_ = new QPushButton("FootRaiseHeight");
  QPushButton* speed_level_button_ = new QPushButton("SpeedLevel");
  QPushButton* hello_button_ = new QPushButton("Hello");
  QPushButton* stretch_button_ = new QPushButton("Stretch");
  QPushButton* trajectory_follow_button_ = new QPushButton("TrajectoryFollow");
  QPushButton* continuous_gait_button_ = new QPushButton("ContinuousGait");
  QPushButton* content_button_ = new QPushButton("Content");
  QPushButton* wallow_button_ = new QPushButton("Wallow");
  QPushButton* dance1_button_ = new QPushButton("Dance1");
  QPushButton* dance2_button_ = new QPushButton("Dance2");
  QPushButton* switch_joystick_button_ = new QPushButton("SwitchJoystick");
  QPushButton* pose_button_ = new QPushButton("Pose");
  QPushButton* scrape_button_ = new QPushButton("Scrape");
  QPushButton* front_flip_button_ = new QPushButton("FrontFlip");
  QPushButton* front_jump_button_ = new QPushButton("FrontJump");
  QPushButton* front_pounce_button_ = new QPushButton("FrontPounce");
  QPushButton* wiggle_hips_button_ = new QPushButton("WiggleHips");
  QPushButton* economic_gait_button_ = new QPushButton("EconomicGait");
  QPushButton* finger_heart_button_ = new QPushButton("FingerHeart");
  QPushButton* dance3_button_ = new QPushButton("Dance3");
  QPushButton* dance4_button_ = new QPushButton("Dance4");
  QPushButton* hop_spin_left_button_ = new QPushButton("HopSpinLeft");
  QPushButton* hop_spin_right_button_ = new QPushButton("HopSpinRight");
  QPushButton* left_flip_button_ = new QPushButton("LeftFlip");
  QPushButton* back_flip_button_ = new QPushButton("BackFlip");
  QPushButton* free_walk_button_ = new QPushButton("FreeWalk");
  QPushButton* free_bound_button_ = new QPushButton("FreeBound");
  QPushButton* free_jump_button_ = new QPushButton("FreeJump");
  QPushButton* free_avoid_button_ = new QPushButton("FreeAvoid");
  QPushButton* walk_stair_button_ = new QPushButton("WalkStair");
  QPushButton* walk_up_right_button_ = new QPushButton("WalkUpRight");
  QPushButton* cross_step_button_ = new QPushButton("CrossStep");

  connect(damp_button_, &QPushButton::clicked, this, [this]() { onModeChanged("damp"); });
  connect(balance_stand_button_, &QPushButton::clicked, this, [this]() { onModeChanged("balance_stand"); });
  connect(stop_move_button_, &QPushButton::clicked, this, [this]() { onModeChanged("stop_move"); });
  connect(stand_up_button_, &QPushButton::clicked, this, [this]() { onModeChanged("stand_up"); });
  connect(stand_down_button_, &QPushButton::clicked, this, [this]() { onModeChanged("stand_down"); });
  connect(recovery_stand_button_, &QPushButton::clicked, this, [this]() { onModeChanged("recovery_stand"); });
  connect(euler_button_, &QPushButton::clicked, this, [this]() { onModeChanged("euler"); });
  connect(move_button_, &QPushButton::clicked, this, [this]() { onModeChanged("move"); });
  connect(sit_button_, &QPushButton::clicked, this, [this]() { onModeChanged("sit"); });
  connect(rise_sit_button_, &QPushButton::clicked, this, [this]() { onModeChanged("rise_sit"); });
  connect(switch_gait_button_, &QPushButton::clicked, this, [this]() { onModeChanged("switch_gait"); });
  connect(trigger_button_, &QPushButton::clicked, this, [this]() { onModeChanged("trigger"); });
  connect(body_height_button_, &QPushButton::clicked, this, [this]() { onModeChanged("body_height"); });
  connect(foot_raise_height_button_, &QPushButton::clicked, this, [this]() { onModeChanged("foot_raise_height"); });
  connect(speed_level_button_, &QPushButton::clicked, this, [this]() { onModeChanged("speed_level"); });
  connect(hello_button_, &QPushButton::clicked, this, [this]() { onModeChanged("hello"); });
  connect(stretch_button_, &QPushButton::clicked, this, [this]() { onModeChanged("stretch"); });
  connect(trajectory_follow_button_, &QPushButton::clicked, this, [this]() { onModeChanged("trajectory_follow"); });
  connect(continuous_gait_button_, &QPushButton::clicked, this, [this]() { onModeChanged("continuous_gait"); });
  connect(content_button_, &QPushButton::clicked, this, [this]() { onModeChanged("content"); });
  connect(wallow_button_, &QPushButton::clicked, this, [this]() { onModeChanged("wallow"); });
  connect(dance1_button_, &QPushButton::clicked, this, [this]() { onModeChanged("dance1"); });
  connect(dance2_button_, &QPushButton::clicked, this, [this]() { onModeChanged("dance2"); });
  connect(switch_joystick_button_, &QPushButton::clicked, this, [this]() { onModeChanged("switch_joystick"); });
  connect(pose_button_, &QPushButton::clicked, this, [this]() { onModeChanged("pose"); });
  connect(scrape_button_, &QPushButton::clicked, this, [this]() { onModeChanged("scrape"); });
  connect(front_flip_button_, &QPushButton::clicked, this, [this]() { onModeChanged("front_flip"); });
  connect(front_jump_button_, &QPushButton::clicked, this, [this]() { onModeChanged("front_jump"); });
  connect(front_pounce_button_, &QPushButton::clicked, this, [this]() { onModeChanged("front_pounce"); });
  connect(wiggle_hips_button_, &QPushButton::clicked, this, [this]() { onModeChanged("wiggle_hips"); });
  connect(economic_gait_button_, &QPushButton::clicked, this, [this]() { onModeChanged("economic_gait"); });
  connect(finger_heart_button_, &QPushButton::clicked, this, [this]() { onModeChanged("finger_heart"); });
  connect(dance3_button_, &QPushButton::clicked, this, [this]() { onModeChanged("dance3"); });
  connect(dance4_button_, &QPushButton::clicked, this, [this]() { onModeChanged("dance4"); });
  connect(hop_spin_left_button_, &QPushButton::clicked, this, [this]() { onModeChanged("hop_spin_left"); });
  connect(hop_spin_right_button_, &QPushButton::clicked, this, [this]() { onModeChanged("hop_spin_right"); });
  connect(left_flip_button_, &QPushButton::clicked, this, [this]() { onModeChanged("left_flip"); });
  connect(back_flip_button_, &QPushButton::clicked, this, [this]() { onModeChanged("back_flip"); });
  connect(free_walk_button_, &QPushButton::clicked, this, [this]() { onModeChanged("free_walk"); });
  connect(free_bound_button_, &QPushButton::clicked, this, [this]() { onModeChanged("free_bound"); });
  connect(free_jump_button_, &QPushButton::clicked, this, [this]() { onModeChanged("free_jump"); });
  connect(free_avoid_button_, &QPushButton::clicked, this, [this]() { onModeChanged("free_avoid"); });
  connect(walk_stair_button_, &QPushButton::clicked, this, [this]() { onModeChanged("walk_stair"); });
  connect(walk_up_right_button_, &QPushButton::clicked, this, [this]() { onModeChanged("walk_up_right"); });
  connect(cross_step_button_, &QPushButton::clicked, this, [this]() { onModeChanged("cross_step"); });


  QVBoxLayout *layout = new QVBoxLayout(this);

  QList<QPushButton*> buttons = {
    damp_button_, balance_stand_button_, stop_move_button_, stand_up_button_,
    stand_down_button_, recovery_stand_button_, euler_button_, move_button_,
    sit_button_, rise_sit_button_, switch_gait_button_, trigger_button_,
    body_height_button_, foot_raise_height_button_, speed_level_button_, hello_button_,
    stretch_button_, trajectory_follow_button_, continuous_gait_button_, content_button_,
    wallow_button_, dance1_button_, dance2_button_,
    switch_joystick_button_, pose_button_,
    scrape_button_, front_flip_button_, front_jump_button_, front_pounce_button_,
    wiggle_hips_button_, economic_gait_button_, finger_heart_button_,
    dance3_button_, dance4_button_, hop_spin_left_button_, hop_spin_right_button_,
    left_flip_button_, back_flip_button_, free_walk_button_, free_bound_button_,
    free_jump_button_, free_avoid_button_, walk_stair_button_, walk_up_right_button_, cross_step_button_
  };


  for (int i = 0; i < buttons.size(); i += 2) {
    QHBoxLayout *row = new QHBoxLayout();
    row->addWidget(buttons[i]);

    if (i + 1 < buttons.size()) {
      row->addWidget(buttons[i + 1]);
    }

    layout->addLayout(row); 
  }

  setLayout(layout);
}

Go2Modes::~Go2Modes()
{
}

void Go2Modes::onModeChanged(std::string mode)
{
  auto request = std::make_shared<go2_interfaces::srv::Mode::Request>();
  request->mode = mode;

  mode_client_->async_send_request(request);
}

}  // namespace go2_rviz
