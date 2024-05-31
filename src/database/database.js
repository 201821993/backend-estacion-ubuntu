// configuración de mysql y la base de datos 

import mysql from "promise-mysql"; //import mysql from "mysql2/promise";

import config from "../config.js";

const connection = mysql.createConnection({
    host:config.host,
    user:'estacion',
    password:config.password,
    database: config.database,
    port :'3306'
},{multipleStatement:true});


const getConnection = () =>{
    return connection;
}
module.exports = {
    getConnection
}