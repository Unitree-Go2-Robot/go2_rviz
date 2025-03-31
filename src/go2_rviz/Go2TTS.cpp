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

#include "go2_rviz/Go2TTS.hpp"

#include <QHBoxLayout>

namespace go2_rviz
{

  Go2TTS::Go2TTS(rclcpp::Node::SharedPtr node, QWidget *parent)
: QWidget(parent), node_(node)
{
  tts_client_ = node_->create_client<go2_interfaces::srv::Say>("/say");

  QVBoxLayout *layout = new QVBoxLayout();
  QWidget *container = new QWidget();
  QScrollArea *scroll_area = new QScrollArea(this);
  scroll_area->setWidgetResizable(true);

  // Sección TTS
  QLabel *tts_label = new QLabel("<h3 align='center'>TTS</h3>");
  tts_label->setStyleSheet("font-size: 10px;");

  QLineEdit *tts_input = new QLineEdit();
  tts_input->setPlaceholderText("Enter the text to say...");

  QPushButton *tts_button = new QPushButton("Say");
  connect(tts_button, &QPushButton::clicked, this, [this, tts_input]() {
      auto request = std::make_shared<go2_interfaces::srv::Say::Request>();
      request->text = tts_input->text().toStdString();

      tts_client_->async_send_request(request);
  });

  QGroupBox *tts_group = new QGroupBox();
  QVBoxLayout *tts_layout = new QVBoxLayout();
  tts_layout->setSpacing(1);
  tts_layout->setContentsMargins(1, 1, 1, 1);
  tts_layout->addWidget(tts_label);
  tts_layout->addWidget(tts_input);
  tts_layout->addWidget(tts_button);
  tts_group->setLayout(tts_layout);

  layout->addWidget(tts_group);

  container->setLayout(layout);
  scroll_area->setWidget(container);

  QVBoxLayout *main_layout = new QVBoxLayout(this);
  main_layout->addWidget(scroll_area);

  setLayout(main_layout);
}

Go2TTS::~Go2TTS()
{
}

}  // namespace go2_rviz
