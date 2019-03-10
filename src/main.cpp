#include <math.h>
#include <uWS/uWS.h>
#include <iostream>
#include <string>
#include "json.hpp"
#include "PID.h"

// for convenience
using nlohmann::json;
using std::string;

// For converting back and forth between radians and degrees.
constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in string format will be returned,
// else the empty string "" will be returned.
string hasData(string s) {
  auto found_null = s.find("null");
  auto b1 = s.find_first_of("[");
  auto b2 = s.find_last_of("]");
  if (found_null != string::npos) {
    return "";
  }
  else if (b1 != string::npos && b2 != string::npos) {
    return s.substr(b1, b2 - b1 + 1);
  }
  return "";
}

int main() {
  uWS::Hub h;

  // This pid controll is specifically tailored to the steering wheel.
  // It should adjust the steering value based on the CTE
  PID steering_pid;
  double steering_k_p = 0.3;
  double steering_k_d = 1.9;
  double steering_k_i = 0.000;
  steering_pid.init(steering_k_p, steering_k_d, steering_k_i);

  // This pid controll is specifically tailored to the throttle.
  // It should reduce/increase the throttle depending on how fast
  // the CTE is increasing/decreasing (respectively)
  PID throttle_pid;
  double throttle_k_p = 0.0;
  double throttle_k_d = 0.05;
  double throttle_k_i = 0.0;
  throttle_pid.init(throttle_k_p, throttle_k_d, throttle_k_i);

  /**
   * TODO: Initialize the pid variable.
   */

  h.onMessage([&steering_pid, &throttle_pid](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length,
                     uWS::OpCode opCode) {
    // "42" at the start of the message means there's a websocket message event.
    // The 4 signifies a websocket message
    // The 2 signifies a websocket event
    if (length && length > 2 && data[0] == '4' && data[1] == '2') {
      auto s = hasData(string(data).substr(0, length));

      if (s != "") {
        auto j = json::parse(s);

        string event = j[0].get<string>();

        if (event == "telemetry") {
          // j[1] is the data JSON object
          double cte = std::stod(j[1]["cte"].get<string>());
          double speed = std::stod(j[1]["speed"].get<string>());
          double angle = std::stod(j[1]["steering_angle"].get<string>());

          /**
           * This is the core of the project. Using 2 controllers here to
           * control both the steering and the speed
           */
          steering_pid.updateError(cte);
          throttle_pid.updateError(cte);
          double steer_control = steering_pid.getControlSignal();
          double throttle_control = 0.3;  //throttle_pid.getControlSignal();

          // DEBUG
          std::cout << "CTE: " << cte
                    << "\tSteering Value: " << steer_control
                    // << "\tThrottle Value: " << throttle_control
                    << std::endl;

          json msgJson;
          msgJson["steering_angle"] = steer_control;
          msgJson["throttle"] = throttle_control;
          auto msg = "42[\"steer\"," + msgJson.dump() + "]";
          // std::cout << msg << std::endl;
          ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
        }  // end "telemetry" if
      } else {
        // Manual driving
        string msg = "42[\"manual\",{}]";
        ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
      }
    }  // end websocket message if
  }); // end h.onMessage

  h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
    std::cout << "Connected!!!" << std::endl;
  });

  h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code,
                         char *message, size_t length) {
    ws.close();
    std::cout << "Disconnected" << std::endl;
  });

  int port = 4567;
  if (h.listen(port)) {
    std::cout << "Listening to port " << port << std::endl;
  } else {
    std::cerr << "Failed to listen to port" << std::endl;
    return -1;
  }

  h.run();
}