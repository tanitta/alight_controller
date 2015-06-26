#pragma once

#include "ofMain.h"
#include "ofxUI.h"
#include "controller_generator.hpp"

class ofApp : public ofBaseApp{
	//xml
	//osc
	//gui
	std::shared_ptr<variable_controller::VariableController> variable_controller_;
	variable_controller::ControllerGenerator controller_generator_;
	public:
		ofApp(){}
		virtual ~ofApp(){}
		void setup(){
			variable_controller_ = controller_generator_.generate_from("profile1.xml");
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
		
};
