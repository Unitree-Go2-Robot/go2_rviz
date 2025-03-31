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

#ifndef GO2_RVIZ_GO2_VUI_HPP_
#define GO2_RVIZ_GO2_VUI_HPP_

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QScrollArea>
#include <QGroupBox>
#include <rclcpp/rclcpp.hpp>
#include <go2_interfaces/srv/set_brightness.hpp>
#include <go2_interfaces/srv/set_volume.hpp>


namespace go2_rviz
{

class Go2VUI : public QWidget
{
  Q_OBJECT

public:
  explicit Go2VUI(rclcpp::Node::SharedPtr node, QWidget * parent = nullptr);
  ~Go2VUI();

private slots:
  void onBrightnessChanged(int value);
  void onVolumeChanged(int value);

private:
  rclcpp::Node::SharedPtr node_;

  // Service clients
  rclcpp::Client<go2_interfaces::srv::SetBrightness>::SharedPtr brightness_client_;
  rclcpp::Client<go2_interfaces::srv::SetVolume>::SharedPtr volume_client_;

  // UI Elements
  QSlider * brightness_slider_;
  QSlider * volume_slider_;
};

}  // namespace go2_rviz

#endif  // GO2_RVIZ_GO2_VUI_HPP_
