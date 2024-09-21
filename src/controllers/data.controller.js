import {getConnection} from "./../database/database";
import {app} from "../app";
import ecoData from "../globals/globalsData";
import fetch from "node-fetch";

import { response } from "express";
// estas variables se ocupan para calcular el viento 
let sensorExp = [66,84,126,184,244,287,406,461,599,630,702,785,827,886,945];
let sensorMin = [63,80,89,120,175,232,273,385,438,569,613,667,746,812,869,931];
let sensorMax = [69,88,98,133,194,257,301,426,484,612,661,737,811,868,930,993];
let dirCard = ["SE","SE","SSW","S","NNE","NE","WSW","SW","NNW","N","WNW","NW","W"];


/*
let sensorExp = [65,82,93,126,186,244,287,405,460,597,627,701,784,828,886,937];
let dirDeg = [112.5,67.5,90,157.5,135,202.5,180,22.5,45,247.5,225,337.5,0,292.5,315,270];
let dirCard = ["ESE","ENE","E","SSE","SE","SSW","S","NNE","NE","WSW","SW","NNW","N","WNW","NW","W"];
let sensorMin = [61,78,88,120,176,232,274,385,437,568,596,666,744,787,842,891];
let sensorMax = [68,86,97,133,195,257,302,426,483,627,659,736,823,869,930,1023];
*/

let incoming = 0;
let aux = "";
let weatherStation = ["",0,0];
let globalDirection = '';
let angle  = "";

// aquí mandamos los datos al servidor 


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
    /*
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
     */

}
const completeRecord = async(req,res)=>{
    /*
    const{
        ozono, 
        windSpeed, 
        direction, 
    }= req.body;
    */
    try {
        /*
        const connection = await getConnection();
        const result = await connection.query(`call sp_appendToRecord('${ozono}','${windSpeed}','${angle}')`);
        res.status(200).json({status:"Well done!", message:" Data registered successfully "});
        
        ecoData.ozono = ozono;
        ecoData.windSpeed = windSpeed ;
        ecoData.direction = direction ;
        
        */
        res.status(200).json({status:"Well done!", message:" Data registered successfully "});


            console.log("estoy llega del servidor",req.body);
       
    }catch(error){
        console.log(error);
        res.status(500).json(error.message);
    }

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
        //console.log('req.body',req.body);
        globalDirection = direction;
        
        ecoData.temperature = temperature;
        ecoData.pressure = pressure;
        ecoData.altitud = altitud;
        //ecoData.ozono = ozono;
        ecoData.co2 = co2;
        ecoData.uv = uv;
        ecoData.pm10_env = pm10_env;
        ecoData.pm25 = pm25;
        ecoData.pm100_env = pm100_env;
        //ecoData.windSpeed = windSpeed ;
        //ecoData.direction = direction ;
       
       /* const url = 'https://ccaitese.com/servicioEstacion.php/+"?addW="1'; // Cambia esto por la URL de tu documento PHP


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
*/

    try{
        // aquí se calcula la dirección del viento 
       
        const connection = await getConnection();
        const result = await connection.query(`call sp_StoreMeteorologicalData('${temperature}','${pressure}','${altitud}','${pm10_env}','${pm25}','${pm100_env}','${ozono}','${co2}','${uv}','${windSpeed}','${angle}')`);
        res.status(200).json({status:"Well done!", message:" Data registered successfully "});
        const io = req.app.get('socketio');
        // aquí mandamos los datos al servidor 
        io.emit("reciveRealData", ecoData);

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
    console.log("PERO VISTE O NO litros ",litrosm2,"tds",tds);    
   try{
       console.log("Sí entre o nelson");
      
       const connection = await getConnection();
       const result = await connection.query(`call  sp_storeRanningData('${litrosm2}','${tds}')`);
       res.status(200).json({status:"Well done!", message:"Datos registrados con exito"});


       /*
       const connection = await getConnection();
        const result = await connection.query(`call sp_StoreMeteorologicalData('${temperature}','${pressure}','${altitud}','${pm10_env}','${pm25}','${pm100_env}','${ozono}','${co2}','${uv}','${windSpeed}','${angle}')`);
*/

     //  const io = req.app.get('socketio');
     //  io.emit("reciveRealData", req.body);
       //console.log(req.body);
      
   }catch(error){
       console.log(error);
       res.status(500).json(error.message);
   }


/*
    try {

        const { listrosm2, tds } = req.body;

        console.log(listrosm2); // Esto debería mostrar: { listrosm2: 20, tds: 123.5 }
        res.status(200).json({status:"Well done!", message:"Datos registrados con exito"});    } catch (error) {
        console.error('Error procesando los datos:', error);
        res.status(400).send('Error en los datos recibidos');
    }
        */

}

const RainAndEnvController = async(req,res)=>{

    const { 
        datoTipo,
        dato1,
        dato2,
        dato3
         } = req.body;
 

    try{

        if (datoTipo=="1") {
            console.log("Me llegaron los datos ambientales");
        
               // aquí se calcula la dirección del viento 
            for(let i=0; i<=15; i++) {
            
                if(dato3 >= sensorMin[i] && dato3 <= sensorMax[i])
                    {
                        angle = dirCard[i];
                        break;
                } 
            }
            if(dato3 >940 ){
                    angle = "270° W";

            }
            else if(dato3>890 ){
                angle = "315° NW";
            }
            else if(dato3>820 ){
                angle = "2925° WNW";
            }
            else if(dato3>785 ){
                angle = "0° N";
            }
            else if(dato3>690 ){
                angle = "337.5 NNW";
            }
            else if(dato3>630 ){
                angle = "225° SW";
            }
            else if(dato3>590 ){
                angle = "247.5° WSW";
            }
            else if(dato3>455 ){
                angle = "NE";
            }
            else if(dato3>400 ){
                angle = "NNE";
            }
            else if(dato3>285 ){
                angle = "S";
            }
            else if(dato3>240 ){
                angle = "SSW";
            }
            else if(dato3>180 ){
                angle = "SE";
            }
            else if(dato3>125 ){
                angle = "SSE";
            }
            else if(dato3>90 ){
                angle = "E";
            }
            else if(dato3>80 ){
                angle = "ESE";
            }
            const connection = await getConnection();
            const result = await connection.query(`call sp_appendToRecord('${dato1}','${dato2}','${angle}')`);
            res.status(200).json({status:"Well done!", message:" Data registered successfully "});
            


            ecoData.ozono = dato1;
            ecoData.windSpeed = dato2 ;
            ecoData.direction = angle ;
            const io = req.app.get('socketio');

        // aquí mandamos los datos al servidor 
        io.emit("reciveRealData", ecoData);
       
         } else {
            console.log("Me llegaron los datos que no son ambientales ");
            const connection = await getConnection();
            const result = await connection.query(`call  sp_storeRanningData('${dato1}','${dato2}')`);
            res.status(200).json({status:"Well done!", message:"Datos registrados con exito"});
            
         }


    }catch(error){
        console.log(error);
        res.status(500).json(error.message);
    }
}

export const methods = {
    getRealTimeData,
    insertDataWeatherStation,
    insertRanning,
    getDataWeatherStation,
    getRainData,
    EnvioDatos,
    completeRecord,
    RainAndEnvController 
    
};
