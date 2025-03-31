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

#include "go2_rviz/Go2VUI.hpp"

#include <QHBoxLayout>

namespace go2_rviz
{

Go2VUI::Go2VUI(rclcpp::Node::SharedPtr node, QWidget * parent)
: QWidget(parent), node_(node)
{
  brightness_client_ = node_->create_client<go2_interfaces::srv::SetBrightness>("/set_brightness");
  volume_client_ = node_->create_client<go2_interfaces::srv::SetVolume>("/set_volume");

  QVBoxLayout * layout = new QVBoxLayout(this);
  QWidget * container = new QWidget();
  QScrollArea * scroll_area = new QScrollArea(this);
  scroll_area->setWidgetResizable(true);

  // Brightness Section
  QLabel * brightness_label = new QLabel("<h3 align='center'>Brightness</h3>");
  brightness_label->setStyleSheet("font-size: 10px;");
  brightness_slider_ = new QSlider(Qt::Horizontal);
  brightness_slider_->setMinimum(0);
  brightness_slider_->setMaximum(10);
  brightness_slider_->setValue(0);
  brightness_slider_->setTickInterval(1);
  brightness_slider_->setTickPosition(QSlider::TicksBelow);

  connect(brightness_slider_, &QSlider::valueChanged, this, &Go2VUI::onBrightnessChanged);

  QGroupBox * brightness_group = new QGroupBox();
  QVBoxLayout * brightness_layout = new QVBoxLayout();
  brightness_layout->setSpacing(1);
  brightness_layout->setContentsMargins(1, 1, 1, 1);
  brightness_layout->addWidget(brightness_label);
  brightness_layout->addWidget(brightness_slider_);
  brightness_group->setLayout(brightness_layout);

  layout->addWidget(brightness_group);

  // Volume Section
  QLabel * volume_label = new QLabel("<h3 align='center'>Volume</h3>");
  volume_label->setStyleSheet("font-size: 10px;");
  volume_slider_ = new QSlider(Qt::Horizontal);
  volume_slider_->setMinimum(0);
  volume_slider_->setMaximum(10);
  volume_slider_->setValue(5);
  volume_slider_->setTickInterval(1);
  volume_slider_->setTickPosition(QSlider::TicksBelow);

  connect(volume_slider_, &QSlider::valueChanged, this, &Go2VUI::onVolumeChanged);

  QGroupBox * volume_group = new QGroupBox();
  QVBoxLayout * volume_layout = new QVBoxLayout();
  volume_layout->setSpacing(1);
  volume_layout->setContentsMargins(1, 1, 1, 1);
  volume_layout->addWidget(volume_label);
  volume_layout->addWidget(volume_slider_);
  volume_group->setLayout(volume_layout);

  layout->addWidget(volume_group);

  container->setLayout(layout);
  scroll_area->setWidget(container);

  QVBoxLayout * main_layout = new QVBoxLayout(this);
  main_layout->addWidget(scroll_area);

  setLayout(main_layout);
}

Go2VUI::~Go2VUI()
{
}

void Go2VUI::onBrightnessChanged(int value)
{
  auto request = std::make_shared<go2_interfaces::srv::SetBrightness::Request>();
  request->brightness = value;

  brightness_client_->async_send_request(request);
}

void Go2VUI::onVolumeChanged(int value)
{
  auto request = std::make_shared<go2_interfaces::srv::SetVolume::Request>();
  request->volume = value;

  volume_client_->async_send_request(request);
}

}  // namespace go2_rviz
