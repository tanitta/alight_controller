#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxMidi.h"

#include "value_box.hpp"
#include "controller_generator.hpp"
class ofApp : public ofBaseApp,public ofxMidiListener{
	//xml
	//osc
	//gui
	// std::shared_ptr<variable_controller::ValueBox> value_box_sptr_;
	variable_controller::ValueBox value_box_;
	std::shared_ptr<variable_controller::VariableController> variable_controller_;
	variable_controller::ControllerGenerator controller_generator_;
	
	ofxMidiIn midi_in_;
	public:
		ofApp():value_box_(),controller_generator_(value_box_){}
		virtual ~ofApp(){}
		void setup(){
			
			ofBackground(32);
			variable_controller_ = controller_generator_.generate_from("profile1.xml");
			// variable_controller_->set_value_box(value_box_sptr_);
			midi_in_.listPorts();
			midi_in_.openPort(1);
			midi_in_.ignoreTypes(false,false,false);
			midi_in_.addListener(this);
		};
		
		void update(){};
		void draw(){};

		void keyPressed(int key){};
		void keyReleased(int key){};
		void mouseMoved(int x, int y ){};
		void mouseDragged(int x, int y, int button){};
		void mousePressed(int x, int y, int button){};
		void mouseReleased(int x, int y, int button){};
		void windowResized(int w, int h){};
		void dragEvent(ofDragInfo dragInfo){};
		void gotMessage(ofMessage msg){};
		void exit(){
			midi_in_.closePort();
			midi_in_.removeListener(this);
		};
		void newMidiMessage(ofxMidiMessage& msg){
			std::string value_name = "midi_control_" + std::to_string(msg.control);
			// variable_controller_->set_value(value_name, (float)msg.value/127.0f);
			// value_box_.set(value_name, (float)msg.value/127.0f);
			std::cout<<value_name<<std::endl;
			
		};
};
