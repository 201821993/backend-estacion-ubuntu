const http = require('http');
const socketIO = require('socket.io');
const server = http.createServer(); // Crear un servidor HTTP básico
const io = socketIO(server); // Configurar Socket.IO para que se ejecute en el servidor

// Configurar eventos de conexión y desconexión
io.on('connection', (socket) => {
  console.log('Nuevo cliente conectado');

  // Manejar eventos personalizados
  socket.on('mensaje', (data) => {
    console.log('Mensaje recibido:', data);
   
  });
   // Emitir un evento a todos los clientes conectados
   io.emit('mensaje', "chingue su madre el peje");

  // Manejar eventos de desconexión
  socket.on('disconnect', () => {
    console.log('Cliente desconectado');
  });
});

// Iniciar el servidor en el puerto 3000
server.listen(3000, () => {
  console.log('Servidor Socket.IO escuchando en el puerto 3000');
});