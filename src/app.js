
/* se configura  express y se configura socket.io  */


//se importa la dependencia de express
import  Express  from "express";

import  cors  from "cors";
//import socketio from "socket.io";

const bodyParser = require('body-parser');
//  se crea una constante de express
const app = Express();
const http = require('http').createServer(app);
const io = require('socket.io')(http);

// se importan las rutas
import realtimeRoute from "./routes/meteorological.routes";


app.use(bodyParser.urlencoded({ extended: false }));
/* se utiliza para establecer el puerto en el que se ejecutará tu aplicación Express. */
app.set('port', process.env.PORT || 3001);

// Middlewares
/*Funciones intermedias entre una petición y una respuesta*/
app.use(cors());
app.use(Express.json());
http.prependListener("request", (req, res) => {
    res.setHeader("Access-Control-Allow-Origin", "*");
 });

 /* app.use((req, res, next) => {
  console.log(`Se ha recibido una solicitud en: ${req.url}`);
  next();
});
 */
// las rutas
app.use(realtimeRoute);



/*  global.io.on("connection",socket=>{
    console.log(socket.id);
 }); */
 
 const globalDataWeather = require('./globals/globalsData');

// Se escucha el evento 'sala' y se imprime el dato enviado por el cliente
io.on('connection', socket=>{
  // all socket events here
  console.log('id socket',socket.id);
 socket.on('sala',(data)=>{
   console.log("Esta es la sala que manda el cliente ",data);
   io.emit('almacenamientoDatos',globalDataWeather);
 })
});



// exportación de app
app.set('socketio', io);

module.exports = { app, http };


