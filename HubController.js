var Hub = require('./Hub');
Hubs = [];
module.exports = {

	AddHub : function(uniqueID_,socket){

		var hub = new Hub(uniqueID_,socket);
		this.RemoveDuplicates(uniqueID_,hub);
		Hubs.push(hub);
		// console.log("Hub Added ("+__filename+")" );

		return hub;
	},

	PrintHubs : function(){

		console.log("Total Hubs connected : " + Hubs.length);

		for (var i = 0; i < Hubs.length; i++) {
		 	console.log("["+i+"]: "+Hubs[i].uniqueID());		 	
		};
	},

	HubExists : function(uniqueID){
	    var output = Hubs.filter(function(item){  return item.uniqueID() == uniqueID; });
	    if(output.isEmpty())
	    {
	          return false;
	    }
	    return true;
	},

	GetHub : function(uniqueID){
   		return (Hubs.find(o => o.uniqueID() === uniqueID));
	},

	RemoveHub : function(Hub){
		    Hubs.splice(Hubs.indexOf(Hub),1);
		    console.log("Hub Removed : "); 
		    console.log(Hub);
	},
    RemoveDuplicates : function(uniqueID_,hub){
    	//console.log(Hubs);
    		// console.log(" "+ Hubs.length);
    		for (var i = 0; i < Hubs.length; i++) {
		 		if(Hubs[i].uniqueID() == uniqueID_){
		 	//		console.log("mobile devices :")
		 	//		console.log(Hubs[i].MobileDevices);
		 			// var temp = 
		 			hub.MobileDevices = Hubs[i].MobileDevices.concat(hub.MobileDevices);
		 			for (var j = 0; j < hub.MobileDevices.length; j++) {
		 				hub.MobileDevices[j].Hub = hub;
		 			}
		 //			console.log("RemoveDuplicates  " + i);
		 			Hubs.splice(i,1);		
		 		}	
		 	}
		// console.log(Hubs);	 	
	},
	UpdateDevices : function(){
		console.log("UpdateDevices");
		for (var i = 0; i < Hubs.length; i++) {
			Hubs[i].sendHeartBeat();
		}
	}
};
