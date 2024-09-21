import { Injectable } from '@angular/core';
import { HttpClient } from '@angular/common/http';
import { Observable } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class DataFetchManagerService {
  private apiUrl = 'http://localhost:3000/api/'; // Reemplaza con la URL de tu backend
// http://estacion.ccaitese.com:3000/api/  http://localhost:3000/api/';

  constructor( private http:HttpClient ) { }

  obtenerRainDatos(){
    return this.http.get("http://localhost:3000/api/getDataRain");// http://estacion.ccaitese.com:3000/api/getDataRain  |  http://localhost:3000/api/getDataRain
  } 
  obtenerweatherMeasuremnts(){
    return this.http.get(this.apiUrl+"getDataWeather");
  }
  







}
