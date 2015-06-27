#pragma once
#include "ofxXmlSettings.h"
#include "variable_controller.hpp"
#include "network_gate.hpp"

namespace variable_controller {
	class ControllerGenerator {
		std::string profile_name_;
		ofxXmlSettings xml_;
		
		std::shared_ptr<VariableController> variable_controller_;
		ValueBox& value_box_;
		NetworkGate& network_gate_;
		
		void save_xml(const std::string& name){

		};

		void load_xml(const std::string& str){
			std::string message;
			if(xml_.loadFile(str)){
				message = str+" loaded!";
				// isLoaded = true;
			}else{
				message = "unable to load "+str+" check data/ folder";
			}
			std::cout<<message<<std::endl;

		};
		
		void make_controller(){
			xml_.pushTag("guis");
			//gui毎の処理
			for (int gui_index = 0; gui_index < xml_.getNumTags("gui"); gui_index++) {
				//add gui
				std::string gui_name = xml_.getAttribute("gui","name", "", gui_index);
				variable_controller_->add_gui(gui_name);
				
				xml_.pushTag("gui",gui_index);
				std::vector<std::string> attribute_names;
				int num_widgets = xml_.getNumTags("widget");
				//widget毎の処理
				for (int widget_index = 0; widget_index < num_widgets; widget_index++) {
					xml_.getAttributeNames("widget",attribute_names,widget_index);
					
					std::map<std::string,std::string> params;
					for (auto&& attribute : attribute_names) {
						std::string attribute_data = xml_.getAttribute("widget",attribute, "", widget_index);
						params[attribute] = attribute_data;
					}
					variable_controller_->add_widget(params, gui_index);
				}
				xml_.popTag();
			}
			xml_.popTag();
		}

		public:
			ControllerGenerator(ValueBox& value_box, NetworkGate& network_gate):
				value_box_(value_box),
				network_gate_(network_gate),
				variable_controller_(new VariableController(value_box,network_gate)){};
			
			virtual ~ControllerGenerator(){};
			
			std::shared_ptr<VariableController> generate_from(std::string file_name){
				load_xml(file_name);
				make_controller();
				variable_controller_->reset_gui_position(212);
				return variable_controller_;
			};
	};
} // namespace variable_controller
