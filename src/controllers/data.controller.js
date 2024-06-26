import {getConnection} from "./../database/database";
import {app} from "../app";
import ecoData from "../globals/globalsData";
import fetch from "node-fetch";

import { response } from "express";
// estas variables se ocupan para calcular el viento 
let sensorMin = [63,80,89,120,175,232,273,385,438,569,613,667,746,812,869,931];
let sensorMax = [69,88,98,133,194,257,301,426,484,612,661,737,811,868,930,993];
let dirCard = ["SE","SE","SSW","S","NNE","NE","WSW","SW","NNW","N","WNW","NW","W"];
let incoming = 0;
let aux = "";
let weatherStation = ["",0,0];
let globalDirection = '';
let angle  = "";



const getRealTimeData = async(req,res) =>{
    console.log("pero sí me llego o no");
    try{
        const connection = await getConnection();
        const result = await connection.query("select * from get_RealTimeData");
      console.log("",req.body);
      res.json(result);
      res.status(200).json({status:"Well done!", message:"Ahí vamos poco a poco no sé por que no funcinaba"});

    }catch(error){
        res.status(500);
        res.send(error.message);
        console.log(res.status);
    }
    
   
}

//Este controlador ejecuta la vista sp_view_dataRain, la cual me permite ver la cantidad de lluvia las ultimas 6 horas.
const getRainData = async(req,res) =>{
   
    try{
            const connection = await getConnection();
            const result = await connection.query("select * from sp_view_dataRain");
            console.log("",req.body);
             res.json(result);
        

    }catch(error){
        res.status(500);
        res.send(error.message);
        console.log(res.status);
    }
}


//  este controlador ejecuta la vista weather_measurements la cual me va a permitir todos los datos de todos los sensores las ultimas 6 horas. 
const getDataWeatherStation = async(req,res) =>{
  
    try{

        const connection = await getConnection();
        const result = await connection.query("select * from sp_view_weatherdata");
        res.json(result);
     
     

    }catch(error){
        res.status(500);
        res.send(error.message);
        console.log(res.status);
    }
    
   
}

const EnvioDatos = async(req,res)=>{

   const url = 'https://ccaitese.com/servicioEstacion.php/+"?prueba="1'; // Cambia esto por la URL de tu documento PHP
        
   const { 
        
    temperature,
    pressure, 
    altitud, 
    ozono, 
    co2, 
    uv, 
    pm10_env, 
    pm25, 
    pm100_env, 
    windSpeed, 
    direction, 
   
   
   } = req.body;
   
     const data = {
        nombre: 'Juan',
        apellido: 'Pérez',
        edad: 30
    }; 
    
    fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({data})
    })
        .then(response => response.json())
        .then(data => {
            console.log('Respuesta del servidor:', data);
        })
        .catch(error => {
            console.error('Error se ha capturado un error', error);
        });
     

}


// controlador para insertar la información  que manda el Arduigo Giga cada media hora en la base de datos y que también se manda al cliente
const insertDataWeatherStation = async(req,res)=>{
  
    const { 
        
         temperature,
         pressure, 
         altitud, 
         ozono, 
         co2, 
         uv, 
         pm10_env, 
         pm25, 
         pm100_env, 
         windSpeed, 
         direction, 
        
        
        } = req.body;
        console.log('req.body',req.body);
        globalDirection = direction;
        
        ecoData.temperature = temperature;
        ecoData.pressure = pressure;
        ecoData.altitud = altitud;
        ecoData.ozono = ozono;
        ecoData.co2 = co2;
        ecoData.uv = uv;
        ecoData.pm10_env = pm10_env;
        ecoData.pm25 = pm25;
        ecoData.pm100_env = pm100_env;
        ecoData.windSpeed = windSpeed ;
        ecoData.direction = direction ;
        const url = 'https://ccaitese.com/servicioEstacion.php/+"?addW="1'; // Cambia esto por la URL de tu documento PHP


    fetch(url, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({ecoData})
    })
        .then(response => response.json())
        .then(data => {
            console.log('Respuesta del servidor:', data);
        })
        .catch(error => {
            console.error('Error se ha capturado un error', error);
        });


    try{
        // aquí se calcula la dirección del viento 
        for(let i=0; i<=15; i++) {
            
                    if(globalDirection >= sensorMin[i] && globalDirection <= sensorMax[i]) {
                        angle = dirCard[i];
                        break;
            } 
           }
        
        const connection = await getConnection();
        const result = await connection.query(`call sp_StoreMeteorologicalData('${temperature}','${pressure}','${altitud}','${pm10_env}','${pm25}','${pm100_env}','${ozono}','${co2}','${uv}','${windSpeed}','${angle}')`);
        res.status(200).json({status:"Well done!", message:" Data registered successfully "});
        const io = req.app.get('socketio');
        // aquí mandamos los datos al servidor 
        io.emit("reciveRealData", req.body);


       
    }catch(error){
        console.log(error);
        res.status(500).json(error.message);
    }
}

// esta función o controlador me permite llamar el procedimineto almacenado sp_storeLitrosm2, el cual me permite almacenar la cantidad de lluvia

const insertRanning = async(req,res)=>{
    const { 
        litrosm2,
        tds
         } = req.body;
     
   try{
       
       const connection = await getConnection();
       const result = await connection.query(`call  sp_storeLitrosm2('${litrosm2}','${tds}')`);
       res.status(200).json({status:"Well done!", message:"Datos registrados con exito"});
     //  const io = req.app.get('socketio');
     //  io.emit("reciveRealData", req.body);
       console.log(req.body);
      
   }catch(error){
       console.log(error);
       res.status(500).json(error.message);
   }

}

const showDataFromESP32 = async(req,res)=>{
    
    
  try{
     
     console.log(req.body);
   
      res.status(200).json({status:"Well done!", message:"bien echo "});
   // io.emit('reciveRealData',req.body);
     
  }catch(error){
      console.log(error);
      res.status(500).json(error.message);
  }
  }

export const methods = {
    getRealTimeData,
    insertDataWeatherStation,
    showDataFromESP32,
    insertRanning,
    getDataWeatherStation,
    getRainData,
    EnvioDatos
    
};
