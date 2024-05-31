import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class DataFetchManagerService {
  private apiUrl = 'http://estacion.ccaitese.com:3003/api/'; // Reemplaza con la URL de tu backend

  constructor( private http:HttpClient ) { }

  obtenerRainDatos(){
    return this.http.get("http://estacion.ccaitese.com:3003/api/getDataRain");
  }
  obtenerweatherMeasuremnts(){
    return this.http.get(this.apiUrl+"getDataWeather");
  }
  







}
