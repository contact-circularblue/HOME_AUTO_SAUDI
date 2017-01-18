var Node = require('./Node');

var DeviceState = {Online:"Online",Offline:"Offline"};

module.exports = function Hub(uniqueID,socket){
	this.uniqueID_ = uniqueID;
	this.Nodes = [];
	this.MobileDevices = [];
	this.curentState_;
	this.wifi_details;
	this.socket = socket;
	this.check_alive;
	    
	 console.log("HUB.js SOCKET ID : " + socket.id);                      

	 this.addNode = function(name,type){
	 	var node = new Node(name,type);
		this.Nodes.push(node);
		return node;
	};

	this.nodeCount = function(){
		return this.Nodes.length;
	};

	this.removeNode = function(node){
		this.Nodes.splice(this.Nodes.indexOf(node), 1);
	};

	this.addMobileDevice = function(mobileDevice){
		if(!this.mobileDeviceExits(mobileDevice.id)){
				this.MobileDevices.push(mobileDevice);		
		}
		return 1;
	};

	this.removeMobileDeive = function(mobileDevice){
		this.MobileDevices.splice(this.MobileDevices.indexOf(mobileDevice),1);
	};

	this.mobileDeviceCount = function(){
		return this.MobileDevices.length;
	};
	this.mobileDeviceExits =function(socketId){
	    var output = this.MobileDevices.filter(function(item){  return item.id == socketId; });
	    if(output.isEmpty())
	    {
	          return false;
	    }
	    return true;
	}

	this.uniqueID = function(){
		return this.uniqueID_;
	};

	this.setUniqueID = function(uniqueID){
		this.uniqueID_ = uniqueID;
	};

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
		// console.log(wifiDetails);
	};
	this.printNodes = function(){
		console.log("length : " + this.Nodes.length);
		for (var i = 0; i < this.Nodes.length ; i++) {
			console.log(this.Nodes[i].name());
		}
	}; 

	this.broadCastToMobieDevices = function(data,event){
		console.log("BroadCast To Mobie Devices");
		// console.log("MobileDevices length" + this.MobileDevices.length);
		for (var i = 0; i < this.MobileDevices.length; i++){
			// console.log(this.MobileDevices[i].id);
			this.MobileDevices[i].emit(event,data);
		}
	};
	this.emit = function(event,message){

	       console.log("SOCKET ID : " + socket.id);	
	       console.log(message);	  
		    socket.emit(event,message);
	};

	this.getNode =function(nodeId){
		for (var i = 0; i < this.Nodes.length; i++) {
			if(this.Nodes[i].id() == nodeId){
				console.log("NODE FOUND");
				return this.Nodes[i];
			}
		}
	};
	this.checkAlive = function(data){
		this.check_alive = data;
	};
	this.isAlive = function(){
		return this.check_alive;
	};
	this.sendHeartBeat = function(){
		  //  socket.emit('heartbeat',"true");
		  //  socket.emit(Events.On.dummy,'hi');
		    socket.send('hi');    
	};
	this.getDateTime = function(){

	    var date = new Date();

	    var hour = date.getHours();
	    hour = (hour < 10 ? "0" : "") + hour;

	    var min  = date.getMinutes();
	    min = (min < 10 ? "0" : "") + min;

	    var sec  = date.getSeconds();
	    sec = (sec < 10 ? "0" : "") + sec;

	    var year = date.getFullYear();

	    var month = date.getMonth() + 1;
	    month = (month < 10 ? "0" : "") + month;

	    var day  = date.getDate();
	    day = (day < 10 ? "0" : "") + day;

	    return year + ":" + month + ":" + day + ":" + hour + ":" + min + ":" + sec;

	};
}










