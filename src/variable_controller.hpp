#pragma once
#include "ofxUI.h"
#include "value_box.hpp"

namespace variable_controller {
	class VariableController {
		std::vector<std::shared_ptr<ofxUISuperCanvas>> guis_;
		// std::map<std::string, int> val_ints_;
		// std::map<std::string, float> val_floats_;
		// std::map<std::string, std::string> val_strings_;
		
		// std::shared_ptr<ValueBox> value_box_sptr_;
		ValueBox& value_box_;
		
		public:
			
		VariableController(ValueBox& value_box):value_box_(value_box){};

		virtual ~VariableController(){
		};

		void add_gui(std::string name){
			guis_.push_back(std::shared_ptr<ofxUISuperCanvas>(new ofxUISuperCanvas( name )));
			std::cout<<"gui size : "<<guis_.size()<<std::endl;
		};
		void reset_gui_position(const int& distance = 212){
			for(int gui_index = 0; gui_index < guis_.size(); gui_index++){
				guis_[gui_index]->setPosition(gui_index*distance,0);
				guis_[gui_index]->autoSizeToFitWidgets();
			}
		
		};
		
		// void set_value_box(std::shared_ptr<ValueBox> value_box_sptr){
		// 	value_box_sptr_ = value_box_sptr;
		// };
		
		void add_widget(std::map<std::string,std::string> params, const int gui_index){
			if(params["type"]=="Spacer"){
				guis_[gui_index]->addSpacer();
			};
			if(params["type"]=="Label"){
				guis_[gui_index]->addLabel(params["name"]);
			};
			if(params["type"]=="Slider"){
				if(params["val_type"] == "int"){
					int val_min = std::atoi(params["min"].c_str());
					int val_max = std::atoi(params["max"].c_str());
					if(value_box_.type_of(params["val_name"]) == ""){
						value_box_.set(params["val_name"],0);
						std::cout<<"val_name : "<<params["val_name"]<<" : "<<value_box_.get_int_ref(params["val_name"])<<std::endl;
					};
					guis_[gui_index]->addIntSlider(params["name"], val_min, val_max, &value_box_.get_int_ref(params["val_name"]));
				};
				// if(params["val_type"] == "int"){
				// 	int val_min = std::atoi(params["min"].c_str());
				// 	int val_max = std::atoi(params["max"].c_str());
				// 	// if(val_ints_.find(params["val_name"]) == val_ints_.end()){
				// 	// 	val_ints_[params["val_name"]] = 0;
				// 		value_box_.set(params["val_naame"],0);
				// 	// };
				// 	// guis_[gui_index]->addIntSlider(params["name"], val_min, val_max, &val_ints_.at(params["val_name"]));
				// 	guis_[gui_index]->addIntSlider(params["name"], val_min, val_max, &value_box_.get_int_ref(params["val_name"]));
				// };
				// value_box_.set("hoge",5.0f);
				// std::cout<<value_box_.get_float_ref("hoge")<<std::endl;
				if(params["val_type"] == "float"){
					float val_min = std::atof(params["min"].c_str());
					float val_max = std::atof(params["max"].c_str());
					if(value_box_.type_of(params["val_name"]) == ""){
						value_box_.set(params["val_name"],0.0f);
						std::cout<<"val_name : "<<params["val_name"]<<" : "<<value_box_.get_float_ref(params["val_name"])<<std::endl;
					};
					guis_[gui_index]->addSlider(params["name"], val_min, val_max, &value_box_.get_float_ref(params["val_name"]));
				};
			};
			std::cout<<params["type"]<<" to gui"<<gui_index<<std::endl;
			std::cout<<"gui"<<gui_index<<" size : "<<guis_[gui_index]->getWidgets().size()<<std::endl;
		};
		
		// void set_value(std::string name, int val){
		// 	val_ints_[name] = val;
		// };
		//
		// void set_value(std::string name, float val){
		// 	val_floats_[name] = val;
		// };
		//
		// void set_value(std::string name, std::string val){
		// 	val_strings_[name] = val;
		// };
		//
		// void get_value(std::string name, int& out){
		// 	out = val_ints_[name];
		// };
		// void get_value(std::string name, float& out){
		// 	out = val_floats_[name];
		// };
		// void get_value(std::string name, std::string& out){
		// 	out = val_strings_[name];
		// };

		void gui_event(ofxUIEventArgs &e){
			std::cout<<"event"<<std::endl;
		};
	};
} // namespace variable_controller
