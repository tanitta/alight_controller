#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "ofxMidi.h"

#include "value_box.hpp"
#include "controller_generator.hpp"
#include "network_gate.hpp";

class ofApp : public ofBaseApp,public ofxMidiListener{
	//xml
	//osc
	//gui
	// std::shared_ptr<variable_controller::ValueBox> value_box_sptr_;
	variable_controller::ValueBox value_box_;
	variable_controller::NetworkGate network_gate_;
	variable_controller::ControllerGenerator controller_generator_;
	std::shared_ptr<variable_controller::VariableController> variable_controller_;

	ofxMidiIn midi_in_;

	public:
	ofApp():
		value_box_(),
		network_gate_(value_box_),
		controller_generator_(value_box_,network_gate_){}
	virtual ~ofApp(){}

	void setup(){
		network_gate_.connect(8080,8090);

		ofBackground(32);
		variable_controller_ = controller_generator_.generate_from("profile1.xml");
		// variable_controller_->set_value_box(value_box_sptr_);
		midi_in_.listPorts();
		midi_in_.openPort(1);
		midi_in_.ignoreTypes(false,false,false);
		midi_in_.addListener(this);
	};

	void update(){
	};

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
	void guiEvent(ofxUIEventArgs &e){
		std::cout<<e.getName()<<std::endl;
		variable_controller_->gui_event(e);
	};

	void newMidiMessage(ofxMidiMessage& msg){
		std::string val_name = "midi_control_" + std::to_string(msg.control);
		// variable_controller_->set_value(value_name, (float)msg.value/127.0f);
		float val = (float)msg.value/127.0f;
		value_box_.set(val_name, val);
		std::cout<<val_name<<std::endl;

		std::string val_type = "float";
		if(val_type == "int"){
			int val;
			value_box_.get(val_name,val);
			network_gate_.send(val_name,val_type);
			// std::cout<<"send val(name : "<<val_name<<" type : "<<val_type<<" val : "<<val<<std::endl;
		};
		if(val_type == "float"){
			float val;
			value_box_.get(val_name,val);
			network_gate_.send(val_name,val_type);
			// std::cout<<"send val(name : "<<val_name<<" type : "<<val_type<<" val : "<<val<<std::endl;
		};
	};
};
