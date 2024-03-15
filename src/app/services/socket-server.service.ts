
// servicio que
import { Injectable } from '@angular/core';

import {Socket} from 'ngx-socket-io';
@Injectable({
  providedIn: 'root'
})
export class SocketServerService {

  constructor(private socket:Socket) {
    this.socket.emit("sala",'uml');
    console.log("y aquí entre?");
   }

  sendMessage(msg: string) {
    this.socket.emit('message', msg);
  }
  getMessage() {
    return this.socket.fromEvent('message');
  }
  getRealData() {
    return this.socket.fromEvent('reciveRealData');
  }
  accumulatedData(){
    return this.socket.fromEvent('almacenamientoDatos');
  }



}
