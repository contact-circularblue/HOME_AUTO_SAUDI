var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http, {'pingInterval': 2000, 'pingTimeout': 3600000});
var readlineSync = require('readline-sync');
var readline = require('readline');
var typeOf = require('typeof');
var net = require('net');
var fs = require("fs");
var mongoose = require('mongoose');



// Object.defineProperty(Object.prototype, 'isEmpty', {
//   enumerable: false,
//   value: () => 1
// });

// Object.prototype.isEmpty = function() {
//     for(var key in this) {
//         if(this.hasOwnProperty(key))
//             return false;
//     }
//     return true;
// }



//classes 
var Hub = require('./Hub');
var HubController = require('./HubController');
var Device = require('./Device');
var Events = require('./Events');
var Database = require('./Database');
///

var DeviceType = {Mobile:"Mobile",Hub:"Hub"};
connections = [];
// var db = new Database();
http.listen(3000, function(){

  console.log('listening on port :3000');
});



var stdin = process.openStdin();
stdin.setEncoding( 'utf8' );
stdin.on('data', function(chunk) {

  if(chunk.toString().trim() ==='rohan'){
    console.log("I am the greatest");

  }else if(chunk.toString().trim() ==='Hubs'){
    HubController.PrintHubs();

  }else if(chunk.toString().trim() ==='wifi'){

          var response_obj = {};
          response_obj['success'] = "true";
          response_obj['message'] = ['Circular Blue','mightycartoon'] ;
        
          io.emit(Events.Emit.wifi_details ,{ message: JSON.stringify(response_obj) } );
  }else if(chunk.toString().trim() ==='addNode'){

          var response_obj = {};
          response_obj['success'] = "true";
          response_obj['message'] = " " ;
          io.emit(Events.Emit.add_Node,{ message: JSON.stringify(response_obj) } );
  }else if(chunk.toString().trim() ==='power'){

  } else{
    console.log("command not found")
  }

 });


app.get('/', function(req, res){
   res.sendFile(__dirname + '/index.html');
   

});




io.on('ping',function(data){
  console.log('ping  ' + data );
});
io.on('pong',function(data){
  console.log('pong  ' + data );
});

///

io.on('connection', function(socket){
 
  connections.push(socket);
  console.log('connected %s sockets connected', connections.length);
  // console.log('transport ' + socket.io.engine.transport.name);
  console.log(socket.conn.transport.name);

  var socketId = socket.id;
  var clientIp = socket.request.connection.remoteAddress;


  //On connection request
  var NewObject = {};
  NewObject['success'] = "true";
  NewObject['message'] = "connected";
        
  socket.emit(Events.Emit.ack ,{ message: JSON.stringify(NewObject) } );
 // socket.emit(Events.Emit.ack ,JSON.stringify(NewObject));

  console.log("socket ID : " + socketId);
  console.log("Client IP : " + clientIp);

    socket.on("packet", function(type, data) {
    console.log("received ping");
});

socket.on("packetCreate", function(type, data) {
    console.log("sending pong");
});

socket.on('ping',function(data){
  console.log('ping  ' + data );
});
socket.on('pong',function(data){
  console.log('pong  ' + data );
});

  socket.on(Events.On.add_Node,function(data){

    switch(socket.DeviceType){

      case DeviceType.Mobile:
      console.log("Mobile : ");
      console.log(data);
        var response_obj = {};
          response_obj['success'] = "true";
          response_obj['message'] = " " ;
          socket.Hub.emit(Events.Emit.add_Node,{ message: JSON.stringify(response_obj) } );
        break;
      case DeviceType.Hub:
      console.log("Hub :");
      console.log(data);
      var node = socket.Hub.addNode(data.nodeId,data.type);
      //DATABASE

      // var db_obj = {};
      // {Hubid: socket.Hub.uniqueID(), Nodeid: data.nodeId}
      Database.addNode({hubid: socket.Hub.uniqueID(), node: node});
      socket.Hub.broadCastToMobieDevices({'nodeId':node.id(),'type':node.type()},Events.Emit.add_Node);
        break;
    }
    console.log("add node ");  
  });

  socket.on(Events.On.Node_info,function(data){



    var node = socket.Hub.getNode(data.nodeId);
    // var response_obj = {};
    // response_obj['success'] = "true";
    // response_obj['message'] = " " 

    socket.emit(Events.Emit.Node_info,node);
  });

  socket.on(Events.On.chat_message, function(msg){
  	console.log('message: ' + msg);
  	io.emit('chat message', msg);
  });

  socket.on(Events.On.addDevice, function(data,callback){
    // console.log(data);
    var deviceType,uniqueID;  
    deviceType = data.deviceType;
    uniqueID   = data.uniqueID; 
    // console.log("uniqueID" + uniqueID); 
    // console.log("deviceType" + deviceType); 

    switch(deviceType)
    { 
      case DeviceType.Hub:

        var hub_temp = HubController.AddHub(uniqueID,socket);
        // Database.find({});
        // Person.findOne({ 'name.last': 'Ghost' }, 'name occupation', function (err, person) {

        var response_obj = {};

        if(hub_temp != null){
          console.log("Hub Added");
          response_obj['success'] = "true";
          response_obj['message'] = "Hub Added";
          socket.DeviceType = DeviceType.Hub; 
          socket.Hub = hub_temp;

          mongoose.model('nodes').find({Hubid: '1234'},function(err,docs){

              for(var docs_i=0; docs_i < docs.length; docs_i++){

                var node_docs = docs[docs_i];
                var nodeId   = node_docs.Nodeid;
                var hubId    = node_docs.Hubid;
                var nodeType = node_docs.Nodetype;
                var devices =  node_docs.devices;
      
                    console.log("adding node to Hub");
                socket.Hub.addNode(nodeId,nodeType);
               } 
          });            

       }else{
          console.log("Hub Not Added")
          response_obj['success'] = "false";
          response_obj['message'] = "Hub Not Added";
       }
       socket.emit(Events.Emit.ack, { message: JSON.stringify(response_obj) } );
        setTimeout(function() {
            socket.emit(Events.On.dummy,"data");
          // HubController.UpdateDevices();
        }, 3000);

        break;

      case DeviceType.Mobile:
        var response_obj = {};

        console.log('Mobile connected');
        socket.DeviceType = DeviceType.Mobile;

          if(HubController.HubExists(uniqueID)){
               console.log("Hub Exists");
               var Hub_temp = HubController.GetHub(uniqueID);
               socket.Hub = Hub_temp;
               if(Hub_temp.addMobileDevice(socket)==1){
                  console.log("Mobile device added");
                 // callback(true);
                  socket.DeviceType = DeviceType.Mobile;
                  response_obj['success'] = "true";
                  response_obj['message'] = "Mobile Added";
               }else{
                  response_obj['success'] = "false";
                  response_obj['message'] = "Mobile Not Added";                
               }
              // mobiles.push(socket);
          }else{
              //  callback(false);
                response_obj['success'] = "false";
                response_obj['message'] = "Hub not found";
          }
          socket.emit(Events.Emit.addDevice,response_obj);
          break;

        }
     
  });

  socket.on(Events.On.wifi_details,function(data){
    socket.Hub.setWifiDetails(data);
    var response_obj = {};
    response_obj['success'] = "true";
    response_obj['message'] = [data.wifi_name,data.wifi_pass] ;
    socket.Hub.emit(Events.Emit.wifi_details ,{ message: JSON.stringify(response_obj) } );
    console.log('wifi_details');
    console.log(response_obj);
  });

  socket.on(Events.On.wifi_details_rec,function(wifi_details){
    console.log("wifi_details_rec");
    console.log(wifi_details);
    socket.Hub.broadCastToMobieDevices(wifi_details,Events.On.wifi_details);
  });

   socket.on(Events.On.get_wifi_details,function(data,callback){

    callback(socket.wifi_details.toString());
    //socket.hub.emit('wifi_details',data);
    console.log("data" + data + " callback "  +  socket.wifi_details.toString());
  });

   socket.on(Events.On.Node_change,function(data){
        console.log(data);
        switch(socket.DeviceType){
          case DeviceType.Mobile:
              console.log("Mobile : ");
              console.log(data);
              var response_obj = {};
              response_obj['success'] = "true";
              response_obj['nId'] = data.nodeId;
              response_obj['dId'] = data.deviceId;
              response_obj['dState'] = data.deviceState;
              socket.Hub.emit(Events.Emit.Node_change,{ message: JSON.stringify(response_obj) });
          break;
          case DeviceType.Hub:
            console.log("Hub : ");
            console.log(data);
            var response_obj = {};
            response_obj['nodeId'] = data.nId;
            response_obj['deviceId'] = data.dId;
            response_obj['deviceState'] = data.dState;

            // var node =  socket.Hub.getNode(data.nId);
            // var device = node.getDevice(data.dId);
            // device.setCurrentState(data.dState);

            socket.Hub.broadCastToMobieDevices(response_obj,Events.Emit.Node_change);
          break;
        }
   });

   socket.on(Events.On.addIRDevice,function(data){

        console.log("ADD IR DEVICE");
        console.log(data);
        switch(socket.DeviceType){
          case DeviceType.Mobile:
            console.log("Mobile : ");
            console.log(data);
              var response_obj = {};
              response_obj['success'] = "true";
              response_obj['nId'] = data.nodeId;
              socket.Hub.emit(Events.Emit.addIRDevice,{ message: JSON.stringify(response_obj) });
          break;
          case DeviceType.Hub:
            console.log("Hub : ");
            console.log(data);

            var response_obj = {};
            response_obj['nodeId']      = data.nId;
            response_obj['deviceId']    = data.dId;
            response_obj['deviceState'] = "true"; 
            response_obj['success']     = data.success ;



            var node = socket.Hub.getNode(data.nId);

            console.log("______________________________HUB =");
            console.log(socket.Hub);

            console.log("______________________________NODE = ");
            console.log(node);

            node.addDevice(new Device(data.dId,"IR"));

            socket.Hub.broadCastToMobieDevices(response_obj,Events.Emit.addIRDevice);
          break;
        }
   });

   socket.on(Events.On.Node_all,function(data){
        var nodes = []; 
        for (var i = 0; i < socket.Hub.Nodes.length; i++) {
            nodes.push({'nodeId':socket.Hub.Nodes[i].id(),'type':socket.Hub.Nodes[i].type()});
        }
        socket.emit(Events.Emit.Node_all,nodes);
   });

   socket.on(Events.On.Node_devices_IR,function(data){

        var node =  socket.Hub.getNode(data.nodeId);
        // console.log(node);
        var IRDevice = [];
        console.log("IR DEVICES FOR NODE : " + node.id());
        for (var i = 0; i < node.IRDevices.length; i++) {
           console.log(node.IRDevices[i].id());
        }
       // socket.emit(Events.Emit.Node_devices_IR,IRDevice);
   });

   socket.on(Events.On.Node_devices,function(data){

          var node =  socket.Hub.getNode(data.nodeId);

          var devices = [];
          for (var j = 0; j < node.Devices.length; j++) {
              // console.log("device id " + node.Devices[j].id());
              // console.log("current State " + node.Devices[j].currentState());
              devices.push({'id':node.Devices[j].id(),'state':node.Devices[j].currentState()});
          }
          console.log("Node devices : ")
          console.log(devices);
          socket.emit(Events.Emit.Node_devices,devices);
   });
  socket.on(Events.On.Node_power,function(data){

        console.log("NODE POWER");
        console.log(data);
        switch(socket.DeviceType){
          case DeviceType.Mobile:
            console.log("Mobile : ");
            console.log(data);
              var response_obj = {};
              response_obj['success'] = "true";
              response_obj['nId'] = data.nodeId;

              socket.Hub.emit(Events.Emit.Node_power,{ message: JSON.stringify(response_obj) });
          break;
          case DeviceType.Hub:
            console.log("Hub : ");
            console.log(data);
//            { nId: '4234567890', success: 'true', dId: '11' }
            var response_obj = {};
            response_obj['nodeId']      = data.nId;
            response_obj['power']    = data.power;     

            var node = socket.Hub.getNode(data.nId);
          //  node.addDevice(new Device(data.dId,"IR"));

            socket.Hub.broadCastToMobieDevices(response_obj,Events.Emit.Node_power);
          break;
        }
   });

  socket.on(Events.On.Node_IR_delete,function(data){

        // console.log("NODE POWER");
        // console.log(data);
        switch(socket.DeviceType){
          case DeviceType.Mobile:
            console.log("Mobile : ");
            console.log(data);
              var response_obj        = {};
              response_obj['success'] = "true";
              response_obj['nId']     = data.nodeId;
              response_obj['dId']     = data.deviceId;

              socket.Hub.emit(Events.Emit.Node_IR_delete,{ message: JSON.stringify(response_obj) });
          break;
          case DeviceType.Hub:
            console.log("Hub : ");
            console.log(data);
//            { nId: '4234567890', success: 'true', dId: '11' }
            var response_obj = {};
            response_obj['nodeId']   = data.nId;
            response_obj['power']    = data.power;     

            var node = socket.Hub.getNode(data.nId);
          //  node.addDevice(new Device(data.dId,"IR"));

           // socket.Hub.broadCastToMobieDevices(response_obj,Events.Emit.Node_IR_delete);
          break;
        }
  });



  socket.on(Events.On.dummy,function(data){
    console.log("HUB : " + socket.Hub.uniqueID() + " is connected");
 //   socket.emit(Events.On.dummy,data);
  });

 //    socket.on('message',function(data){
 //    console.log("HUB : " + socket.Hub.uniqueID() + " is connected");
 // //   socket.emit(Events.On.dummy,data);
 //  });
   socket.on('check_alive',function(data){
    console.log("data : " + data);
    // socket.Hub.checkAlive(true);    
  });

  socket.on(Events.On.disconnect ,function(data){
    //  console.log(socket.DeviceType);
    // console.log(data);
    switch(socket.DeviceType){

      case DeviceType.Hub:
        if(data == "transport close"){

          console.log("transport close for Hub");

            // HubController.RemoveHub(socket.Hub.uniqueID());
        }else if(data == "ping timeout"){

          console.log("ping timeout for Hub");
          // socket.Hub.emit('check_alive','There?');
          socket.emit('check_alive','There?');
          // socket.Hub.checkAlive(false);
          // socket.socket.reconnect();
    

          setTimeout(function(Hub){
            console.log('CHECK ALIVE : ' + Hub.uniqueID());
            if(!Hub.isAlive()){
              console.log("Hub is Dead : " + Hub.uniqueID())
               HubController.RemoveHub(Hub);
            }else{
              console.log("Hub is Alive : " + Hub.uniqueID());
            }

          }, 5000,socket.Hub);

        }else{

        }
        console.log("TIME : " + socket.Hub.getDateTime());
        // socket.Hub.getDateTime();
            break;
        case DeviceType.Mobile:

        if(data == "transport close"){

          console.log("transport close for Mobile");

        }else if(data == "ping timeout"){

          console.log("ping timeout for Mobile");
        }

        console.log("Mobile Deives length" + socket.Hub.MobileDevices.length)
        socket.Hub.MobileDevices.splice(socket,1);
        console.log("Mobile Deives length" + socket.Hub.MobileDevices.length)
                console.log("TIME : " + socket.Hub.getDateTime());

        break;
    }
    connections.splice(connections.indexOf(socket),1);
		console.log('Disconnected %s sockets connected',connections.length);
	});

});




