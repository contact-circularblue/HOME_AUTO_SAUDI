var Hub = require('./Hub');
Hubs = [];
module.exports = {

	AddHub : function(uniqueID_,socket){


		this.RemoveDuplicates(uniqueID_);

		var hub = new Hub(uniqueID_,socket);
		Hubs.push(hub);
		console.log("Hub Added ("+__filename+")" );

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
    RemoveDuplicates : function(uniqueID_){
    	//console.log(Hubs);
    		for (var i = 0; i < Hubs.length; i++) {
		 		if(Hubs[i].uniqueID() == uniqueID_){
		 			Hubs.splice(i,1);		
		 		}	
		 	}
		// console.log(Hubs);	 	
	}

};
