var Device = require('./Device');

var NodeType = {Type_4:4,Type_6:6};

module.exports = function Node(id,type) {

	this.powerUsage_=0.0;
	this.Devices    = [];
	this.IRDevices  = [];
	this.type_      = type;
	this.id_        = id;

	this.addDevices = function(number){
		for (var i = 1; i<=number ; i++) {
			this.addDevice(new Device(i,"Default"));
			console.log("Device Added : " + "Device " + i);
		}
	};
	this.type = function(){
    	return this.type_;
	};

	this.powerUsage = function(){
		return this.powerUsage_;
	};

	this.setPowerUsage = function(){
		return this.powerUsage;
	};

	this.id = function(){
		return this.id_;
	};

	this.addDevice = function(device){
		
		switch(device.type()){

			case 'Default':
				this.Devices.push(device);
				break;
			case 'IR':
		        this.IRDevices.push(device);
			    break;
		};
	};


	this.getDevice =function(deviceId){
		for (var i = 0; i < this.Devices.length; i++) {
			if(this.Devices[i].id() == deviceId){
				return this.Devices[i];
			}
		}
	};
	

	// call class functions and variables

	this.addDevices(this.type_);
}
