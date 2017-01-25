var mongoose = require('mongoose');
var async = require('async');

var Node = require('./Node');

mongoose.connect('mongodb://localhost/nodes',function(err){
  
	  if(err){
	    console.log(err);
	  }else{ 
	    console.log('connected to mongodb!');
	  }
});

var node_schema = mongoose.Schema({
  Hubid: String,
  Nodeid: String,
  Nodetype: String,
  devices: [{id: String,state: Boolean}],
  irDevices: [{id: String}]
});

var node_model = mongoose.model('nodes', node_schema);

 

module.exports = {

	addNode : function(data){
			var node = new node_model;


			var Hubid = data.hubid;
			var Nodeid = data.node.id();
			var Nodetype = data.node.type();
			var devices = data.node.getDevices();


			node.Hubid   = Hubid;
			node.Nodeid  = Nodeid;
			node.Nodetype = Nodetype;

			for(var i=0;i<devices.length;i++){
				var id = devices[i].id();
				var state =  devices[i].currentState();
				node.devices.push({id: id,state: state});
			}

			node.save(function(argument) {
				// body...
				console.log(argument);
			});

			console.log("Add node to database");
	},
	addDevice : function(node){


	},
    addDevices: function(node){

	},
	find : function(data){
		    mongoose.model('nodes').find(data,function(err,docs){

		    	return docs;
		 	});
	
	}
}


