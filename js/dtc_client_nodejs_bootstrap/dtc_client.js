// node stuff
process.env["NODE_TLS_REJECT_UNAUTHORIZED"] = 0;
var WebSocket = require('ws');

// dtc
const LOGON_REQUEST = 1;
const HEARTBEAT = 3;


const socket = new WebSocket('wss://localhost:11099');


socket.addEventListener('close', function(event){
    console.log('received close...');
    console.log(event.reason);
});



socket.addEventListener('error', function(event){
    console.log('received error...');
    console.log(event.message);
    
});



socket.addEventListener('message', function(event){
    console.log('received message...');
    console.log(event.data);
    var msg = JSON.parse(event.data);
    console.log('type is ', msg.Type);
    
    switch(msg.Type){
        case HEARTBEAT:
        console.log('sending heartbeat');
        socket.send('{"Type":3}\0');
        break;
    }


});



socket.addEventListener('open', function(event){
    //LOGON_REQUEST = 1
    console.log("logging in...");
    socket.send('{"Type":1, "HeartbeatIntervalInSeconds":5}\0')

});


