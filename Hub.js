var Node = require('./Node');

var DeviceState = {Online:"Online",Offline:"Offline"};

module.exports = function Hub(uniqueID,socket){
	this.uniqueID_ = uniqueID;
	this.Nodes = [];
	this.MobileDevices = [];
	this.curentState_;
	this.wifi_details;
	this.socket = socket;

	// this.property1 = 5;
	// this.property2 = "World";
	// this.method1 = function(arg1){
	// return arg1+" "+this.property2;
 //  }

	 this.addNode = function(name,type){
		this.Nodes.push(new Node(name,type));
	};

	this.nodeCount = function(){
		return this.Nodes.length;
	};

	this.removeNode = function(node){
		this.Nodes.splice(this.Nodes.indexOf(node), 1);
	};

	this.addMobileDevice = function(mobileDevice){
		this.MobileDevices.push(mobileDevice);
		return 1;
	};

	this.removeMobileDeive = function(mobileDevice){
		this.MobileDevices.splice(this.MobileDevices.indexOf(mobileDevice),1);
	};

	this.mobileDeviceCount = function(){
		return this.MobileDevices.length;
	};

	this.uniqueID = function(){
		return this.uniqueID_;
	};

	this.setUniqueID = function(uniqueID){
		this.uniqueID_ = uniqueID;
	}

	this.curentState = function(){
		return this.curentState_;
	};

	this.switchState = function(){
		if(this.curentState_ == DeviceState.Offline){
			 this.setCurrentState(DeviceState.Online);
			return;
		}
		this.setCurrentState(DeviceState.Offline);	
	};
	this.setCurrentState = function(state){
		this.curentState_ = state;
	};

	this.setWifiDetails = function(wifiDetails){
		console.log(wifiDetails);
	}
	this.printNodes = function(){
		console.log("length : " + this.Nodes.length);
		for (var i = 0; i < this.Nodes.length ; i++) {
			console.log(this.Nodes[i].name());
		}
	}; 

	this.broadCastToMobieDevices = function(data,event){

		console.log("MobileDevices length" + this.MobileDevices.length);

		for (var i = 0; i < this.MobileDevices.length; i++){
			this.MobileDevices[i].emit(event,data);
		}
	};
	this.emit = function(event,message){
		    socket.emit(event,message);
	};

}










