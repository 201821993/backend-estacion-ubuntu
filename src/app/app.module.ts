import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { NgxGaugeModule } from 'ngx-gauge';
import {SocketIoConfig, SocketIoModule } from 'ngx-socket-io';
import { HttpClientModule } from '@angular/common/http';
import { DashboardViewComponent } from './components/dashboard-view/dashboard-view.component';

const config: SocketIoConfig = {
  url: 'http://estacion.ccaitese.com:3003/', //url: 'http://localhost:3001',
  options: {} };

@NgModule({
  declarations: [
    AppComponent,
    DashboardViewComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    NgxGaugeModule,

    SocketIoModule.forRoot(config),
    HttpClientModule,
    

  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
