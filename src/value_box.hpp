#pragma once
namespace variable_controller {
	class ValueBox {
		std::map<std::string, int> val_ints_;
		std::map<std::string, float> val_floats_;
		std::map<std::string, std::string> val_strings_;
		public:
			ValueBox(){};
			virtual ~ValueBox(){};
			void set(std::string value_name,const int& value){
				val_ints_[value_name] = value;
			};
			
			bool is_exist_as_int(std::string name){
				return val_ints_.find(name)!=val_ints_.end();
			};
			
			bool is_exist_as_float(std::string name){
				return val_floats_.find(name)!=val_floats_.end();
			};
			
			bool is_exist_as_string(std::string name){
				return val_strings_.find(name)!=val_strings_.end();
			};
			
			std::string type_of(std::string value_name){
				std::string type_name;
				if(is_exist_as_int(value_name)){
					type_name = "int";
				}else if( is_exist_as_float(value_name)){
					type_name = "float";
				}else if( is_exist_as_string(value_name)){
					type_name = "string";
				};
				return type_name;
			};
			
			void set(std::string value_name,const float& value){
				val_floats_[value_name] = value;
			};
			
			void set(std::string value_name,const std::string& value){
				val_strings_[value_name] = value;
			};
			
			void get(std::string value_name, int& value){
				value = val_ints_[value_name];
			};
			
			void get(std::string value_name, float& value){
				value = val_floats_[value_name];
			};
			
			void get(std::string value_name, std::string& value){
				value = val_strings_[value_name];
			};
			
			int& get_int_ref(std::string value_name){
				return val_ints_.at(value_name);
			};
			float& get_float_ref(std::string value_name){
				return val_floats_.at(value_name);
			};
			std::string& get_string_ref(std::string value_name){
				return val_strings_.at(value_name);
			};
			float* get_float_ptr(std::string value_name){
				return &val_floats_.at(value_name);
			};
	};
} // namespace variable_controller
