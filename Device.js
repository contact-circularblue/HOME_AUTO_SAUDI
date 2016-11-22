
var DeviceState = {On:"On",Off:"off"};

module.exports = function Device(name){
	// var curentState_;
	// var name_;
	this.curentState_ = DeviceState.off;
	this.name_ = name;
	// this.setName(name);
	// // this.property1 = 5;
	// this.property2 = "World";
	// this.method1 = function(arg1){
	// 	return arg1+" "+this.property2;
	// }
	this.currentState = function(){
		return this.curentState_;
	};

	this.setName = function(name){
		this.name_ = name;
	};

	this.name = function(){
			return name_;
	};

	this.switchState = function(){
		if(this.curentState_ == DeviceState.Off){
			 this.setCurrentState(DeviceState.On);
			return;
		}
		setCurrentState(DeviceState.Off);	
	};
	this.setCurrentState = function(state){
		curentState_ = state;
	}; 
};