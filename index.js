var app = require('express')();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var readlineSync = require('readline-sync');
var readline = require('readline');
var typeOf = require('typeof');

//classes 
var Hub = require('./Hub');
var HubController = require('./HubController');
//var exampleClass = require('./class_test');
var Events = require('./Events');
///

var DeviceType = {Mobile:"Mobile",Hub:"Hub"};
connections = [];

Object.prototype.isEmpty = function() {
    for(var key in this) {
        if(this.hasOwnProperty(key))
            return false;
    }
    return true;
}

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
  }else{
    console.log("command not found")
  }


 });


app.get('/', function(req, res){
  res.sendFile(__dirname + '/index.html');
});



io.on('connection', function(socket){
  
  connections.push(socket);
  
  console.log('connected %s sockets connected', connections.length)
  
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
  // console.log("username  : " + socket.username); 
  


  socket.on(Events.On.add_Node,function(data){
    if(data=="addNode"){
       var response_obj = {};
          response_obj['success'] = "true";
          response_obj['message'] = " " ;
          socket.Hub.emit(Events.Emit.add_Node,{ message: JSON.stringify(response_obj) } );

    }else{
       console.log(data);
       socket.Hub.broadCastToMobieDevices(data,Events.Emit.add_Node);
    }
    console.log("add node ");
  
   // socket.Hub.addNode(data.message,'4');
  });

  socket.on(Events.On.chat_message, function(msg){
  	console.log('message: ' + msg);
  	io.emit('chat message', msg);
  });

  socket.on(Events.On.addDevice, function(data,callback){
    console.log(data);
    var deviceType,uniqueID;  
    deviceType = data.deviceType;
    uniqueID   = data.uniqueID; 
    console.log("uniqueID" + uniqueID); 
    console.log("deviceType" + deviceType); 

    switch(deviceType)
    { 
      case DeviceType.Hub:

        var hub_temp = HubController.AddHub(uniqueID,socket);

        var response_obj = {};

        if(hub_temp != null){
          console.log("Hub Added");
          response_obj['success'] = "true";
          response_obj['message'] = "Hub Added";
          socket.DeviceType = DeviceType.Hub; 
          socket.Hub = hub_temp;

       }else{
          console.log("Hub Not Added")
          response_obj['success'] = "false";
          response_obj['message'] = "Hub Not Added";
       }
        socket.emit(Events.Emit.ack, { message: JSON.stringify(response_obj) } );
        break;

      case DeviceType.Mobile:
        console.log('Mobile connected');
        socket.DeviceType = DeviceType.Mobile;

          if(HubController.HubExists(uniqueID)){
               console.log("Hub Exists");
               var Hub_temp = HubController.GetHub(uniqueID);
               socket.Hub = Hub_temp;
               if(Hub_temp.addMobileDevice(socket)==1){
                  socket.DeviceType = DeviceType.Mobile;
                  console.log("Mobile device added");
                  callback(true);
               }

              // mobiles.push(socket);
          }else{
                callback(false);
          }

        
          break;

        }
     
  });

  socket.on(Events.On.wifi_details,function(data){
    socket.Hub.setWifiDetails(data);
    var response_obj = {};
    response_obj['success'] = "true";
    response_obj['message'] = [data.wifi_name,data.wifi_pass] ;
    socket.Hub.emit(Events.Emit.wifi_details ,{ message: JSON.stringify(response_obj) } );
  });

  socket.on(Events.On.wifi_details_rec,function(wifi_details){
    console.log("wifi_details_rec" +  wifi_details);
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
            console.log("Mobile : " + data);
              var response_obj = {};
              response_obj['success'] = "true";
              response_obj['nId'] = data.nodeId;
              response_obj['dId'] = data.deviceId;
              response_obj['dState'] = data.deviceState;

              socket.Hub.emit(Events.Emit.Node_change,{ message: JSON.stringify(response_obj) });
          break;
          case DeviceType.Hub:
            console.log("Hub : " + data);
            socket.Hub.broadCastToMobieDevices(data,Events.Emit.Node_change);
          break;
        }
   });



  socket.on(Events.On.dummy,function(data){
   // socket.emit(Events.On.dummy,data);
  });

  socket.on(Events.On.disconnect ,function(data){

    //  console.log(socket.DeviceType);
    console.log(data);
    switch(socket.DeviceType){

      case DeviceType.Hub:
          HubController.RemoveHub(socket.Hub.uniqueID());
          break;
      case DeviceType.Mobile:
          console.log("Mobile Removed");
          break;
    }
    connections.splice(connections.indexOf(socket),1);
		console.log('Disconnected %s sockets connected',connections.length);
	});

});

http.listen(3000, function(){
  console.log('listening on port :3000');
});

