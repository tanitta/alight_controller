#pragma once
#include"value_box.hpp"
#include "ofxOsc.h"
namespace variable_controller {
	class NetworkGate {

		ValueBox& value_box_;

		ofxOscReceiver receiver_;
		ofxOscSender sender_;

		std::string addres_from_value_name(const std::string value_name){
			std::string addres = value_name;
			std::replace(addres.begin(),addres.end(),'_','/');
			addres.insert(0,"/");
			return addres;
		};

		std::string value_name_from_addres(const std::string& addres){
			std::string val_name = addres;
			val_name.erase(0,1);
			std::replace(val_name.begin(),val_name.end(),'/','_');
			return val_name;
		};
		
		public:
		NetworkGate(ValueBox& value_box):
			value_box_(value_box)
			{};

		virtual ~NetworkGate(){};

		void connect(const int& send_port, const int& receive_port){
			sender_.setup("localhost",send_port);
			receiver_.setup(receive_port);
		};

		void send(std::string val_name, std::string val_type){
			ofxOscMessage message;
			message.setAddress(addres_from_value_name(val_name));
			message.addStringArg(val_type);
			if(val_type == "int"){
				int val;
				value_box_.get(val_name,val);
				message.addIntArg(val);
			}else if(val_type == "float"){
				float val;
				value_box_.get(val_name,val);
				message.addFloatArg(val);
			}else if(val_type == "string"){
				std::string val;
				value_box_.get(val_name,val);
				message.addStringArg(val);
			};
			sender_.sendMessage(message);
		};
		
		void receive(){
			while(receiver_.hasWaitingMessages()){
				ofxOscMessage m;
				receiver_.getNextMessage(&m);
				std::string val_name = value_name_from_addres(m.getAddress());
				std::string val_type = m.getArgAsString(0);
				if(val_type == "int"){
					int val = m.getArgAsInt32(1);
					value_box_.set(val_name,val);
					std::cout<<"received(name:"<<val_name<<" type:"<<val_type<<" val:"<<val<<")"<<std::endl;
					
				}else if(val_type == "float"){
					float val = m.getArgAsFloat(1);
					value_box_.set(val_name,val);
					std::cout<<"received(name:"<<val_name<<" type:"<<val_type<<" val:"<<val<<")"<<std::endl;
					
				}else if(val_type == "string"){
					std::string val = m.getArgAsString(1);
					value_box_.set(val_name,val);
					std::cout<<"received(name:"<<val_name<<" type:"<<val_type<<" val:"<<val<<")"<<std::endl;
				};
				std::cout<<m.getNumArgs()<<std::endl;
			};
		};
		
		void addListener(){};

		
	};
} // namespace variable_controller
