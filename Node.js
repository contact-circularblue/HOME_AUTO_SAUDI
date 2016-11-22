var Device = require('./Device');

var NodeType = {Type_4:4,Type_6:6};

module.exports = function Node(name,type) {

	this.powerUsage_=0.0;
	this.Devices = [];
	this.type_ = type;
	this.name_ = name;

	this.addDevices = function(number){
		for (var i = 1; i<=number ; i++) {
			this.addDevice(new Device("Device " + i) );
			console.log("Device Added : " + "Device " + i);
		}
	};
	this.getType = function(){
    	return this.type_;
	};

	this.powerUsage = function(){
		return this.powerUsage_;
	};


	this.setPowerUsage = function(){
		return this.powerUsage;
	};

	this.name = function(){
		return this.name_;
	};

	this.setName =  function(name){
		 this.name_ = name;
	};

	this.addDevice = function(device){
		this.Devices.push(device);
	};

	// call class functions and variables

	this.addDevices(this.type_);


	
}
