// Copyright 2025 Juan Carlos Manzanares Serrano
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "go2_rviz/Go2ObstaclesAvoidance.hpp"

#include <QHBoxLayout>

namespace go2_rviz
{

Go2ObstaclesAvoidance::Go2ObstaclesAvoidance(rclcpp::Node::SharedPtr node, QWidget * parent)
: QWidget(parent), node_(node)
{
  switch_obstacles_avoidance_client_ =
    node_->create_client<go2_interfaces::srv::SetSwitchObstaclesAvoidance>(
    "/set_obstacles_avoidance");

  QVBoxLayout * layout = new QVBoxLayout(this);
  QWidget * container = new QWidget();
  QScrollArea * scroll_area = new QScrollArea(this);
  scroll_area->setWidgetResizable(true);

  // Switch Obstacles Avoidance Section
  QLabel * switch_label = new QLabel("<h3 align='center'>Switch Obstacles Avoidance</h3>");
  switch_label->setStyleSheet("font-size: 10px;");

  switch_true_button_ = new QPushButton("True");
  switch_false_button_ = new QPushButton("False");
  switch_true_button_->setStyleSheet("background-color: green;");

  connect(switch_true_button_, &QPushButton::clicked, this, [this]() {onSwitchChanged(1);});
  connect(switch_false_button_, &QPushButton::clicked, this, [this]() {onSwitchChanged(0);});

  QHBoxLayout * switch_button_layout = new QHBoxLayout();
  switch_button_layout->addWidget(switch_true_button_);
  switch_button_layout->addWidget(switch_false_button_);

  QVBoxLayout * switch_layout = new QVBoxLayout();
  switch_layout->setSpacing(1);
  switch_layout->setContentsMargins(1, 1, 1, 1);
  switch_layout->addWidget(switch_label);
  switch_layout->addLayout(switch_button_layout);

  QGroupBox * switch_group = new QGroupBox();
  switch_group->setLayout(switch_layout);

  layout->addWidget(switch_group);

  container->setLayout(layout);
  scroll_area->setWidget(container);

  QVBoxLayout * main_layout = new QVBoxLayout(this);
  main_layout->addWidget(scroll_area);

  setLayout(main_layout);
}

Go2ObstaclesAvoidance::~Go2ObstaclesAvoidance()
{
}

void Go2ObstaclesAvoidance::onSwitchChanged(int flag)
{
  auto request = std::make_shared<go2_interfaces::srv::SetSwitchObstaclesAvoidance::Request>();
  request->enable = flag;

  if (flag == 1) {
    switch_true_button_->setStyleSheet("background-color: green;");
    switch_false_button_->setStyleSheet("");
  } else {
    switch_true_button_->setStyleSheet("");
    switch_false_button_->setStyleSheet("background-color: green;");
  }

  switch_obstacles_avoidance_client_->async_send_request(request);
}

}  // namespace go2_rviz
